#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "tradecrypto.h"
#include "producers.h"

void* bitcoin_producer(void* arg) {
    // Bitcoin producer logic
    // ...

   pthread_exit(NULL);
}

void* ethereum_producer(void* arg) {
    // Ethereum producer logic
    // ...

    pthread_exit(NULL);
}