#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "read.h"
#include "write.h"

#define NUM_READERS 100

struct WriterArgs {
    struct Writer* writer;
};

void* writerThread(void* args) {
    struct WriterArgs* arg = (struct WriterArgs*)(args);

    while (1) {
        struct Writer* w = arg->writer;
        printf("Writer Thread #%d\n", (int)(w->id));
        for (int i = 0; i < w->kClients; i++) {
            const char* msg = "new msg";
            int nbytes = write((int)(w->clientEventFd[i]), msg, sizeof(msg));

            if (nbytes == -1) {
                printf("something error, %s", strerror(errno));
            }
        }
        // 睡眠1s
        sleep(1);
    }

    return NULL;
}

struct ReaderArgs {
    struct Reader* reader;
};

void* readThread(void* args) {
    struct ReaderArgs* arg = (struct ReaderArgs*)(args);
    struct Reader* r = arg->reader;
    readerListen(r);
    return NULL;
}

int main() {
    pthread_t writerId;

    struct ReaderArgs reader_args[NUM_READERS];
    pthread_t reader_id[NUM_READERS];

    int event_fd_list[NUM_READERS];

    // 创建读线程
    for (int i = 0; i < NUM_READERS; i++) {
        reader_args[i].reader = readerInit(i);
        event_fd_list[i] = reader_args[i].reader->eventFd;
        pthread_create(&reader_id[i], NULL, readThread,
                       (void*)(&reader_args[i]));
    }

    struct WriterArgs writer_args;

    // 创建写线程
    writer_args.writer = initWriter(NUM_READERS, event_fd_list, 1);
    pthread_create(&writerId, NULL, writerThread, (void*)(&writer_args));

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_id[i], NULL);
    }

    pthread_join(writerId, NULL);

    return 0;
}
