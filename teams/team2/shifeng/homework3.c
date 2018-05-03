#include <GL/glut.h>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.20, 0.20, 0.0);
    glVertex3f(0.80, 0.20, 0.0);
    glVertex3f(0.80, 0.80, 0.0);
    glVertex3f(0.20, 0.80, 0.0);
    glEnd();

    glFlush();
}

void init(void)
{
    glClearColor(0.0, 1.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(400, 300);
    glutCreateWindow("polyon");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
