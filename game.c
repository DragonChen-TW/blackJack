#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "game.h"

// init
void initUser(Card cards[52],Card user[4][13]){
	char got[52] = {0};		// using char to simulate bool save some memory
	for(int i = 0;i < 4;++i){
		for(int j = 0;j < 13;++j){
			int loc = rand() % 52;
			while(got[loc])loc = rand() % 52;
			got[loc] = 1;
			user[i][j] = cards[loc];
		}
		sortCards(user[i]);
		// printCardsOld(user[i],13);
	}
}
void initCard(Card cards[52],Card user[4][13]){
	createAllCard(cards);
	initUser(cards,user);
}
