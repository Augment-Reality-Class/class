#include <GL/glut.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

void paint(void)
{ 
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1,1,1,1);
    glViewport(0, 0, 400, 100);

    glViewport(0, 0, 100, 100);
    glPointSize(10.0f); glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex2f(0.0f,0.0f);
    glEnd();

    glViewport(100, 0, 100, 100);
    glPointSize(20.0f); glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glViewport(200, 0, 100, 100);
    glPointSize(30.0f); glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glViewport(300, 0, 100, 100);
    glPointSize(40.0f); glColor3f(1, 1, 0);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(400,100);
    glutInitWindowPosition(500,300);
    glutCreateWindow("绘制不同大小的点");
    glutDisplayFunc(paint);
    glutMainLoop();
    return 0;
}
