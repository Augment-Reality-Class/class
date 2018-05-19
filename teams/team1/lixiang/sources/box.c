#include <GL/glut.h>
#include <stdio.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
// glClearColor//清除颜色
    glBegin(GL_POLYGON);
    glVertex2f(-0.5,-0.5);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glEnd();
    glFlush();
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("Hello,world!");
    glutDisplayFunc(display);//glutDisplayFunc(void (*func)(void))
    glutMainLoop();//导致程序进入一个事件
}
