#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "tradecrypto.h"
#include "consumers.h"
#include "report.h"
#include <iostream>
#include "producers.h"

void* consumer(void* arg) {

    ConsumerData *data = (struct ConsumerData*)arg;

    
    while(data->broker->coinsConsumed < data->broker->numOfTradeRequests){

        usleep(data->timeToConsume);

        pthread_mutex_lock(&data->broker->queueMutex);

        while (data->broker->brokerQueue.empty()) {
            pthread_cond_wait(&data->broker->notEmpty, &data->broker->queueMutex);
        }

        RequestType coinRemoved = data->broker->brokerQueue.front();
        data->broker->brokerQueue.pop();

        data->blockChainConsumed[coinRemoved]++;
        data->broker->inRequestQueue[coinRemoved]--;

        if(coinRemoved == Bitcoin){
            data->broker->BTCCount--;
            pthread_cond_signal(&data->broker->BTCNotFull);
        }

        data->broker->coinsConsumed++;

        report_request_removed(data->type, coinRemoved, data->blockChainConsumed, data->broker->inRequestQueue);

        pthread_mutex_unlock(&data->broker->queueMutex);

        pthread_cond_signal(&data->broker->notFull);

        

    }
    
    pthread_exit(NULL);
}
