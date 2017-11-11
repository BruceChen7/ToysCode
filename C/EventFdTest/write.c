#include "write.h"
#include <stdlib.h>

struct Writer* initWriter(int clients, int* clientEventFd,  int writerId) {
    struct Writer* obj =  (struct Writer *)(malloc(sizeof(*obj)));
    obj->id = writerId;
    obj->kClients = clients;
    obj->clientEventFd= (int *)(malloc(sizeof(int) * clients));

    for(int i = 0 ; i < clients; i++) {
        obj->clientEventFd[i] = clientEventFd[i];
    }
    return obj;
}
