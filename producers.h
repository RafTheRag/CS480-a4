/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#ifndef PRODUCERS_H
#define PRODUCERS_H

#include "tradecrypto.h"
#include "monitor.h"

//This struct holds the data that is used by the individual producers
struct ProducerData{
    unsigned int timeToProduce = 0; //Time it takes to produce coin
    RequestType type; //Type of coin produced
    ProducerConsumerMonitor* broker; //pointer to the broker/monitor which holds the shared data
};

//producer function declaration which is used in two threads but with different data corresponding to either BTC or ETH production
void* producer(void* arg);




#endif // PRODUCERS_H