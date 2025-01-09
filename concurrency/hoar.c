#include "HoarMonitorBase.h"

/*
 * This is meant as a small exemple of how to use the base hoar monitor class
 * Say have a server with some threads receiving some connection ( symbolised by their client's IP ),
 * And other threads treat them.
 * This is a typical productor-consumer problem
 */

struct clientQueue {
    hoar_monitor_base base;
    hoar_monitor_condition full, empty;
    unsigned nbProdWaiting, nbConsWaiting;

#define MAX_NB_ELEMENTS 100
    unsigned buffer[MAX_NB_ELEMENTS];
    unsigned writeIndex,readIndex;
    unsigned nbElements;
};

void put(struct clientQueue* cq, unsigned ip) {
    hoar_in(&cq->base);

    if (cq->nbElements == MAX_NB_ELEMENTS)
        hoar_wait(&cq->base,&cq->full);

    cq->nbElements++;
    cq->buffer[cq->writeIndex] = ip;
    cq->writeIndex = (cq->writeIndex + 1) % MAX_NB_ELEMENTS;

    hoar_signal(&cq->base,&cq->empty);

    hoar_out(&cq->base);
}

unsigned get(struct clientQueue* cq) {
    hoar_in(&cq->base);

    if (cq->nbElements == 0)
        hoar_wait(&cq->base,&cq->empty);

    cq->nbElements--;
    unsigned ip = cq->buffer[cq->readIndex];
    cq->readIndex = (cq->readIndex + 1) % MAX_NB_ELEMENTS;

    hoar_signal(&cq->base,&cq->full);

    hoar_out(&cq->base);
    return ip;
}