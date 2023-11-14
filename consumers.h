/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
#ifndef CONSUMERS_H
#define CONSUMERS_H
#include <pthread.h>
#include "report.h"

void* blockchain_x_consumer(void* arg);

void* blockchain_y_consumer(void* arg);

#endif // CONSUMERS_H