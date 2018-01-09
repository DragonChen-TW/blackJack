#include "printout.h"

GLfloat cardX=-8,cardY=-3;
GLfloat buttonX = -10,buttonY = 10;
int len = 2;


int printout()
{
  /*Init the window*********/
  int argc = 1;
  char *argv[1] = {(char *)"Something" };

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(640,480);      //視窗長寬
  glutInitWindowPosition(0,0);      //視窗左上角的位置
  glutCreateWindow("這裡是視窗標題");    //建立視窗
  /************************/

  //下面三個是用來指定Callback函數
  glutReshapeFunc(WindowSize);
  glutMouseFunc(Mouse);
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);
  glutMainLoop();
  return 0;
}

void Display(void)
{
  GLfloat cardX=-8,cardY=-3;/*init card(x,y)*/
  glClearColor(1.0, 1.0, 1.0, 1.0);  //用白色塗背景
  glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0,0,10.0f,0,0,0,0,1,0);  //視線的座標及方向
/*display button*/
  glBegin(GL_QUADS);
  glColor3f(0.0,0.0,1.0);
  glVertex2f(buttonX,buttonY);
  glVertex2f(buttonX+1,buttonY);
  glVertex2f(buttonX+1,buttonY-1);
  glVertex2f(buttonX,buttonY-1);
  glEnd();
/*button end*/

/******draw cards******/
  glBegin(GL_QUADS);
  glColor3f(1.0,0.0,0.0);
  for(int i = 0;i<len;i++){
    glVertex2f(cardX,cardY);
    glVertex2f(cardX,cardY-CARD_HEIGHT);
    glVertex2f(cardX+CARD_WIDTH,cardY-CARD_HEIGHT);
    glVertex2f(cardX+CARD_WIDTH,cardY);
    cardX += CARD_WIDTH +CARD_SPACE;
  }
  glEnd();
  glutSwapBuffers();
}
int Check(int x,int y)
{
  GLfloat tmpx = (GLfloat)x;

  GLfloat tmpy = (GLfloat)y;
   printf("%f  %f\n",tmpx,tmpy);
  if((tmpx>=3&&tmpx<=4)&&(tmpy>=3&&tmpy<=4))return 1;
  else return 0;
}
void Mouse(int button,int state,int x,int y)
{
  printf("你所按按鍵的碼是%d\t此時視窗內的滑鼠座標是(%d,%d)\n", button, x, y);
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && Check(x,y) == 1){
   len++;
   glutPostRedisplay();
   printf("Success!\n");
  }
}
void Keyboard(unsigned char key, int x, int y)
{
  printf("你所按按鍵的碼是%d\t此時視窗內的滑鼠座標是(%d,%d)\n", key, x, y);
  if(key == 'a'){
    len++;
    glutPostRedisplay();
    printf("Success!\n");
  }
  else if(key == 's'){
    /*stop asking for card*/
    printf("stop asking!\n");
  }
}

void WindowSize(int w, int h)
{
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
