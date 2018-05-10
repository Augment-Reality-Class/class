#include <GL/glut.h>   
  
void InitEnvironment()  
{  
    glClearColor(0.6,0.6,0.6,0);  
    glClear(GL_COLOR_BUFFER_BIT);  
    glPointSize(6);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    gluOrtho2D(0,400,0,400);  
}  
  
void myDisplay(void)      
{   
    glClear(GL_COLOR_BUFFER_BIT);  
    glFlush();  
}    
  
void OnMouse(int button,int state,int x,int y)  
{  
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)  
    {  
        glColor3f(1,0,0);  
        glBegin(GL_POINTS);  
        glVertex2f(x,400-y);  
        glEnd();  
        glFlush();  
    }  
    if(button==GLUT_MIDDLE_BUTTON&&state==GLUT_DOWN)  
    {  
        glColor3f(0,1,0);  
        glBegin(GL_POINTS);  
        glVertex2f(x,400-y);  
        glEnd();  
        glFlush();  
    }  
    if(button==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN)  
    {  
        glColor3f(0,0,1);  
        glBegin(GL_POINTS);  
        glVertex2f(x,400-y);  
        glEnd();  
        glFlush();  
    }  
}  
  
int main(int argc, char *argv[])      
{      
    glutInit(&argc, argv);   //��ʼ��GLUT  
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);    
    glutInitWindowPosition(500, 200);      
    glutInitWindowSize(400, 400);      
    glutCreateWindow("OpenGL");   
    InitEnvironment();   //��ʼ��  
    glutMouseFunc(&OnMouse);  //ע������¼�  
    glutDisplayFunc(&myDisplay);   //�ص�����   
    glutMainLoop();    //������ʾ�������ڸı�����»���ͼ��  
    return 0;      
} 