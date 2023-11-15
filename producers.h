#ifndef PRODUCERS_H
#define PRODUCERS_H

#include "tradecrypto.h"
#include "monitor.h"

struct ProducerData{
    unsigned int timeToProduce = 0;
    RequestType type;
    ProducerConsumerMonitor* broker;
};

// Function declaration for bitcoin producer thread
void* producer(void* arg);




#endif // PRODUCERS_H