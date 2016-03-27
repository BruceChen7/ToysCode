#ifndef __C_NET__
#define __C_NET__

int connect_to_server(char* ip, int port);
void str_client(FILE* fp, int sockfd); 
void str_select_client(FILE* fp, int sockfd);

#endif
