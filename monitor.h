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
        int capacity = 15;
        std::queue<RequestType> brokerQueue;

        unsigned int inRequestQueue[RequestTypeN] = {0, 0};

        unsigned int produced[RequestTypeN] = {0, 0};

        int totalConsumed = 0;
        
        
        unsigned int numOfTradeRequests = 120;
        unsigned int msForX = 0;
        unsigned int msForY = 0;
        unsigned int msToProduceBTC = 0;
        unsigned int msToProduceETH = 0;
        unsigned int currentCount = 0;
        unsigned int btcCount = 0;

        void insert(RequestType type);
        RequestType remove(RequestType type);

};


#endif // MONITORS_H