#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "card.h"
#include "game.h"

#define PORT 8080

int connectServer(char IP[16]){
  int server = socket(AF_INET,SOCK_STREAM,0);

  if(server == -1)
    printf("Build a server fail.\n");

  // setting
  struct sockaddr_in clientInfo;
  memset(&clientInfo,0,sizeof(clientInfo));
  clientInfo.sin_family = AF_INET;

  // IP address
  clientInfo.sin_addr.s_addr = inet_addr(IP);
  clientInfo.sin_port = htons(PORT);

  // connect
  int err = connect(server,(struct sockaddr *)&clientInfo,sizeof(clientInfo));
  if(err == -1)
    printf("Connect server_socket fail.\n");

  return server;
}

void printHand(Card hand[5],int *hand_len,int *point){
  system("clear");
  printCardsOld(hand,*hand_len);
  // print point
  *point = calPoint(hand,*hand_len);
  printf("Point: %d\n",*point);
}

void gameLoop(int server,Card hand[5],int *hand_len,int *point){
  char get[16];
  char option[2];

  printHand(hand,hand_len,point);

  // receive each round msg from server
  recv(server,get,sizeof(get),0);

  while(1){
    printf("Please enter a option\n");
    printf("(1) Draw one card\n");
    printf("(2) Stop\n");

    scanf("%s",option);
    send(server,option,sizeof(option),0);

    if(strcmp(option,"2") == 0)break;

    recv(server,get,sizeof(get),0);

    // server give you a new card !!
    // pick it up !!
  	hand[*hand_len] = makeCard(get[0],get[1]);
  	*hand_len += 1;

    printHand(hand,hand_len,point);

    if(*point > 21){
      printf("You boom !!\n");
      break;
    }
  }
}

int main(int argc, char const *argv[]) {
  // build a socket
  int server_socket;
  char ip_address[16];

  // enter ip and connect server
  printf("Please enter server's IP Address: ");
  scanf("%s",ip_address);
  strcpy(ip_address,"140.117.178.29");

  server_socket = connectServer(ip_address);


  // global variable
  Card hand[5];
  int hand_len = 2, point;
  char get[16];

  // get the very first two cards
  recv(server_socket,get,sizeof(get),0);
  hand[0] = makeCard(get[0],get[1]);
  hand[1] = makeCard(get[2],get[3]);

  // the game loop
  gameLoop(server_socket,hand,&hand_len,&point);

  // counting the result
  printHand(hand,&hand_len,&point);
  recv(server_socket,get,sizeof(get),0);
  printf("point: %d\n",point);
  printf("Result: %s\n",get);

  close(server_socket);

  return 0;
}
