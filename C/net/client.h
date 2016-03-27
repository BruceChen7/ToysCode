#ifndef __C_NET_CLIENT__
#define __C_NET_CLIENT___

int connect_to_server(char* ip, int port);
void str_client(FILE* fp, int sockfd); 
void str_select_client(FILE* fp, int sockfd);

#endif
