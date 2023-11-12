#ifndef MONITORS_H
#define MONITORS_H

#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include "tradecrypto.h"  // Include the necessary structures
class ProducerConsumerMonitor{
    public:
        sem_t barrier_sem;
        pthread_mutex_t queue_mutex;          // Mutex for protecting critical sections
        pthread_cond_t unconsumed;      // Condition variable for signaling unconsumed items
        pthread_cond_t availableSlots;   // Condition variable for signaling available slots
        int capacity = 15;
        std::queue<int> brokerQueue;
        
        unsigned int numOfTradeRequests = 120;
        unsigned int msForX = 0;
        unsigned int msForY = 0;
        unsigned int msToProduceBTC = 0;
        unsigned int msToProduceETH = 0;

        void insert(RequestType type);
        void remove(RequestType type);

};


#endif // MONITORS_H