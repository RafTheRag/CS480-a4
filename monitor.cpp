#include <fstream>
#include <iostream>
#include "monitor.h"


void ProducerConsumerMonitor::insert(RequestType type){
    while (brokerQueue.size() == capacity) {
        pthread_cond_wait(&notFull, &queueMutex); 
    }

    pthread_mutex_lock(&queueMutex);

    
    brokerQueue.push(type);
    produced[type] += 1;
    inRequestQueue[type] +=1;

    pthread_mutex_unlock(&queueMutex);
    

    pthread_cond_signal(&notEmpty);

    
}

RequestType ProducerConsumerMonitor::remove(RequestType type){
    while (brokerQueue.empty()) {
            pthread_cond_wait(&notEmpty, &queueMutex);
    }
    
    pthread_mutex_lock(&queueMutex);

        
    RequestType item = brokerQueue.front();
    brokerQueue.pop();
    inRequestQueue[type] -= 1;
    totalConsumed++;
       
    pthread_mutex_unlock(&queueMutex);

    pthread_cond_signal(&notFull);    
    return item;
    


}
