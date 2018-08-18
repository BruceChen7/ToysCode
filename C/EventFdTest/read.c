#include "read.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>

struct Reader* readerInit(int id) {
    struct Reader* r = (struct Reader*)(malloc(sizeof(*r)));
    r->id = id;
    r->eventFd = eventfd(0, EFD_NONBLOCK);
    r->epfd = epoll_create(5);

    struct epoll_event data;
    data.events = EPOLLIN;

    if (r->epfd != -1) {
        epoll_ctl(r->epfd, EPOLL_CTL_ADD, r->eventFd, &data);
    }

    if (r->eventFd == -1 || r->epfd == -1) {
        return NULL;
    } else {
        return r;
    }
}

void readerListen(struct Reader* r) {
    int ep_fd = r->epfd;
    struct epoll_event event;

    while (1) {
        int num_events = epoll_wait(ep_fd, &event, 1, -1);

        if (num_events == 1) {
            char buf[512];
            int nbytes = read(r->eventFd, buf, sizeof(buf));

            if (nbytes >= 1) {
                printf("readThread#%d get message %s\n", (int)r->id, buf);
            }
        }
    }
}
