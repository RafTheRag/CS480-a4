#include <fstream>
#include <iostream>
#include "monitor.h"


void ProducerConsumerMonitor::insert(RequestType type){
    pthread_mutex_lock(&queueMutex);

    while (brokerQueue.size() == capacity) {
        pthread_cond_wait(&notFull, &queueMutex); 
    }
    brokerQueue.push(type);
    pthread_cond_signal(&notEmpty);

    pthread_mutex_unlock(&queueMutex);
}

/*void ProducerConsumerMonitor::remove(RequestType type){
    pthread_mutex_lock(&queueMutex);

        while (brokerQueue.empty()) {
            pthread_cond_wait(&notEmpty, &queueMutex);
        }
        RequestType item = brokerQueue.pop();
        pthread_cond_signal(&notFull);
       
        pthread_mutex_unlock(&queueMutex);
        return item;
    


}*/
