#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "game.h"

// init
Card drawOneCard(Card cards[52],int *all_len){
  // choose one location
	int temp = rand() & *all_len;
	Card res = cards[temp];
  // change the last one card to this location
	cards[temp] = cards[*all_len - 1];

	*all_len -= 1;

	return res;
}
void initPlayer(Card cards[52],int *all_len,Card player[4][5],int p_len[4]){
	srand(time(NULL));
  // setting all cards
	createAllCard(cards);
	*all_len = 52;

  // draw to each player
	for(int i = 0;i < 2;++i){
		player[i][0] = drawOneCard(cards,all_len);
		player[i][1] = drawOneCard(cards,all_len);
		p_len[i] = 2;
	}
	printf("%d\n",*all_len);
}
