    #include <GL/glut.h>  
    #include <GL/gl.h>  
    #include <stdlib.h>  
            
    float angle = 0.0;  
    float red=1.0, blue=1.0, green=1.0;  
      
    void changeSize(int w, int h)   
    {  
      
        // Prevent a divide by zero, when window is too short  
        // (you cant make a window of zero width).  
        if(h == 0)  
            h = 1;  
      
        float ratio = 1.0* w / h;  
      
        // Reset the coordinate system before modifying  
        glMatrixMode(GL_PROJECTION);  
        glLoadIdentity();  
      
        // Set the viewport to be the entire window  
        glViewport(0, 0, w, h);  
      
        // Set the correct perspective.  
        gluPerspective(45,ratio,1,1000);  
        glMatrixMode(GL_MODELVIEW);  
        glLoadIdentity();  
        gluLookAt(0.0,0.0,5.0,   
            0.0,0.0,-1.0,  
            0.0f,1.0f,0.0f);  
      
      
    }  
      
      
    void renderScene(void)   
    {  
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
        glPushMatrix();  
        glRotatef(angle,0.0,1.0,0.0);  
      
        glColor3f(red,green,blue);  
      
        glBegin(GL_TRIANGLES);  
        glVertex3f(-0.5,-0.5,0.0);  
        glVertex3f(0.5,0.0,0.0);  
        glVertex3f(0.0,0.5,0.0);  
        glEnd();  
        glPopMatrix();  
        angle++;  
        glutSwapBuffers();  
    }  
      
    void processNormalKeys(unsigned char key, int x, int y)   
    {  
      
        if (key == 27)  //按ESC退出  
            exit(0);  
    }  
      
    void processSpecialKeys(int key, int x, int y)   
    {  
      
        switch(key)   
        {  
        case GLUT_KEY_F1 : red = 1.0; green = 0.0; blue = 0.0; break;  
        case GLUT_KEY_F2 : red = 0.0; green = 1.0; blue = 0.0; break;  
        case GLUT_KEY_F3 : red = 0.0; green = 0.0; blue = 1.0; break;  
        }  
    }  
      
    void main(int argc, char **argv)   
    {  
        glutInit(&argc, argv);  
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
        glutInitWindowPosition(100,100);  
        glutInitWindowSize(320,320);  
        glutCreateWindow("Lighthouse 3D - GLUT Tutorial");  
        glutDisplayFunc(renderScene);  //  
        /* 
        glutIdleFunc设置全局的回调函数，当没有窗口事件到达时，GLUT程序功能可以执行后台处理任务或连续动画。 
        如果启用，这个idle function会被不断调用，直到有窗口事件发生。 
        */  
        glutIdleFunc(renderScene); //空闲时调用的函数，即渲染时调用的函数  
        glutReshapeFunc(changeSize);  
      
        //adding here the setting of keyboard processing  
        glutKeyboardFunc(processNormalKeys);  
        glutSpecialFunc(processSpecialKeys);  
        glutMainLoop(); //进入循环，该语句后面的语句不会执行  
    }  
