/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "tradecrypto.h"
#include "consumers.h"
#include "report.h"
#include <iostream>
#include "producers.h"

/*We consume a coin by removing it from the broker queue each time our corresponding blockcain is done sleeping. We do this while total amount consumed by both blockchains is less than the
number of trade requests. Once we exit the loop, we transfer over the individual amounts of coins consumed by each blockchain to a monitor variable. We do this in order to print the summary 
in main*/
void* consumer(void* arg) {

    ConsumerData *data = (struct ConsumerData*)arg; //We pass in our corresponding struct pointer as data

    
    while(data->broker->coinsConsumed < data->broker->numOfTradeRequests - 1){

        usleep(data->timeToConsume);

        pthread_mutex_lock(&data->broker->queueMutex); //Mutexlock once blockchain is done sleeping

        while (data->broker->brokerQueue.empty()) {
            pthread_cond_wait(&data->broker->notEmpty, &data->broker->queueMutex); //If our broker queue is empty we have to wait for a producer to produce
        }

        RequestType coinRemoved = data->broker->brokerQueue.front(); //We see that type of coin we are consuming
        data->broker->brokerQueue.pop(); //Remove coin from broker queue

        data->blockChainConsumed[coinRemoved]++;
        data->broker->inRequestQueue[coinRemoved]--;

        if(coinRemoved == Bitcoin){
            data->broker->BTCCount--;
            pthread_cond_signal(&data->broker->BTCNotFull); //We signal back to the produce waiting to produce BTC letting it know that there is less than 6 BTC in the broker queue
        }

        data->broker->coinsConsumed++;

        report_request_removed(data->type, coinRemoved, data->blockChainConsumed, data->broker->inRequestQueue); //We report the consumer transaction

        pthread_mutex_unlock(&data->broker->queueMutex); //MutexUnlock once blockchain is done removing.

        pthread_cond_signal(&data->broker->notFull); //We signal back to the producer waiting to produce coins letting it know that the broker queue is no longer full

    }
    
    //We have to do this to transfer the needed values for the summary from the threads to main. This is done through the monitor shared data
    if(data->type == BlockchainX){
        data->broker->BTCConsumedByX = data->blockChainConsumed[Bitcoin];
        data->broker->ETHConsumedByX = data->blockChainConsumed[Ethereum];
    }else{
        data->broker->BTCConsumedByY = data->blockChainConsumed[Bitcoin];
        data->broker->ETHConsumedByY = data->blockChainConsumed[Ethereum];
    }
    
    pthread_exit(NULL); //Exit Thread
}
