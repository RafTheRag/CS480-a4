#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "tradecrypto.h"
#include "consumers.h"
#include "monitor.h"

void* blockchain_x_consumer(void* arg) {
    // Blockchain X consumer logic
    // ...
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;


    unsigned int consumed[RequestTypeN] = {0, 0};
    
    while(monitor->totalConsumed < monitor->numOfTradeRequests){
        usleep(monitor->msForX);
        RequestType coinType = monitor->brokerQueue.front();
        RequestType currType = monitor->remove(coinType);

        if(currType == Bitcoin){
            consumed[Bitcoin] += 1;
        } else {
            consumed[Ethereum] += 1;
        }    


        report_request_removed(BlockchainX, currType, consumed, monitor->inRequestQueue);

    }
    
    pthread_exit(NULL);
}

void* blockchain_y_consumer(void* arg) {
    // Blockchain Y consumer logic
    // ...
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    unsigned int consumed[RequestTypeN] = {0, 0};

    while(monitor->totalConsumed < monitor->numOfTradeRequests){
        usleep(monitor->msForY);
        RequestType coinType = monitor->brokerQueue.front();
        RequestType currType = monitor->remove(coinType);

        if(currType == Bitcoin){
            consumed[Bitcoin] += 1;
        } else {
            consumed[Ethereum] += 1;
        }    


        report_request_removed(BlockchainY, currType, consumed, monitor->inRequestQueue);

    }
    

    pthread_exit(NULL);
}
