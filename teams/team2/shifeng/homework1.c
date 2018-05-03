#include <GL/glut.h>
#include <stdlib.h>

void display(void)
{
   /* clear all pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   glFlush ();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("蓝色背景窗体");
   glClearColor (0.0, 0.0, 1.0, 0.0);
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;
}
