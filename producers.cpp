/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "tradecrypto.h"
#include "producers.h"
#include "report.h"
#include <iostream>

/*We produce a coin and add it to the broker queue each time our corresponding producer is done sleeping. We do this while total amount produced by both producers is less than the number of
trade requests*/
void* producer(void* arg) {

    ProducerData *data = (struct ProducerData*)arg; //We pass in our corresponding struct pointer as data


    while(data->broker->coinsProduced < data->broker->numOfTradeRequests - 1){

        usleep(data->timeToProduce);

        pthread_mutex_lock(&data->broker->queueMutex); //Mutexlock once producer is done sleeping

        while (data->broker->brokerQueue.size() == data->broker->capacity) {
            pthread_cond_wait(&data->broker->notFull, &data->broker->queueMutex); //If our broker queue is full we need to wait for a consumer to consume
        }
        
        //Since we can have a max of 6 BTC in the broker queue at a time, we need to check if we are full on BTC
        if(data->type == Bitcoin){
            while(data->broker->BTCCount > 5){
                pthread_cond_wait(&data->broker->BTCNotFull, &data->broker->queueMutex); //If our broker queue has 6 BTC we nned to wait for a consumer to consume BTC
            }
            data->broker->BTCCount++;
        }

        data->broker->brokerQueue.push(data->type); //Add coin to broker queue
        data->broker->produced[data->type]++;
        data->broker->inRequestQueue[data->type]++;

        data->broker->coinsProduced++;
        
        report_request_added(data->type, data->broker->produced, data->broker->inRequestQueue); //We report the production transaction

        pthread_mutex_unlock(&data->broker->queueMutex); //Mutexunlock once producer is done adding to the broker queue

        pthread_cond_signal(&data->broker->notEmpty); //We signal back to the consumer waiting to consume letting it know that the broker queue is no longer empty
        
    }

   pthread_exit(NULL); //Exit Thread
}