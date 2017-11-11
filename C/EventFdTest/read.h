#ifndef __EventFdTest_H_
#define __EventFdTest_H_

#include <stdint.h>

struct Reader {
    uint64_t id;
    int eventFd;
    int epfd;
};

struct Reader* readerInit(int id);

void readerListen(struct Reader* r);
#endif
