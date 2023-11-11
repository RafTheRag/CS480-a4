#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "tradecrypto.h"
#include "consumers.h"
#include "monitor.h"

void* blockchain_x_consumer(void* arg) {
    // Blockchain X consumer logic
    // ...
    


    pthread_exit(NULL);
}

void* blockchain_y_consumer(void* arg) {
    // Blockchain Y consumer logic
    // ...

    pthread_exit(NULL);
}

