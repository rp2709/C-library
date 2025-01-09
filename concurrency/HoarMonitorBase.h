#ifndef HOARMONITORBASE_H
#define HOARMONITORBASE_H

#include "semaphore.h"

struct hoar_monitor_base {
    sem_t signaled;
    sem_t mutex;
    unsigned nbSignaled;
};
typedef struct hoar_monitor_base hoar_monitor_base;

void hoar_monitor_base_init(hoar_monitor_base *mb);


struct hoar_monitor_condition {
    sem_t waitingSem;
    unsigned nbWaiting;
};
typedef struct hoar_monitor_condition hoar_monitor_condition;

void hoar_monitor_condition_init(hoar_monitor_condition *cond);

void hoar_wait(hoar_monitor_base *mb, hoar_monitor_condition *cond);
void hoar_signal(hoar_monitor_base *mb, hoar_monitor_condition *cond);

void hoar_in(hoar_monitor_base *mb);
void hoar_out(hoar_monitor_base *mb);

#endif //HOARMONITORBASE_H
