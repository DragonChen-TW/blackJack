#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "card.h"
#include "game.h"

#define PORT 8080

int setServer(int *s_socket,int *infoLen){
  // build serverSocket
  *s_socket = socket(PF_INET,SOCK_STREAM,0);

  // setting
  struct sockaddr_in serverInfo;
  *infoLen = sizeof(serverInfo);

  memset(&serverInfo,0,sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(PORT);

  // bind and listen
  bind(*s_socket,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
  listen(*s_socket,4);

  printf("-----Server is listening-----\n");
}
void waitClients(int serverSocket,int infoLen,int clients[4]){
  struct sockaddr_storage clientInfo;
  char clientIP[16];

  int i;
  for(i = 0;i < 2;++i){
    clients[i] = accept(serverSocket,(struct sockaddr *)&clientInfo,&infoLen);

    printf("Accepted player %d from %s.\n",i + 1,
    inet_ntop(clientInfo.ss_family,&(((struct sockaddr_in *)&clientInfo))->sin_addr,clientIP, 16));
  }
}
void initSend(int clients[4],Card player[4][5]){
  char msg[16];
  for(int i = 0;i < 2;++i){
    msg[0] = player[i][0].flow;
    msg[1] = player[i][0].point;
    msg[2] = player[i][1].flow;
    msg[3] = player[i][1].point;

    send(clients[i],msg,sizeof(msg),0);
  }
}

int main(int argc, char const *argv[]) {
  // build a socket
  int serverSocket, clientSockets[4];
  int infoLen;


  setServer(&serverSocket,&infoLen);
  waitClients(serverSocket,infoLen,clientSockets);

// recv(clients[0],input,sizeof(input),0);
// send(clientSocket,msg,sizeof(msg),0);


  Card all_cards[52], player[4][5];
  int all_len, player_len[4], max;

  initPlayer(all_cards,&all_len,player,player_len);
  initSend(clientSockets,player);

  // sendCardToClient(clientSockets,player);
  //
  // char msg[32] = {0};
  //
  // printf("%c %d \n",player[0][0].flow,player[0][0].point);
  // msg[0] = player[0][0].flow;
  // msg[1] = player[0][0].point;
  // send(clientSockets[0],msg,sizeof(msg),0);
  //
  // sleep(1);

  // printf("%c %d \n",player[1][0].flow,player[1][0].point);
  // msg[0] = player[1][0].flow;
  // msg[1] = player[1][0].point;
  // send(clientSockets[1],msg,sizeof(msg),0);


  return 0;
}
