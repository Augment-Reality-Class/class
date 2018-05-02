#include <GL/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glBegin(GL_POINTS);
    //glEnd();
    glRectf(-0.5f,-0.5f,0.5f,0.5f);
    glFlush();

    return;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0); 
    glutInitWindowSize(300, 300);
    glutCreateWindow("OpenGL 3D View");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}