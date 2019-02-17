#include "mutex.h"
#include "toys_utils.h"

void
pthreadInit(pthread_mutex_t* mutex) {
    systemCall(pthread_mutex_init(mutex, NULL), "pthread_mutex_init called error");
}

void
pthreadLock(pthread_mutex_t* mutex) {
    systemCall(pthread_mutex_lock(mutex), "pthread_mutex_lock called error");
}

void
pthreadUnLock(pthread_mutex_t* mutex) {
    systemCall(pthread_mutex_unlock(mutex), "pthread_mutex_unlock called error");
}
