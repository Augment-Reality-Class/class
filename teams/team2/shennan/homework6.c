#include <GL/glut.h>  
  
void display()  
{  
    glShadeModel(GL_SMOOTH);    //光滑明暗处理  
    glClear(GL_COLOR_BUFFER_BIT);  
    glBegin(GL_POLYGON);  
    glColor3f(0.0f, 0.0f, 1.0f);    //蓝色  
    glVertex2f(-0.5,-0.5);  
    glColor3f(0.0f, 1.0f, 0.0f);    //绿色  
    glVertex2f(-0.5,0.5);  
    glColor3f(0.0f, 1.0f, 1.0f);    //青色  
    glVertex2f(0.5,0.5);  
    glColor3f(1.0f, 0.0f, 0.0f);    //红色  
    glVertex2f(0.5,-0.5);  
    glEnd();  
    glFlush();  
}  
  
void main(int argc, char* argv[])  
{  
    glutInit(&argc,argv);  
    glutCreateWindow("rectangle");        //窗口名为"rectangle"  
    glutDisplayFunc(display);  
    glutMainLoop();  
}


