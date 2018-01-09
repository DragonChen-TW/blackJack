#ifndef printout_h
#define printout_h
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>//使用DevC++的話要改為標入 #include <GL\openglut.h>
#include "card.h"
#define CARD_WIDTH 1.3
#define CARD_HEIGHT 4.4
#define CARD_SPACE 0.2

int printout();
void WindowSize(int , int );            //負責視窗及繪圖內容的比例
void Keyboard(unsigned char , int, int );   //獲取鍵盤輸入
void Display(void);                     //描繪
void Mouse(int ,int ,int ,int);
int Check(int,int );

#endif
