#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "card.h"
#include "game.h"

#define PORT 8080
#define PLAYER_NUM 2

int setServer(int *s_socket,int *info_len){
  // build server_socket

  *s_socket = socket(PF_INET,SOCK_STREAM,0);
  if(*s_socket == -1)
    printf("Build a server_socket fail.\n");

  // setting
  struct sockaddr_in serverInfo;
  *info_len = sizeof(serverInfo);

  memset(&serverInfo,0,sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(PORT);

  // reuse Address
  setsockopt(*s_socket,SOL_SOCKET,SO_REUSEADDR,info_len,sizeof(*info_len));

  // bind and listen
  int temp;
  temp = bind(*s_socket,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
  if(temp == -1)
    printf("bind server_socket Fail.\n");
  temp = listen(*s_socket,4);
  if(temp == -1)
    printf("listen server_socket fail.\n");

  printf("-----Server is listening-----\n");
}
void waitClients(int server_socket,int info_len,int clients[4]){
  struct sockaddr_storage clientInfo;
  char clientIP[16];

  int i;
  for(i = 0;i < 2;++i){
    clients[i] = accept(server_socket,(struct sockaddr *)&clientInfo,&info_len);

    printf("Accepted player %d from %s.\n",i + 1,
    inet_ntop(clientInfo.ss_family,&(((struct sockaddr_in *)&clientInfo))->sin_addr,clientIP, 16));
  }
}
void initSend(int clients[4],Card player[4][5]){
  char msg[16];
  for(int i = 0;i < PLAYER_NUM;++i){
    msg[0] = player[i][0].flow;
    msg[1] = player[i][0].point;
    msg[2] = player[i][1].flow;
    msg[3] = player[i][1].point;

    send(clients[i],msg,sizeof(msg),0);
  }
}

void startGame(int clients[4],Card player[4][5],Card all_cards[52],int *all_len,int p_len[4],int point[4]){
	char msg[16];
	char option[2];
	for(int i = 0;i < PLAYER_NUM;i++){
    // send tha start msg to client
    strcpy(msg,"start");
		send(clients[i],msg,sizeof(msg),0);

    // game loop
    while(1){
      // get client's option
			recv(clients[i],option,sizeof(option),0);
			printf("%d: %s\n",clients[i],option);

			if(strcmp(option,"1") == 0){
        // give player one card
				player[i][p_len[i]] = drawOneCard(all_cards,all_len);
				msg[0] = player[i][p_len[i]].flow;
				msg[1] = player[i][p_len[i]].point;
        // send to client
				send(clients[i],msg,sizeof(msg),0);
				p_len[i]++;

        // count the point
				point[i] = calPoint(player[i],p_len[i]);
				if(point[i] > 21){
          break;
        }
			}
			else if(strcmp(option,"2")==0){
				point[i] = calPoint(player[i],p_len[i]);
				break;
			}
		}
	}
}

void findWinner(int clients[4],int point[4]){
  char results[4][16];
  int max = 0, count = 0;
  // find those boom and max
  for(int i = 0;i < PLAYER_NUM;++i){
    if(point[i] > 21)strcpy(results[i],"Lose");
    else if(point[i] > max)max = point[i];
  }
  // count how many winner
  for(int i = 0;i < PLAYER_NUM;++i){
    if(point[i] == max)++count;
  }

  if(count == PLAYER_NUM){
    for(int i = 0;i < PLAYER_NUM;++i){
      strcpy(results[i],"Draw");
    }
  }
  else{
    for(int i = 0;i < PLAYER_NUM;++i){
      if(point[i] == max)strcpy(results[i],"Win");
      else strcpy(results[i],"Lose");
    }
  }

  // sned these out
  for(int i = 0;i < PLAYER_NUM;++i){
    send(clients[i],results[i],sizeof(results[i]),0);
  }
}

int main(int argc, char const *argv[]) {
  // build a socket
  int server_socket, client_sockets[4];
  int info_len;

  setServer(&server_socket,&info_len);
  waitClients(server_socket,info_len,client_sockets);


  // init all cards
  Card all_cards[52], player[4][5];
  int all_len, player_len[4], max;
  int total_point[4];

  initPlayer(all_cards,&all_len,player,player_len);
  initSend(client_sockets,player);
  startGame(client_sockets,player,all_cards,&all_len,player_len,total_point);
  findWinner(client_sockets,total_point);


  close(server_socket);

  return 0;
}
