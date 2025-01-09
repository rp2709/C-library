#include "HoarMonitorBase.h"

void hoar_monitor_base_init(hoar_monitor_base *mb) {
    sem_init(&mb->signaled, 0, 0);
    sem_init(&mb->mutex, 0, 1);
    mb->nbSignaled = 0;
}

void hoar_monitor_condition_init(hoar_monitor_condition *cond) {
    sem_init(&cond->waitingSem, 0, 0);
    cond->nbWaiting = 0;
}

void hoar_wait(hoar_monitor_base *mb, hoar_monitor_condition *cond) {
    cond->nbWaiting++;
    if (mb->nbSignaled > 0)
        sem_post(&mb->signaled);
    else
        sem_post(&mb->mutex);

    sem_wait(&cond->waitingSem);
    cond->nbWaiting--;
}

void hoar_signal(hoar_monitor_base *mb, hoar_monitor_condition *cond) {
    if (cond->nbWaiting == 0)
        return;

    mb->nbSignaled++;
    sem_post(&cond->waitingSem);
    sem_wait(&mb->signaled);
    mb->nbSignaled--;
}

void hoar_in(hoar_monitor_base *mb) {
    sem_wait(&mb->mutex);
}
void hoar_out(hoar_monitor_base *mb) {
    if (mb->nbSignaled > 0) {
        sem_post(&mb->signaled);
    }else {
        sem_post(&mb->mutex);
    }
}