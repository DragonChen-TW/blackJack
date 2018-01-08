#ifndef game_h
#define game_h

struct Card;
typedef struct Card Card;

// get new card
Card drawOneCard(Card cards[52],int *all_len);

// init
void initPlayer(Card cards[52],int *all_len,Card player[4][5],int p_len[4]);

int calPoint(Card player[5],int p_len);
#endif
