#include <fstream>
#include <iostream>
#include "monitor.h"


void ProducerConsumerMonitor::insert(RequestType type){

    pthread_mutex_lock(&queueMutex);

    while (brokerQueue.size() == capacity) {
        pthread_cond_wait(&notFull, &queueMutex); 
    }


    
    brokerQueue.push(type);
    produced[type] += 1;
    inRequestQueue[type] +=1;
    if(type == Bitcoin) btcCount++;
    totalProduced++;

    pthread_mutex_unlock(&queueMutex);
    

    pthread_cond_signal(&notEmpty);

    
}

RequestType ProducerConsumerMonitor::remove(RequestType type){
    pthread_mutex_lock(&queueMutex);

    while (brokerQueue.empty()) {
            pthread_cond_wait(&notEmpty, &queueMutex);
    }


        
    RequestType item = brokerQueue.front();
    brokerQueue.pop();
    inRequestQueue[type] -= 1;
    if(type == Bitcoin) btcCount--;
    totalConsumed++;
       
    pthread_mutex_unlock(&queueMutex);

    pthread_cond_signal(&notFull);    
    return item;
    


}
