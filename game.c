#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "game.h"

// get new card
Card drawOneCard(Card cards[52],int *all_len){
  // choose one location
	int temp = rand() % *all_len;
	Card res = cards[temp];
  // change the last one card to this location
	cards[temp] = cards[*all_len - 1];

	*all_len -= 1;

	return res;
}

// init
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

int calPoint(Card player[5],int p_len){
	int point = 0;
	int ace = 0;
	for(int i=0;i<p_len;i++){
		if(player[i].point==1){
			point += 11;
			ace++;
		}
		else if(player[i].point>10) point += 10;
		else point += player[i].point;
	}
	while(point > 21 && ace > 0){
		--ace;
		point -= 10;
	}
	return point;
}
