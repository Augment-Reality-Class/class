#include <GL/glut.h>
#include <gl/gl.h>
void  display()
{
     glClearColor(0.0,0.0,0.0,0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     glColor4f(1.0,0.0,0.0,1.0);     // set the quad color     glBegin(GL_QUADS);
         glVertex3f(-0.5,-0.5,0.0);
         glVertex3f(0.5,-0.5,0.0);
         glVertex3f(0.5,0.5,0.0);
         glVertex3f(-0.5,0.5,0.0);
    glEnd();
    glFlush();
}int main(int argc, char** argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
     glutInitWindowPosition(100, 100);
     glutInitWindowSize(400, 400);
     glutCreateWindow("第一个OpenGL程序");
     glutDisplayFunc(display);
     glutMainLoop();
     return 0;
}