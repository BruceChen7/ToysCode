#ifndef ECHO_SERVER_ECHO_CLIENT_H
#define ECHO_SERVER_ECHO_CLIENT_H
#include <stdint.h>
#include <stdio.h>

void str_client(FILE* fp, int socket);

int connect_to_server(char* ip, int port);

//=====================================================================
// 异步连接的上下文
//=====================================================================
struct connectAsyncContext;

typedef void (*OnConnectSuccessFn)(connectAsyncContext* ctx);
typedef void (*OnConnectFailFn)(connectAsyncContext* ctx, int error);
typedef void (*AfterConnectSuccessFn)(connectAsyncContext* ctx, void* data);

struct connectAsyncContext {
    int fd;
    const char* server_ip;
    int server_port;
    OnConnectSuccessFn* success_fn;
    OnConnectFailFn* fail_fn;
    AfterConnectSuccessFn* after_sucess_fn;
};

connectAsyncContext* createConnectAsyncContext(const char* host, int port);
int connectToServerAsync(connectAsyncContext* ctx);

#endif
