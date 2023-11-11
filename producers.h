#ifndef PRODUCERS_H
#define PRODUCERS_H


// Function declaration for bitcoin producer thread
void* bitcoin_producer(void* arg);

// // Function declaration for ethereum producer thread
void* ethereum_producer(void* arg);

#endif // PRODUCERS_H