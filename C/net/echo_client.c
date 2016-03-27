#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
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
        fprintf(stdout, "can't create socket %s", strerror(errno));
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

    if (connect(socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        fprintf(stdout, "can't connect server %s", strerror(errno));
        return -1;
    } 
    return sockfd;
}

