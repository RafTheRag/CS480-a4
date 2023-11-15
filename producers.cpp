#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "tradecrypto.h"
#include "producers.h"
#include "report.h"
#include <iostream>


void* producer(void* arg) {

    ProducerData *data = (struct ProducerData*)arg;


    while(data->broker->coinsProduced < data->broker->numOfTradeRequests - 1){

        usleep(data->timeToProduce);

        pthread_mutex_lock(&data->broker->queueMutex);

        data->broker->coinsProduced++;

        while (data->broker->brokerQueue.size() == data->broker->capacity) {
            pthread_cond_wait(&data->broker->notFull, &data->broker->queueMutex); 
        }
        
        if(data->type == Bitcoin){
            while(data->broker->BTCCount > 5){
                pthread_cond_wait(&data->broker->BTCNotFull, &data->broker->queueMutex);
            }
            data->broker->BTCCount++;
        }

        data->broker->brokerQueue.push(data->type);
        data->broker->produced[data->type]++;
        data->broker->inRequestQueue[data->type]++;
        
        report_request_added(data->type, data->broker->produced, data->broker->inRequestQueue);

        pthread_mutex_unlock(&data->broker->queueMutex);

        pthread_cond_signal(&data->broker->notEmpty);
        
    }

   pthread_exit(NULL);
}