#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>//使用DevC++的話要改為標入 #include <GL\openglut.h>

#include <sys/socket.h>

#include "card.h"
#include "printout.h"
#include "client.h"

// global
// graphic
GLfloat fix_cardX=-8.5,fix_cardY=-3.25;
GLfloat tableX = -12,tableY = 9;
GLfloat squareX = -9,squareY1 = 8,squareY2 = -3;
GLfloat buttonX = -10,buttonY = 10;
GLfloat deckX=6,deckY=2;

// card
Card hand[5];
int hand_len, point;
// setting
int first = 1;
int server_socket;

void loadCard(Card temp_card,int card_i){
  hand[card_i] = temp_card;
}

int initGraphic(){
  /*Init the window*********/
  int argc = 1;
  char *argv[1] = {(char *)"Something" };

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640,480);      //視窗長寬
  glutInitWindowPosition(0,0);      //視窗左上角的位置
  glutCreateWindow("這裡是視窗標題");    //建立視窗
  /************************/

  // hand[0] = makeCard('S',1);
  // hand[1] = makeCard('D',10);
  // hand[2] = makeCard('D',3);
  // hand[3] = makeCard('C',7);
  // hand[4] = makeCard('H',13);

  //下面三個是用來指定Callback函數
  glutReshapeFunc(WindowSize);
  // glutMouseFunc(Mouse);
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);

  return 0;
}
void startGraphic(){
  glutMainLoop();
}


void text(float x,float y,int card_i){
  char buf[1];
  char buf_num[2];
  // put hand to each card
  buf[0] = hand[card_i].flow;
  if(hand[card_i].point >= 10){
    buf_num[0] = hand[card_i].point / 10 + '0';
    buf_num[1] = hand[card_i].point % 10 + '0';
  }
  else{
    buf_num[0] = ' ';
    buf_num[1] = hand[card_i].point + '0';
  }

  // color
  if(hand[card_i].flow == 'C' || hand[card_i].flow == 'S')glColor3f(0,0,0);
  else glColor3f(1,0,0);

  glRasterPos3f(x+0.42,y-1.1,0);
  // glRasterPos3f(x+0.4,y-0.7,0);
  // output one char
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,buf[0]);


  glRasterPos3f(x+0.40,y-2.0,0);
  // output two number
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,buf_num[0]);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,buf_num[1]);


}
void courage(int length){
  char buffer[50];
  if(length == 5){
    strcpy(buffer,"Chiken Chiken Winner Dinner!");
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(-10.0,0.0,0);
    for(int i = 0;buffer[i] != '\0' ;i++)
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);
    }
  }
  else {
    strcpy(buffer,"One more!");
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(-10.0,0.0,0);
    for(int i = 0;buffer[i] != '\0' ;i++)
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);
    }
  }


}

void Display(void){
  GLfloat cardX = fix_cardX, cardY = fix_cardY;
  glClearColor(0.0, 0.0, 0.0, 0.0);  //用白色塗背景
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,0,10.0f,0,0,0,0,1,0);  //視線的座標及方向

/*display table*/
  glBegin(GL_QUADS);
    glColor3f(.012,0.201,0.031);
    glVertex2f(tableX,tableY);
    glVertex2f(tableX+24,tableY);
    glVertex2f(tableX+24,tableY-18);
    glVertex2f(tableX,tableY-18);
  glEnd();
/*button table*/

/*SUM area*/
  glBegin(GL_QUADS);
    glColor3f(0.008,0.115,0.018);
    glVertex2f(tableX+18,tableY-1);
    glVertex2f(tableX+23,tableY-1);
    glVertex2f(tableX+23,tableY-6);
    glVertex2f(tableX+18,tableY-6);

    glVertex2f(tableX+18,tableY-12);
    glVertex2f(tableX+23,tableY-12);
    glVertex2f(tableX+23,tableY-17);
    glVertex2f(tableX+18,tableY-17);
  glEnd();
  /*White square rival:*/
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_LINE_STRIP);
    glVertex2f(squareX,squareY1);
    glVertex2f(squareX+15,squareY1);
    glVertex2f(squareX+15,squareY1-5);
    glVertex2f(squareX,squareY1-5);
    glVertex2f(squareX,squareY1);
  glEnd();
/*White square me:*/
  glBegin(GL_LINE_STRIP);
    glVertex2f(squareX,squareY2);
    glVertex2f(squareX+15,squareY2);
    glVertex2f(squareX+15,squareY2-5);
    glVertex2f(squareX,squareY2-5);
    glVertex2f(squareX,squareY2);
  glEnd();
/*draw deck*/

  for(int i=0;i<40;i++){
    glBegin(GL_QUADS);
      glColor3f(0.208,0.025,0.025);
      glVertex2f(deckX+0.01*i,deckY-0.005*i);
      glVertex2f(deckX+0.01*i,deckY-CARD_HEIGHT-0.005*i);
      glVertex2f(deckX+0.01*i+CARD_WIDTH,deckY-CARD_HEIGHT-0.005*i);
      glVertex2f(deckX+0.01*i+CARD_WIDTH,deckY-0.005*i);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glColor3f(0.0,0.0,0.0);
      glVertex2f(deckX+0.01*i,deckY-0.005*i);
      glVertex2f(deckX+0.01*i,deckY-CARD_HEIGHT-0.005*i);
      glVertex2f(deckX+0.01*i+CARD_WIDTH,deckY-CARD_HEIGHT-0.005*i);
      glVertex2f(deckX+0.01*i+CARD_WIDTH,deckY-0.005*i);
      glVertex2f(deckX+0.01*i,deckY-0.005*i);
    glEnd();

  }

/******draw cards******/
  if(hand_len>1){
    courage(hand_len);
  }
  for(int i = 0;i<hand_len;i++){
    glBegin(GL_QUADS);
      glColor3f(1.0,1.0,1.0);
      glVertex2f(cardX,cardY);
      glVertex2f(cardX,cardY-CARD_HEIGHT);
      glVertex2f(cardX+CARD_WIDTH,cardY-CARD_HEIGHT);
      glVertex2f(cardX+CARD_WIDTH,cardY);
    glEnd();

    /*output text*/

    text(cardX,cardY,i);
    cardX += CARD_WIDTH +CARD_SPACE;
  }

  glutSwapBuffers();

  if(first){
    first = 0;

    char get[16];
    printHand(hand,&hand_len,&point);
    recv(server_socket,get,sizeof(get),0);
  }
}
int Check(int x,int y){
  GLfloat tmpx = (GLfloat)x;

  GLfloat tmpy = (GLfloat)y;
   printf("%f  %f\n",tmpx,tmpy);
  if((tmpx>=3&&tmpx<=4)&&(tmpy>=3&&tmpy<=4))return 1;
  else return 0;
}
void Mouse(int button,int state,int x,int y){
  printf("你所按按鍵的碼是%d\t此時視窗內的滑鼠座標是(%d,%d)\n", button, x, y);
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && Check(x,y) == 1){
   // len++;
   glutPostRedisplay();
   printf("Success!\n");
  }
}
void Keyboard(unsigned char key, int x, int y){
  // printf("你所按按鍵的碼是%d\t此時視窗內的滑鼠座標是(%d,%d)\n", key, x, y);

  int status = gameLoop(server_socket,hand,&hand_len,&point,key);

  glutPostRedisplay();

  if(status == 0){
    printf("All Done.\n");

    result(server_socket,hand,&hand_len,&point);
  }
}

void WindowSize(int w, int h){
  printf("目前視窗大小為%dX%d\n",w,h);
  glViewport(0, 0, w, h);        //當視窗長寬改變時，畫面也跟著變
  GLfloat aspect = (GLfloat)w / (GLfloat)h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(w>=h)
  {
    glOrtho(-10 * aspect,10 * aspect,-10,10,-10,10);
  }
  else
  {
    glOrtho(-10,10,-10 / aspect,10 / aspect,-10,10);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


int main(int argc, char const *argv[]) {
  // client setting
  socketSetting(&server_socket,hand,&hand_len);
  // graphic setting
  initGraphic();

  startGraphic();

  return 0;
}
