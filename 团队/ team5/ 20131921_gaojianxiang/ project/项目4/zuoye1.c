#include <GL/glut.h>

void myDisplay()
{
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(100, 100);//设置窗口在屏幕中的位置
    glutInitWindowSize(400, 400);//设置窗口的大小
    glutCreateWindow("kuangopengl");
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
