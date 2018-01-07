#ifndef game_h
#define game_h

struct Card;
typedef struct Card Card;

// init
void initUser(Card cards[52],Card user[4][13]);
void initCard(Card cards[52],Card user[4][13]);

#endif
