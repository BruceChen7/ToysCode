#include "echo_server/echo_client.h"

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void str_client(FILE* fp, int sockfd) {
    char sendline[512];
    char recvline[512];

    while (fgets(sendline, 512, fp) != NULL) {
        if (write(sockfd, sendline, sizeof(sendline)) == -1) {
            fputs("can't send line to server", stdout);
        }

        if (read(sockfd, recvline, sizeof(recvline)) == 0) {
            fputs("server exit prematurely", stdout);
        }

        fputs(recvline, stdout);
    }
}

int connect_to_server(char* ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        fprintf(stdout, "can't create socket %s\n", strerror(errno));
    }
    // Init the server_addr
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // Set port number
    server_addr.sin_port = htons(port);
    // Convert IP address string to binary form
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) != 1) {
        fprintf(stdout, "can't convert ip address %s", strerror(errno));
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
        -1) {
        fprintf(stdout, "can't connect server %s", strerror(errno));
        return -1;
    }

    return sockfd;
}

struct connectAsyncContext* createConnectAsyncContext(
    const char* host, int port, OnConnectSuccessFn* success_fn,
    OnConnectFailFn* fail_fn, AfterConnectSuccessFn* after_success_fn) {
    struct connectAsyncContext* ctx =
        (struct connectAsyncContext*)(malloc(sizeof(*ctx)));
    if (!ctx) {
        return NULL;
    }

    ctx->fd = -1;
    ctx->server_ip = host;
    ctx->server_port = port;
    ctx->after_sucess_fn = after_success_fn;
    ctx->success_fn = success_fn;
    ctx->fail_fn = fail_fn;
    return ctx;
}

static int32_t setSocketNonBlocking(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFD)) == -1) {
        fprintf(stdout, "fcntl error, error %s ", strerror(errno));
        return -1;
    }
    flag |= O_NONBLOCK;
    if (fcntl(fd, F_SETFD, flag) == -1) {
        fprintf(stdout, "fcntl error, error %s", strerror(errno));
        return -1;
    }
    return 0;
}

//=====================================================================
// 检查当前socket的错误
//=====================================================================

static bool getCurrentSocketError(struct connectAsyncContext* context) {
    int err = 0;
    socklen_t errlen = sizeof(err);
    if (getsockopt(context->fd, SOL_SOCKET, SO_ERROR, &err, &errlen) == -1) {
        puts("getsocketopt error");
        return false;
    }

    if (err) {
        errno = err;
        return false;
    }
    return true;
}

bool static connectWaitReady(struct connectAsyncContext* context,
                             int32_t time_in_ms) {
    struct pollfd wfd[1];
    wfd[0].fd = context->fd;
    wfd[0].events = POLLOUT;

    if (errno == EINPROGRESS) {
        int res;
        if ((res = poll(wfd, 1, time_in_ms)) == -1) {
            puts("poll error");
            close(context->fd);
            return false;
        } else if (res == 0) {
            puts("time out");
            close(context->fd);
            return false;
        }
    }
    return false;
}

bool connectToServerAsync(struct connectAsyncContext* context) {
    struct addrinfo hint;
    hint.ai_family = AF_INET;
    hint.ai_protocol = 0;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    char port_in_str[6];
    memset(port_in_str, 0, sizeof(port_in_str));
    snprintf(port_in_str, 6, "%d", context->server_port);

    struct addrinfo *server_info, *p;
    if (getaddrinfo(context->server_ip, port_in_str, &hint, &server_info) ==
        -1) {
        puts("getaddrinfo error");
        return false;
    }
    for (p = server_info; p != NULL; p = p->ai_next) {
        int32_t s = 0;
        if ((s = socket(p->ai_family, p->ai_socktype, p->ai_protocol) == -1)) {
            continue;
        }
        context->fd = s;
        if (setSocketNonBlocking(context->fd) != 0) {
            puts("setSocketNonBlocking error");
            return false;
        }

        if (context->reuse_addr) {
            int32_t n = 1;
            if (setsockopt(context->fd, SOL_SOCKET, SO_REUSEADDR, (char*)&n,
                           sizeof(n)) < 0) {
                puts("setsockopt errro");
                return false;
            }
            return false;
        }

        if (connect(context->fd, p->ai_addr, p->ai_addrlen) == -1) {
            if (errno == EHOSTUNREACH) {
                close(context->fd);
                puts("connect errror");
                continue;
            } else if (errno == EINPROGRESS && context->reuse_addr) {
                // OK
            } else if (errno == EADDRNOTAVAIL && context->reuse_addr) {
                // 这里应该重试
            } else {  // 等待连接超时
                if (connectWaitReady(context, context->connect_time_out)) {
                }
            }
        }
        return false;
    }
    return true;
}
