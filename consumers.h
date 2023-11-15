/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#ifndef CONSUMERS_H
#define CONSUMERS_H
#include <pthread.h>
#include "tradecrypto.h"
#include "monitor.h"

//This struct holds the data that is used by the individual blockchains
struct ConsumerData{
    unsigned int timeToConsume = 0; //How long it takes the blockchain to consume
    unsigned int blockChainConsumed[RequestTypeN] = {0, 0}; //An array that keeps track of how much BTC & ETH the blockchain has consumed
    ConsumerType type; //What type of blockchain
    ProducerConsumerMonitor* broker; //pointer to the broker/monitor which holds the shared data
};

//consumer function declaration which is used in two threads but with different data corresponding to either blockchain X or Y consumption
void* consumer(void* arg);


#endif