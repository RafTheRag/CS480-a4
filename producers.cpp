#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "tradecrypto.h"
#include "producers.h"
#include "monitor.h"


void* bitcoin_producer(void* arg) {
    // Bitcoin producer logic
    // ...

    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    usleep(monitor->msToProduceBTC);

    
    RequestType request = Bitcoin;



   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    // Ethereum producer logic
    // ...

    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    usleep(monitor->msToProduceETH);

    RequestType request = Ethereum;

    pthread_exit(NULL);
}