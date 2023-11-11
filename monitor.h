#ifndef MONITORS_H
#define MONITORS_H

#include "tradecrypto.h"  // Include the necessary structures

typedef struct {
    pthread_mutex_t mutex;          // Mutex for protecting critical sections
    pthread_cond_t unconsumed;      // Condition variable for signaling unconsumed items
    pthread_cond_t availableSlots;   // Condition variable for signaling available slots
    BufferADT buffer;   
} ProducerConsumerMonitor;


#endif // MONITORS_H