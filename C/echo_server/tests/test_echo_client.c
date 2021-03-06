#include <assert.h>
#include <stdio.h>
#include "echo_server/echo_client.h"
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fputs("usage: ./test_echo_client IPAddress\n", stdout);
        return -1;
    }

    int port = 9877;
    int sockfd = connect_to_server(argv[1], port);
    assert(sockfd != -1);
    str_client(stdin, sockfd);
}
