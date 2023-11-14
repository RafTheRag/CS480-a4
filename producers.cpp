#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "tradecrypto.h"
#include "producers.h"
#include "monitor.h"
#include "report.h"



void* bitcoin_producer(void* arg) {

    

    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Bitcoin;

    

    while(monitor->totalProduced < monitor->numOfTradeRequests){

        usleep(monitor->msToProduceBTC);

        while(monitor->btcCount > 5){
            
        }

        monitor->insert(request);
        
        report_request_added(request, monitor->produced, monitor->inRequestQueue);
        
    }

   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Ethereum;

    // unsigned int produced[RequestTypeN] = {0, 0};

    while(monitor->totalProduced < monitor->numOfTradeRequests){


        usleep(monitor->msToProduceETH);
        
        monitor->insert(request);


        report_request_added(request, monitor->produced, monitor->inRequestQueue);

    }

    pthread_exit(NULL);
}