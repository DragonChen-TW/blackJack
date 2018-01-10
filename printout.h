#ifndef printout_h
#define printout_h

#define CARD_WIDTH 2.6
#define CARD_HEIGHT 4.4
#define CARD_SPACE 0.2

void loadCard(Card temp_card,int card_i);
int initGraphic();
void startGraphic();

void text(float,float,int);
void WindowSize(int , int );            //負責視窗及繪圖內容的比例
void Keyboard(unsigned char , int, int );   //獲取鍵盤輸入
void Display(void);                     //描繪
void Mouse(int ,int ,int ,int);
int Check(int,int );
void courage(int);

#endif
