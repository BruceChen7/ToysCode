#ifndef __BASE_MUTEX_H__
#define __BASE_MUTEX_H__
#include <pthread.h>

void pthreadInit(pthread_mutex_t* mutex);

void pthreadLock(pthread_mutex_t* mutex);

void pthreadUnLock(pthread_mutex_t* mutex);



#endif
