#ifndef __C_NET_SERVER__
#define __C_NET_SERVER__
void str_echo(int sockfd);
void create_echo_server(int port, void (*proc)(int sockfd));
#endif
