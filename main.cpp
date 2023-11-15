/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <fstream>
#include "report.h"
#include "tradecrypto.h"
#include "producers.h"
#include "consumers.h"
#include "monitor.h"

using namespace std;

int main(int argc, char** argv) {
    
    //Creates ProducerConsumerMonitor class object (used for sharing data between main, producer and consumers)
    ProducerConsumerMonitor monitorData;

    //Creates two class objects for the producers
    ProducerData BTCData;
    ProducerData ETHData;

    //Gives specific types to each object (each share monitorData)
    BTCData.broker = &monitorData;
    BTCData.type = Bitcoin;

    ETHData.broker = &monitorData;
    ETHData.type = Ethereum;

    ProducerData coinProducers[RequestTypeN] = {BTCData, ETHData};  //used for producer's optional arguements

    //Creates two class objects for the producers
    ConsumerData blockChainXData;
    ConsumerData blockChainYData;

    //Gives specific types to each object (each share monitorData)
    blockChainXData.broker = &monitorData;
    blockChainXData.type = BlockchainX;

    blockChainYData.broker = &monitorData;
    blockChainYData.type = BlockchainY;

    ConsumerData coinConsumers[ConsumerTypeN] = {blockChainXData, blockChainYData}; //used for consumer's optional arguements

    int option = 0;
    
    //Contains the code for optional arguements for command line
    while ((option = getopt(argc, argv, "n:x:y:b:e:")) != -1) {
        switch (option) {
            
            case 'n':

                monitorData.numOfTradeRequests = atoi(optarg);                          //Total number of trade requests (production limit). The default is 120 if not specified
                if (monitorData.numOfTradeRequests < 0){
                    cerr << "Number of trade requests must be atleast 1" << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'x':
                coinConsumers[BlockchainX].timeToConsume = atoi(optarg) * 1000;        //Specifies the number of milliseconds N that the consumer using Blockchain X for processing a trade request and completing its transaction.   
                break;

            case 'y':
                coinConsumers[BlockchainY].timeToConsume = atoi(optarg) * 1000;        //Specifies the number of milliseconds N that the consumer using Blockchain Y for processing a trade request and completing its transaction.
                break;

            case 'b':
                coinProducers[Bitcoin].timeToProduce = atoi(optarg) * 1000;            //Specifies the number of milliseconds required to produce and publish a Bitcoin request.
                break;

            case 'e':
                coinProducers[Ethereum].timeToProduce = atoi(optarg) * 1000;           //Specifies the number of milliseconds required to produce and publish a Ethereum request.
                break;


            default:
                cout << "Usage: " << argv[0] << " [-n numOfTradeRequests] [-x msForX] [-y msForY] [-b msToProduceBTC] [-e msToProduceETH]" << endl;
                exit(1);
        }
    }



    sem_init(&monitorData.barrierSem, 0, 0);

    //creates four threads(two for producers and two for comsumers)
    pthread_t producers[RequestTypeN];
    pthread_t consumers[ConsumerTypeN];

    //initializes all the pthread mutexs and conditionals
    pthread_mutex_init(&monitorData.queueMutex, NULL);
    pthread_cond_init(&monitorData.notEmpty, NULL);
    pthread_cond_init(&monitorData.notFull, NULL);
    pthread_cond_init(&monitorData.BTCNotFull, NULL);


    //starts the four threads(two for producers and two for comsumers), each one calls on either a producer or consumer thread function to either generate or consume for its specified request type or blockchain
    pthread_create(&producers[Bitcoin], NULL, &producer, (void*)&coinProducers[Bitcoin]);
    pthread_create(&producers[Ethereum], NULL, &producer, (void*)&coinProducers[Ethereum]);
    pthread_create(&consumers[BlockchainX], NULL, &consumer, (void*)&coinConsumers[BlockchainX]);
    pthread_create(&consumers[BlockchainY], NULL, &consumer, (void*)&coinConsumers[BlockchainY]);

    // Wait for producer threads to finish
    pthread_join(producers[Bitcoin], NULL);
    pthread_join(producers[Ethereum], NULL);

    // Wait for consumer threads to finish
    pthread_join(consumers[BlockchainX], NULL);
    pthread_join(consumers[BlockchainY], NULL);


    //our way of returning/updating the values of each consumer after the consumer threads run
    blockChainXData.blockChainConsumed[Bitcoin] = monitorData.BTCConsumedByX;
    blockChainXData.blockChainConsumed[Ethereum] = monitorData.ETHConsumedByX;

    blockChainYData.blockChainConsumed[Bitcoin] = monitorData.BTCConsumedByY;
    blockChainYData.blockChainConsumed[Ethereum] = monitorData.ETHConsumedByY;

    unsigned int* consumedSummary[ConsumerTypeN] = {blockChainXData.blockChainConsumed, blockChainYData.blockChainConsumed};


    //function uses the array for the producers and the 2d array for the consumers to print out a progress report after the thread are done running
    report_production_history(monitorData.produced, consumedSummary);

    exit(0);

}  

