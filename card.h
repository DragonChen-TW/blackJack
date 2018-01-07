#ifndef card_h
#define card_h

struct Card{
	char flow; // 'S' 'H' 'D' 'C'
	int point;
};
typedef struct Card Card;

// functional tool
Card makeCard(char f, int p);
// cards
void createAllCard(Card cards[52]);
void printCardsOld(Card cards[52],int len);

#endif
