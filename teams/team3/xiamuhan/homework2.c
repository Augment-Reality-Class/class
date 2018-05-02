// test.c
/* light.c
�˳�������GLUT����һ��OpenGL���ڣ�����ʾһ�����Թ��յ���
*/
/* ����ͷ�ļ�glut.h���Ѿ�������ͷ�ļ�gl.h��glu.h������ֻ��Ҫinclude ���ļ�*/
# include <GL/glut.h>
# include <stdlib.h>
    
/* ��ʼ���������ԡ���Դ���ԡ�����ģ�ͣ�����Ȼ����� */
void init ( void )
{
    GLfloat mat_specular [ ] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess [ ] = { 50.0 };
    GLfloat light_position [ ] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor ( 0.0, 0.0, 0.0, 0.0 );
    glShadeModel ( GL_SMOOTH );
    glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv ( GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv ( GL_LIGHT0, GL_POSITION, light_position);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);
}
/*����GLUT����������һ����*/
void display ( void )
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidSphere (1.0, 40, 50);
    glFlush ();
}
    
int main(int argc, char** argv)
{
    /* GLUT������ʼ��*/
    glutInit (&argc, argv);
    /* ��ʾģʽ��ʼ�� */
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    /* ���崰�ڴ�С */
    glutInitWindowSize (300, 300);
    /* ���崰��λ�� */
    glutInitWindowPosition (100, 100);
    /* ��ʾ���ڣ����ڱ���Ϊִ�к����� */
    glutCreateWindow ( argv [ 0 ] );
    /* ����OpenGL��ʼ������ */
    init ( );
    /* ע��OpenGL��ͼ���� */
    glutDisplayFunc ( display );
    // /* ����GLUT��Ϣѭ������ʼִ�г��� */
    glutMainLoop( );
    return 0;
}

