#include <GL/glut.h>

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glClearColor(0.0,0.0,1.0,0.0);//重新设置填充色为蓝色,即窗口背景颜色
    glColor3f(0.0f, 0.0f, 1.0f);//设置画笔的颜色为蓝色
    glRectf(-0.5f,-0.5f,0.5f,0.5f);
    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(600,300);
    glutInitWindowSize(400,200);
    glutCreateWindow("我的练习1:红色背景蓝色矩形");
    glClearColor(1.0,0.0,0.0,0.0);//设置背景填充色为红色
    glutDisplayFunc(&myDisplay);//经过测试，寄存回调过程加不加取地址符都正确。
    glutMainLoop();
}
