#include <stdio.h>
#include "card.h"

// functional tool
Card makeCard(char f, int p){
	Card temp = {.flow = f, .point = p};
	return temp;
}

// cards
void createAllCard(Card cards[52]){
	int i;
	for(i = 0;i < 13;++i)cards[i] = makeCard('S',i % 13 + 1);
	for(i = 13;i < 26;++i)cards[i] = makeCard('H',i % 13 + 1);
	for(i = 26;i < 39;++i)cards[i] = makeCard('D',i % 13 + 1);
	for(i = 39;i < 52;++i)cards[i] = makeCard('C',i % 13 + 1);
}
void printCardsOld(Card cards[52],int len){
	int i;
	for(i = 0;i < len;++i){
    // char version
		if(cards[i].flow == 'S')printf("黑 ");
		else if(cards[i].flow == 'H')printf("紅 ");
		else if(cards[i].flow == 'D')printf("方 ");
		else if(cards[i].flow == 'C')printf("梅 ");
	}
	printf("\n");
	for(i = 0;i < len;++i)printf("%2d ",cards[i].point);
	printf("\n");
}
