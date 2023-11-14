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

    

    // while(true){

        usleep(monitor->msToProduceBTC * 1000);

        monitor->insert(request);
    

        // produced[Bitcoin] += 1;

        // monitor->inRequestQueue[Bitcoin] += 1;

        
        report_request_added(request, monitor->produced, monitor->inRequestQueue);

    //     if (monitor->produced[Bitcoin] + monitor->produced[Ethereum] == monitor->numOfTradeRequests){
    //         break;
    //     }

        
    // }

   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Ethereum;

    // unsigned int produced[RequestTypeN] = {0, 0};

    // while(true){


        usleep(monitor->msToProduceETH * 1000);
        
        monitor->insert(request);

        // produced[Ethereum] += 1;
        // monitor->inRequestQueue[Ethereum] += 1;

        report_request_added(request, monitor->produced, monitor->inRequestQueue);

    //     if (monitor->produced[Bitcoin] + monitor->produced[Ethereum] == monitor->numOfTradeRequests){
    //         break;
    //     }
    // }

    pthread_exit(NULL);
}