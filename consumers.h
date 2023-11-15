/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
#ifndef CONSUMERS_H
#define CONSUMERS_H
#include <pthread.h>
#include "tradecrypto.h"
#include "monitor.h"

struct ConsumerData{
    unsigned int timeToConsume = 0;
    unsigned int blockChainConsumed[RequestTypeN] = {0, 0};
    ConsumerType type;
    ProducerConsumerMonitor* broker;
};

void* consumer(void* arg);


#endif // CONSUMERS_H