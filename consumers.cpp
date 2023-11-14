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
    // while(true){
    //     usleep(monitor->msForX);

    //     RequestType currType = monitor->remove();

    //     if(currType == Bitcoin){
    //         monitor->inRequestQueue[Bitcoin] -= 1;
    //         consumed[Bitcoin] += 1;
    //     } else {
    //         monitor->inRequestQueue[Ethereum] -= 1;
    //         consumed[Ethereum] += 1;
    //     }    


    //     report_request_removed(BlockchainX, currType, consumed, monitor->inRequestQueue);

    // }
    
    pthread_exit(NULL);
}

void* blockchain_y_consumer(void* arg) {
    // Blockchain Y consumer logic
    // ...
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    pthread_exit(NULL);
}

