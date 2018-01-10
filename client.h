#ifndef CLIENT_H
#define CLIENT_H


int connectServer(char IP[16]);
void printHand(Card hand[5],int *hand_len,int *point);
int gameLoop(int server,Card hand[5],int *hand_len,int *point,char opt);
void socketSetting(int *server_socket,Card hand[5],int *hand_len);
void result(char get[16],int server_socket, Card hand[5], int *hand_len,int *point);


#endif
