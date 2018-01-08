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
  if(*s_socket == -1)
    printf("Build a serverSocket fail.\n");

  // setting
  struct sockaddr_in serverInfo;
  *infoLen = sizeof(serverInfo);

  memset(&serverInfo,0,sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(PORT);

  // bind and listen
  int temp;
  temp = bind(*s_socket,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
  if(temp == -1)
    printf("bind serverSocket Fail.\n");
  temp = listen(*s_socket,4);
  if(temp == -1)
    printf("listen serverSocket fail.\n");

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
  //struct ServerMsg *sendMsg;
  for(int i = 0;i < 2;++i){
    msg[0] = player[i][0].flow;
    msg[1] = player[i][0].point;
    msg[2] = player[i][1].flow;
    msg[3] = player[i][1].point;
    /*sendMsg->playerId = i;
    sendMsg->msg[0] = player[i][0].flow;
    sendMsg->msg[1] = player[i][0].point;
    sendMsg->msg[2] = player[i][1].flow;
    sendMsg->msg[3] = player[i][1].point;*/

    send(clients[i],msg,sizeof(msg),0);
    //send(clients[i],sendMsg,sizeof(sendMsg),0);
  }
}

void startGame(int clients[4],Card player[4][5],Card all_cards[52],int *all_len,int p_len[4],int point[4]){
	char msg[16];
	char option[2];
	for(int i=0;i<2;i++){
  		strcpy(msg,"start");
  		send(clients[i],msg,sizeof(msg),0);
  		while(1){
  			recv(clients[i],option,sizeof(option),0);
  			printf("%d: %s\n",clients[i],option);
  			if(strcmp(option,"1")==0){
  				player[i][p_len[i]] = drawOneCard(all_cards,all_len);
  				msg[0] = player[i][p_len[i]].flow;
  				msg[1] = player[i][p_len[i]].point;
  				send(clients[i],msg,sizeof(msg),0);
  				p_len[i]++;
  				
  				point[i] = calPoint(player[i],p_len[i]);
  				if(point[i]>21) break;
  				
  			}
  			else if(strcmp(option,"2")==0){
  				point[i] = calPoint(player[i],p_len[i]);
  				break;
  			}
  			else{
  				
  			}
  		}
  	}
  	int max = 0;
  	int playerId;
  	for(int i=0;i<2;i++){
  		if(point[i]>max && point[i]<=21){
  			max = point[i];
  			playerId = i;
  		}
  	}
  	for(int i=0;i<2;i++){
  		if(i==playerId) strcpy(msg,"Win");
  		else strcpy(msg,"Lose");
  		send(clients[i],msg,sizeof(msg),0);
  	}
}

int main(int argc, char const *argv[]) {
  // build a socket
  int serverSocket, clientSockets[4];
  int infoLen;
  int totalPoint[4];

  setServer(&serverSocket,&infoLen);
  waitClients(serverSocket,infoLen,clientSockets);


  // init all cards
  Card all_cards[52], player[4][5];
  int all_len, player_len[4], max;

  initPlayer(all_cards,&all_len,player,player_len);
  initSend(clientSockets,player);
  startGame(clientSockets,player,all_cards,&all_len,player_len,totalPoint);


  // start the game
  char msg[16];
  // refrence how to use function
  // recv(clientSockets[0],,sizeof(msg),0);
  // send(clientSocket[0],msg,sizeof(msg),0);

  close(serverSocket);

  return 0;
}
