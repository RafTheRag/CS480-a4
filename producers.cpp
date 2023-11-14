#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "tradecrypto.h"
#include "producers.h"
#include "monitor.h"


void* bitcoin_producer(void* arg) {

    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Bitcoin;

    while(true){

        usleep(monitor->msToProduceBTC);

        monitor->brokerQueue.push(request);
        monitor->btcCount++;
        monitor->currentCount++;
    }

   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Ethereum;

    while(true){

        usleep(monitor->msToProduceETH);
        
        monitor->brokerQueue.push(request);
        monitor->currentCount++;
    }

    pthread_exit(NULL);
}