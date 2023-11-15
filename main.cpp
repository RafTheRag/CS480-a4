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
    //checks if there is valid amount of mandatory arguements in the command line
    if (argc < 3) {
        throw invalid_argument("Invalid num of arguements");
    }
    
    int option = 0;
    
    ProducerConsumerMonitor monitorData;


    ProducerData BTCData;
    ProducerData ETHData;

    BTCData.broker = &monitorData;
    BTCData.type = Bitcoin;

    ETHData.broker = &monitorData;
    ETHData.type = Ethereum;

    ProducerData coinProducers[RequestTypeN] = {BTCData, ETHData};

    ConsumerData blockChainXData;
    ConsumerData blockChainYData;

    blockChainXData.broker = &monitorData;
    blockChainXData.type = BlockchainX;

    blockChainYData.broker = &monitorData;
    blockChainYData.type = BlockchainY;

    ConsumerData coinConsumers[ConsumerTypeN] = {blockChainXData, blockChainYData};
    

    while ((option = getopt(argc, argv, "n:x:y:b:e:")) != -1) {
        switch (option) {
            
            case 'n':
                monitorData.numOfTradeRequests = atoi(optarg);
                //checks if numOfProgressMarks is greater than 10 to run
                if (monitorData.numOfTradeRequests < 0){
                    cerr << "Number of trade requests must be atleast 1" << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'x':
                coinConsumers[BlockchainX].timeToConsume = atoi(optarg) * 1000;                
                break;

            case 'y':
                coinConsumers[BlockchainY].timeToConsume = atoi(optarg) * 1000;
                break;

            case 'b':
                coinProducers[Bitcoin].timeToProduce = atoi(optarg) * 1000;
                break;

            case 'e':
                coinProducers[Ethereum].timeToProduce = atoi(optarg) * 1000;
                break;


            default:
                cout << "Usage: " << argv[0] << " [-n numOfTradeRequests] [-x msForX] [-y msForY] [-b msToProduceBTC] [-e msToProduceETH]" << endl;
                exit(1);
        }
    }

    sem_init(&monitorData.barrierSem, 0, 0);

    pthread_t producers[RequestTypeN];
    pthread_t consumers[ConsumerTypeN];
    pthread_mutex_init(&monitorData.queueMutex, NULL);
    pthread_cond_init(&monitorData.notEmpty, NULL);
    pthread_cond_init(&monitorData.notFull, NULL);
    pthread_cond_init(&monitorData.BTCNotFull, NULL);

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

    

    exit(0);

}  

