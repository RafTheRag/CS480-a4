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
#include "btcproducer.h"

using namespace std;

int main(int argc, char** argv) {
    //checks if there is valid amount of mandatory arguements in the command line
    if (argc < 3) {
        throw invalid_argument("Invalid num of arguements");
    }
   

    int option = 0;
    
    int numOfTradeRequests = 120;
    int msForX = 0;
    int msForY = 0;
    int msToProduceBTC = 0;
    int msToProduceETH = 0;

    while ((option = getopt(argc, argv, "n:x:y:b:e:")) != -1) {
        switch (option) {
            
            case 'n':
                numOfTradeRequests = atoi(optarg);
                //checks if numOfProgressMarks is greater than 10 to run
                if (numOfTradeRequests < 0){
                    cerr << "Number of trade requests must be atleast 1" << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'x':
                msForX = atoi(optarg);                
                break;

            case 'y':
                msForY = atoi(optarg);
                break;

            case 'b':
                msToProduceBTC = atoi(optarg);
                break;

            case 'e':
                msToProduceETH = atoi(optarg);
                break;


            default:
                cout << "Usage: " << argv[0] << "[-n numOfTradeRequests] [-x msForX] [-y msForY] [-b msToProduceBTC] [-e msToProduceETH]" << endl;
                exit(1);
        }
    }

    pthread_t producers[2];
    pthread_t consumers[2];

    pthread_create(&producers[0], NULL, bitcoin_producer, NULL);
    pthread_create(&producers[1], NULL, ethereum_producer, NULL);
    pthread_create(&consumers[0], NULL, blockchain_x_consumer, NULL);
    pthread_create(&consumers[1], NULL, blockchain_y_consumer, NULL);

    // Wait for producer threads to finish
    pthread_join(producers[0], NULL);
    pthread_join(producers[1], NULL);

    // Wait for consumer threads to finish
    pthread_join(consumers[0], NULL);
    pthread_join(consumers[1], NULL);


    exit(0);

}  

