#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "server.h"

void create_echo_server(int port, void (*proc)(int sockfd)) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    int accept_fd;

    if (listen_fd == -1) {
        fprintf(stdout, "can't create socket: %s \n", strerror(errno));
        return;
    }
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) ==
        -1) {
        fprintf(stdout, "can't bind socket: %s \n", strerror(errno));
        return;
    }

    if ((listen(listen_fd, 5)) == -1) {
        fprintf(stdout, "can't bind socket: %s \n", strerror(errno));
        return;
    }

    for (;;) {
        socklen_t client_len = sizeof(client_addr);
        accept_fd =
            accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        int child_pid = 0;  // Child process

        if ((child_pid = fork()) == 0) {
            close(listen_fd);
            proc(accept_fd);
            exit(0);
        }

        // Parent proccess;
        close(accept_fd);
    }
}

void str_echo(int sockfd) {
    ssize_t n;
    char buf[512];
again:
    while ((n = read(sockfd, buf, sizeof(buf))) > 0) {
        if (write(sockfd, buf, n) == -1) {
            fprintf(stdout, "str_echo : write error\n");
        }
    }

    if (n < 0 && errno == EINTR) {
        goto again;
    } else {
        fprintf(stdout, "str_echo : read error\n");
    }
}
