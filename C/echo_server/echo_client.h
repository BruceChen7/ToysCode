#ifndef ECHO_SERVER_ECHO_CLIENT_H
#define ECHO_SERVER_ECHO_CLIENT_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void str_client(FILE* fp, int socket);

int connect_to_server(char* ip, int port);

//=====================================================================
// 异步连接的上下文
//=====================================================================
struct connectAsyncContext;

typedef void (*OnConnectSuccessFn)(struct connectAsyncContext* ctx);
typedef void (*OnConnectFailFn)(struct connectAsyncContext* ctx, int error);
typedef void (*AfterConnectSuccessFn)(struct connectAsyncContext* ctx,
                                      void* data);

struct connectAsyncContext {
    int fd;
    const char* server_ip;
    int server_port;
    int32_t connect_time_out;
    bool reuse_addr;
    OnConnectSuccessFn* success_fn;
    OnConnectFailFn* fail_fn;
    AfterConnectSuccessFn* after_sucess_fn;
};

struct connectAsyncContext* createConnectAsyncContext(
    const char* host, int port, OnConnectSuccessFn* success_fn,
    OnConnectFailFn* fail_fn, AfterConnectSuccessFn* fn);

bool connectToServerAsync(struct connectAsyncContext* ctx);

#endif
