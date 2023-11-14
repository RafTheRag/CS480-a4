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

    

    while(true){

        usleep(monitor->msToProduceBTC);

        monitor->insert(request);
    

        
        report_request_added(request, monitor->produced, monitor->inRequestQueue);

        std::cout << monitor->produced[Bitcoin] + monitor->produced[Ethereum] << std::endl;
        std::cout << monitor->numOfTradeRequests << std::endl;

        if (monitor->produced[Bitcoin] + monitor->produced[Ethereum] == monitor->numOfTradeRequests){
            break;
        }

        
    }

   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    
    ProducerConsumerMonitor *monitor = (ProducerConsumerMonitor*)arg;

    RequestType request = Ethereum;

    // unsigned int produced[RequestTypeN] = {0, 0};

    while(true){


        usleep(monitor->msToProduceETH);
        
        monitor->insert(request);


        std::cout << monitor->produced[Bitcoin] + monitor->produced[Ethereum] << std::endl;
        std::cout << monitor->numOfTradeRequests << std::endl;


        report_request_added(request, monitor->produced, monitor->inRequestQueue);

        if (monitor->produced[Bitcoin] + monitor->produced[Ethereum] == monitor->numOfTradeRequests){
            break;
        }
    }

    pthread_exit(NULL);
}