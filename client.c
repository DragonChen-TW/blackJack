#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "card.h"
#include "game.h"
#include "printout.h"

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

int gameLoop(int server,Card hand[5],int *hand_len,int *point,char opt){
  char get[16];
  char option[2];

  if(opt == 'a') strcpy(option,"1");
  else strcpy(option,"2");

  send(server,option,sizeof(option),0);

  if(strcmp(option,"2") == 0)return 0;

  recv(server,get,sizeof(get),0);

  printf("Got new card %c %d\n",get[0],get[1]);
  // server give you a new card !!
  // pick it up !!
	hand[*hand_len] = makeCard(get[0],get[1]);
	*hand_len += 1;

  printHand(hand,hand_len,point);

  if(*point > 21){
    printf("You boom !!\n");
    return 0;
  }

  return 1;
}

void socketSetting(int *server_socket,Card hand[5],int *hand_len) {
  // build a socket
  char ip_address[16];

  // enter ip and connect server
  // printf("Please enter server's IP Address: ");
  // scanf("%s",ip_address);
  strcpy(ip_address,"140.117.178.29");

  *server_socket = connectServer(ip_address);


  // global variable
  *hand_len = 2;

  char get[16];

  // get the very first two cards
  recv(*server_socket,get,sizeof(get),0);
  hand[0] = makeCard(get[0],get[1]);
  hand[1] = makeCard(get[2],get[3]);

  // init graphic
  loadCard(hand[0],0);
  loadCard(hand[1],1);
}

void result(char get[16],int server_socket, Card hand[5], int *hand_len,int *point){
  // counting the result
  recv(server_socket,get,sizeof(temp),0);
  printHand(hand,hand_len,point);
  printf("Result: %s\n",get);

  close(server_socket);
}
