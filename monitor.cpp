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

RequestType ProducerConsumerMonitor::remove(){
    
    
    pthread_mutex_lock(&queueMutex);

        while (brokerQueue.empty()) {
            pthread_cond_wait(&notEmpty, &queueMutex);
        }
        RequestType item = brokerQueue.front();
        brokerQueue.pop();
        pthread_cond_signal(&notFull);
       
        pthread_mutex_unlock(&queueMutex);
        return item;
    


}
