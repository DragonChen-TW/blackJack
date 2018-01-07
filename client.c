#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "card.h"

#define PORT 8080

int connectServer(){
  int server = socket(AF_INET,SOCK_STREAM,0);

  if(server == -1)
    printf("Build a server fail.\n");

  // setting
  struct sockaddr_in clientInfo;
  memset(&clientInfo,0,sizeof(clientInfo));
  clientInfo.sin_family = AF_INET;

  // IP address
  clientInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
  clientInfo.sin_port = htons(PORT);

  // connect
  int err = connect(server,(struct sockaddr *)&clientInfo,sizeof(clientInfo));
  if(err == -1)
    printf("Connect serverSocket fail.\n");

  return server;
}

int main(int argc, char const *argv[]) {
  // build a socket
  int serverSocket;

  serverSocket = connectServer();


  // start the game
  // refrence how to use function
  // recv(serverSocket,msg,sizeof(msg),0);
  // send(serverSocket,msg,sizeof(msg),0);

  char get[16];
  recv(serverSocket,get,sizeof(get),0);
  printf("%c %d %c %d \n",get[0],get[1],get[2],get[3]);

  close(serverSocket);

  return 0;
}
