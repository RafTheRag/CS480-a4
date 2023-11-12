#include <fstream>
#include <iostream>
#include "monitor.h"

void ProducerConsumerMonitor::insert(RequestType type){
    pthread_mutex_lock(&queue_mutex);

    while (brokerQueue.size() == capacity) {
        pthread_cond_wait(&notFull, &queue_mutex); 
    }
    brokerQueue.push(type);
    pthread_cond_signal(&notEmpty);

    pthread_mutex_unlock(&queue_mutex);
}

void ProducerConsumerMonitor::remove(RequestType type){
    pthread_mutex_lock(&mutex);

        while (queue.empty()) {
            pthread_cond_wait(&notEmpty, &queue_mutex);
        }
        T item = queue.pop();
        pthread_cond_signal(&notFull);
       
        pthread_mutex_unlock(&mutex);
        return item;
    


}
