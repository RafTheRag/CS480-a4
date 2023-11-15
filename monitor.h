#ifndef MONITORS_H
#define MONITORS_H

#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include "tradecrypto.h"  // Include the necessary structures
class ProducerConsumerMonitor{
    public:
        sem_t barrierSem;
        pthread_mutex_t queueMutex;          // Mutex for protecting critical sections
        pthread_cond_t notEmpty;      // Condition variable for signaling unconsumed items
        pthread_cond_t notFull;   // Condition variable for signaling available slots
        pthread_cond_t BTCNotFull;
        long unsigned int capacity = 15;
        std::queue<RequestType> brokerQueue;

        unsigned int inRequestQueue[RequestTypeN] = {0, 0};

        unsigned int produced[RequestTypeN] = {0, 0};
        
        
        unsigned int numOfTradeRequests = 120;

        void insert(RequestType type);
        RequestType remove(RequestType type);

};


#endif // MONITORS_H