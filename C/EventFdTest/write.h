#ifndef __EVENT_FD_TEST_WRITE_H_
#define __EVENT_FD_TEST_WRITE_H_
#include <stdint.h>
#include "read.h"

struct Writer {
    uint64_t id;
    // num of clients;
    int kClients;
    int* clientEventFd;
};

struct Writer* initWriter(int clients, int* clientEventFd,  int writerId);

int sendMsg(const char* msg, uint64_t client);
#endif
