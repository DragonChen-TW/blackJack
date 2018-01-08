#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "card.h"
#include "game.h"

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
  Card hand[5];
  char option[2];
  int index = 2;
  int point;

  recv(serverSocket,get,sizeof(get),0);
  hand[0] = makeCard(get[0],get[1]);
  hand[1] = makeCard(get[2],get[3]);
  printf("%c %d %c %d \n",hand[0].flow,hand[0].point,hand[1].flow,hand[1].point);
  
  //recv(serverSocket,get,sizeof(get),0);
  //printf("start: %s\n",get);
  
  while(1){
  	recv(serverSocket,get,sizeof(get),0);
  	//printf("start: %s\n",get);
  	
  	if(strcmp(get,"start")!=0){
	  	hand[index] = makeCard(get[0],get[1]);
	  	printf("New card: %c %d\n",hand[index].flow,hand[index].point);
	  	index++;
	  	
	  	point = calPoint(hand,index);
	  	printf("point: %d\n",point);
	  	if(point>21){
	  		printf("You boom!\n");
	  		break;
	  	}
  	}
  	
  	printf("Please enter a option\n");
  	printf("(1) Draw one card\n");
  	printf("(2) Stop\n");
  	scanf("%s",option);
  	send(serverSocket,option,sizeof(option),0);
  	
  	
  	if(strcmp(option,"2")==0) break;
  }
  printCardsOld(hand,index);
  point = calPoint(hand,index);
  recv(serverSocket,get,sizeof(get),0);
  printf("point: %d\n",point);
  printf("Result: %s\n",get);

  close(serverSocket);

  return 0;
}
