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
    
    
    RequestType currType = Bitcoin;

    unsigned int inRequestQueue[RequestTypeN] = {0, 0};;

    unsigned int consumed[RequestTypeN] = {0, 0};
    while(1){

    if(currType == Bitcoin){
        inRequestQueue[Bitcoin] -= 1;
        consumed[Bitcoin] += 1;
    } else {
        inRequestQueue[Ethereum] -= 1;
        consumed[Ethereum] += 1;
    }    


    report_request_removed(BlockchainX, currType, consumed, inRequestQueue);

    }
    
    pthread_exit(NULL);
}

void* blockchain_y_consumer(void* arg) {
    // Blockchain Y consumer logic
    // ...
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    pthread_exit(NULL);
}

