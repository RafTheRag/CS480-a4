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

    unsigned int produced[RequestTypeN] = {0, 0};

    while(true){
        
        

        usleep(monitor->msToProduceBTC);

        monitor->insert(request);
    

        produced[Bitcoin] += 1;

        monitor->inRequestQueue[Bitcoin] += 1;

        report_request_added(request, produced, monitor->inRequestQueue);

        if (produced[Bitcoin] + produced[Ethereum] == monitor->numOfTradeRequests){
            break;
        }
    }

   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Ethereum;

    unsigned int produced[RequestTypeN] = {0, 0};

    while(true){


        usleep(monitor->msToProduceETH);
        
        monitor->brokerQueue.push(request);
        monitor->currentCount++;

        produced[Ethereum] += 1;
        monitor->inRequestQueue[Ethereum] += 1;

        report_request_added(request, produced, monitor->inRequestQueue);

        if (produced[Bitcoin] + produced[Ethereum] == monitor->numOfTradeRequests){
            break;
        }
    }

    pthread_exit(NULL);
}