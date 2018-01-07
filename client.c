#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "card.h"

#define PORT 8080

int main(int argc, char const *argv[]) {
  // build a socket
  int clientSocket;
  clientSocket = socket(AF_INET,SOCK_STREAM,0);

  if(clientSocket == -1)
    printf("Build a clientSocket fail.\n");

  // setting
  struct sockaddr_in clientInfo;
  memset(&clientInfo,0,sizeof(clientInfo));
  clientInfo.sin_family = AF_INET;

  // IP address
  clientInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
  clientInfo.sin_port = htons(PORT);

  // connect
  int err = connect(clientSocket,(struct sockaddr *)&clientInfo,sizeof(clientInfo));
  if(err == -1)
    printf("Connect serverSocket fail.\n");

  char msg[100] = "There is client", input[100];

  // recv(clientSocket,input,sizeof(input),0);
  // printf("%s\n",input);

  char get[16];
  recv(clientSocket,get,sizeof(get),0);
  printf("%c %d %c %d \n",get[0],get[1],get[2],get[3]);

  close(clientSocket);

  return 0;
}
