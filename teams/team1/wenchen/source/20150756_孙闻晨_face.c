/*************************************************************************/
/***************************@author:sunwenchen****************************/
/***************************created at 6.07*******************************/
/****************************description**********************************/
/***************************实现了人脸的渲染*******************************/
#define WindowWidth  800
#define WindowHeight 800
#define WindowTitle  "OpenGL纹理测试"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

//定义两个纹理对象编号
//GLuint texGround;
GLuint texWall;

#define BMP_Header_Length 54  //图像数据在内存块中的偏移量
//static GLfloat angle = 0.0f;   //旋转角度
//GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

int s1=0,s2=0;
// 函数power_of_two用于判断一个整数是不是2的整数次幂
int power_of_two(int n)
{
	if( n <= 0 )
		return 0;
	return (n & (n-1)) == 0;
}

/* 函数load_texture
* 读取一个BMP文件作为纹理
* 如果失败，返回0，如果成功，返回纹理编号
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID=0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if( pFile == 0 )
		return 0;

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	{
		GLint line_bytes = width * 3;
		while( line_bytes % 4 != 0 )
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if( pixels == 0 )
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if( fread(pixels, total_bytes, 1, pFile) <= 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
	// 若图像宽高超过了OpenGL规定的最大值，也缩放
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if( !power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max )
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// 计算每行需要的字节数和总字节数
			new_line_bytes = new_width * 3;
			while( new_line_bytes % 4 != 0 )
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// 分配内存
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if( new_pixels == 0 )
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// 进行像素缩放
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if( texture_ID == 0 )
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID=last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	free(pixels);
	return texture_ID;
}
void keyboard (unsigned char key, int x, int y)
{
switch (key) {
case 's':
s1 = (s1 + 5) % 360;
glutPostRedisplay();
break;
case 'S':
s1 = (s1 - 5) % 360;
glutPostRedisplay();
break;
case 'e':
s2 = (s2 + 5) % 360;
glutPostRedisplay();
break;
case 'E':
s2 = (s2 - 5) % 360;
glutPostRedisplay();
break;
case 27:
exit(0);
break;
default:
break;
}
}
static GLfloat spin = 0.0;
void init(void)
{
glClearColor(0.0,0.0,0.0,0.0);
glShadeModel(GL_FLAT); //������ģ����Ϊƽ��ģʽ
}
void display(void)
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        //gluPerspective(75, 1, 1, 21);
       gluPerspective(20, 1, 3, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-4, 7,7, 0, 0, 0, 0, 0, 1);
	//glRotatef(angle, 0.0f, 0.0f, 1.0f); //旋转
        //glRotatef(spin,0.0,0.0,0.0);
        glRotatef(s1,0.0,0.0,1.0);
        glRotatef(s2,1.0,0.0,0.0);
        glBindTexture(GL_TEXTURE_2D, texWall);
       //glBegin(GL_QUADS);
      glBegin(GL_TRIANGLES);

/*glClear(GL_COLOR_BUFFER_BIT);
glPushMatrix(); //���������任�ļ���
glRotatef(spin,0.0,1.0,0.0);
glColor3f(0.5,0.0,1.0);
glPolygonMode(GL_FRONT_AND_BACK,GL_FRONT);
glBindTexture(GL_TEXTURE_2D, texWall);
glBegin(GL_TRIANGLES);*/
	// 绘制底面以及纹理
glTexCoord2d(0.501041,0.005000);glVertex3f(0.000000f,1.061000f,-0.371000f);
glTexCoord2d(0.587917,0.079375);glVertex3f(0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.600208,0.014375);glVertex3f(0.217000f,1.039000f,-0.371000f);
glTexCoord2d(0.501041,0.005000);glVertex3f(0.000000f,1.061000f,-0.371000f);
glTexCoord2d(0.587917,0.079375);glVertex3f(0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.412708,0.080208);glVertex3f(-0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.501041,0.005000);glVertex3f(0.000000f,1.061000f,-0.371000f);
glTexCoord2d(0.412708,0.080208);glVertex3f(-0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.400833,0.014375);glVertex3f(-0.217000f,1.039000f,-0.371000f);
glTexCoord2d(0.587917,0.079375);glVertex3f(0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.600208,0.014375);glVertex3f(0.217000f,1.039000f,-0.371000f);
glTexCoord2d(0.712708,0.068333);glVertex3f(0.457000f,0.909000f,-0.328000f);
glTexCoord2d(0.412708,0.080208);glVertex3f(-0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.400833,0.014375);glVertex3f(-0.217000f,1.039000f,-0.371000f);
glTexCoord2d(0.289167,0.068542);glVertex3f(-0.457000f,0.909000f,-0.328000f);
glTexCoord2d(0.587917,0.079375);glVertex3f(0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.712708,0.068333);glVertex3f(0.457000f,0.909000f,-0.328000f);
glTexCoord2d(0.716250,0.181458);glVertex3f(0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.587917,0.079375);glVertex3f(0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.716250,0.181458);glVertex3f(0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.587917,0.079375);glVertex3f(0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.412708,0.080208);glVertex3f(-0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.412708,0.080208);glVertex3f(-0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.283958,0.179792);glVertex3f(-0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.412708,0.080208);glVertex3f(-0.174000f,0.800000f,-0.024000f);
glTexCoord2d(0.289167,0.068542);glVertex3f(-0.457000f,0.909000f,-0.328000f);
glTexCoord2d(0.283958,0.179792);glVertex3f(-0.435000f,0.626000f,-0.111000f);
//10
glTexCoord2d(0.712708,0.068333);glVertex3f(0.457000f,0.909000f,-0.328000f);
glTexCoord2d(0.716250,0.181458);glVertex3f(0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.783958,0.240625);glVertex3f(0.610000f,0.539000f,-0.328000f);
glTexCoord2d(0.716250,0.181458);glVertex3f(0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.783958,0.240625);glVertex3f(0.610000f,0.539000f,-0.328000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.716250,0.181458);glVertex3f(0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.703125,0.295208);glVertex3f(0.391000f,0.374000f,0.0300000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.716250,0.181458);glVertex3f(0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.703125,0.295208);glVertex3f(0.391000f,0.374000f,0.0300000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.703125,0.295208);glVertex3f(0.391000f,0.374000f,0.0300000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.502292,0.342708);glVertex3f(0.000000f,0.278000f,0.107000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.502292,0.342708);glVertex3f(0.000000f,0.278000f,0.107000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.298125,0.295208);glVertex3f(-0.391000f,0.374000f,0.030000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.502292,0.203542);glVertex3f(0.000000f,0.539000f,0.085000f);
glTexCoord2d(0.283958,0.179792);glVertex3f(-0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.298125,0.295208);glVertex3f(-0.391000f,0.374000f,0.030000f);
glTexCoord2d(0.283958,0.179792);glVertex3f(-0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.298125,0.295208);glVertex3f(-0.391000f,0.374000f,0.030000f);
//20
glTexCoord2d(0.283958,0.179792);glVertex3f(-0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.217083,0.239583);glVertex3f(-0.610000f,0.539000f,-0.328000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.289167,0.068542);glVertex3f(-0.457000f,0.909000f,-0.328000f);
glTexCoord2d(0.283958,0.179792);glVertex3f(-0.435000f,0.626000f,-0.111000f);
glTexCoord2d(0.217083,0.239583);glVertex3f(-0.610000f,0.539000f,-0.328000f);
glTexCoord2d(0.783958,0.240625);glVertex3f(0.610000f,0.539000f,-0.328000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.783958,0.425625);glVertex3f(0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.783958,0.425625);glVertex3f(0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.703333,0.324375);glVertex3f(0.391000f,0.322000f,0.0300000f);
glTexCoord2d(0.661458,0.374167);glVertex3f(0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.703125,0.295208);glVertex3f(0.391000f,0.374000f,0.0300000f);
glTexCoord2d(0.703333,0.324375);glVertex3f(0.391000f,0.322000f,0.0300000f);
glTexCoord2d(0.703125,0.295208);glVertex3f(0.391000f,0.374000f,0.0300000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.703333,0.324375);glVertex3f(0.391000f,0.322000f,0.0300000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.703333,0.324375);glVertex3f(0.391000f,0.322000f,0.0300000f);
glTexCoord2d(0.661458,0.374167);glVertex3f(0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.512917,0.378542);glVertex3f(0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.502292,0.342708 );glVertex3f(0.000000f,0.278000f,0.107000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.512917,0.378542);glVertex3f(0.022000f,0.213000f,0.063000f);
//30
glTexCoord2d(0.502292,0.342708 );glVertex3f(0.000000f,0.278000f,0.107000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.490208,0.378542);glVertex3f(-0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.490208,0.378542);glVertex3f(-0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.299167,0.324167);glVertex3f(-0.391000f,0.322000f,0.030000f);
glTexCoord2d(0.343125,0.374167);glVertex3f(-0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.298125,0.295208);glVertex3f(-0.391000f,0.374000f,0.030000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.299167,0.324167);glVertex3f(-0.391000f,0.322000f,0.030000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.298125,0.295208);glVertex3f(-0.391000f,0.374000f,0.030000f);
glTexCoord2d(0.299167,0.324167);glVertex3f(-0.391000f,0.322000f,0.030000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.299167,0.324167);glVertex3f(-0.391000f,0.322000f,0.030000f);
glTexCoord2d(0.343125,0.374167);glVertex3f(-0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.218542,0.424583);glVertex3f(-0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.217083,0.239583);glVertex3f(-0.610000f,0.539000f,-0.328000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.218542,0.424583);glVertex3f(-0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.756042,0.609583);glVertex3f(0.550000f,-0.250000f,-0.328000f);
glTexCoord2d(0.783958,0.425625);glVertex3f(0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.783958,0.425625);glVertex3f(0.609000f,0.148000f,-0.328000f);
//40
glTexCoord2d(0.656875,0.442292);glVertex3f(0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.558958,0.568333);glVertex3f(0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.343125,0.441458);glVertex3f(-0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.442917,0.569583);glVertex3f(-0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.218542,0.424583);glVertex3f(-0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.245417,0.608542);glVertex3f(-0.550000f,-0.250000f,-0.328000f);
glTexCoord2d(0.218542,0.424583);glVertex3f(-0.609000f,0.148000f,-0.328000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.524792,0.705833);glVertex3f(0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.563125,0.633333);glVertex3f(0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.563125,0.633333);glVertex3f(0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.558958,0.568333);glVertex3f(0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.442917,0.569583);glVertex3f(-0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.439167,0.632500);glVertex3f(-0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.477292,0.705625);glVertex3f(-0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.439167,0.632500);glVertex3f(-0.120000f,-0.265000f,0.100000f);
//50
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.524792,0.705833);glVertex3f(0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.477292,0.705625);glVertex3f(-0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.502292,0.807708);glVertex3f(0.000000f,-0.591000f,0.107000f);
glTexCoord2d(0.502292,0.941875);glVertex3f(0.000000f,-0.852000f,0.063000f);
glTexCoord2d(0.591458,0.908333);glVertex3f(0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.502292,0.807708);glVertex3f(0.000000f,-0.591000f,0.107000f);
glTexCoord2d(0.502292,0.941875);glVertex3f(0.000000f,-0.852000f,0.063000f);
glTexCoord2d(0.411250,0.908125);glVertex3f(-0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.502292,0.616042);glVertex3f(0.000000f,-0.222000f,0.210000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.502292,0.616042);glVertex3f(0.000000f,-0.222000f,0.210000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.502292,0.342708);glVertex3f(0.000000f,0.278000f,0.107000f);
glTexCoord2d(0.512917,0.378542);glVertex3f(0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.490208,0.378542);glVertex3f(-0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.524792,0.705833);glVertex3f(0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.565000,0.707083);glVertex3f(0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.565000,0.707083);glVertex3f(0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.551875,0.732083);glVertex3f(0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.551875,0.732083);glVertex3f(0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.502292,0.740625);glVertex3f(0.000000f,-0.461000f,0.124000f);
//60
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.477292,0.705625);glVertex3f(-0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.436250,0.707917);glVertex3f(-0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.436250,0.707917);glVertex3f(-0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.449792,0.732083);glVertex3f(-0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.502292,0.717083);glVertex3f(0.000000f,-0.417000f,0.142000f);
glTexCoord2d(0.449792,0.732083);glVertex3f(-0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.502292,0.740625);glVertex3f(0.000000f,-0.461000f,0.124000f);
glTexCoord2d(0.436250,0.707917);glVertex3f(-0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.449792,0.732083);glVertex3f(-0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.401250,0.728333);glVertex3f(-0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.374792,0.727917);glVertex3f(-0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.436250,0.707917);glVertex3f(-0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.401250,0.728333);glVertex3f(-0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.565000,0.707083);glVertex3f(0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.551875,0.732083);glVertex3f(0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.596875,0.728333);glVertex3f(-0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.627083,0.727708);glVertex3f(0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.565000,0.707083);glVertex3f(0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.596875,0.728333);glVertex3f(-0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.524792,0.705833);glVertex3f(0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.565000,0.707083);glVertex3f(0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.627083,0.727708);glVertex3f(0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.565000,0.707083);glVertex3f(0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.477292,0.705625);glVertex3f(-0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.436250,0.707917);glVertex3f(-0.123000f,-0.410000f,0.063000f);
//70
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.374792,0.727917);glVertex3f(-0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.436250,0.707917);glVertex3f(-0.123000f,-0.410000f,0.063000f);
glTexCoord2d(0.550417,0.733333);glVertex3f(0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.566667,0.758958);glVertex3f(0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.596875,0.728333);glVertex3f(0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.627083,0.727708);glVertex3f(0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.566667,0.758958);glVertex3f(0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.596875,0.728333);glVertex3f(0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.502292,0.776875);glVertex3f(0.000000f,-0.526000f,0.150000f);
glTexCoord2d(0.550417,0.733333);glVertex3f(0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.566667,0.758958);glVertex3f(0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.502292,0.776875);glVertex3f(0.000000f,-0.526000f,0.150000f);
glTexCoord2d(0.502292,0.740625);glVertex3f(0.000000f,-0.461000f,0.124000f);
glTexCoord2d(0.550417,0.733333);glVertex3f(0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.502292,0.776875);glVertex3f(0.000000f,-0.526000f,0.150000f);
glTexCoord2d(0.502292,0.740625);glVertex3f(0.000000f,-0.461000f,0.124000f);
glTexCoord2d(0.449375,0.733333);glVertex3f(-0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.502292,0.776875);glVertex3f(0.000000f,-0.526000f,0.150000f);
glTexCoord2d(0.449375,0.733333);glVertex3f(-0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.435417,0.758958);glVertex3f(-0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.449375,0.733333);glVertex3f(-0.100000f,-0.461000f,0.050000f);
glTexCoord2d(0.435417,0.758958);glVertex3f(-0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.401250,0.728333);glVertex3f(-0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.374792,0.727917);glVertex3f(-0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.435417,0.758958);glVertex3f(-0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.401250,0.728333);glVertex3f(-0.200000f,-0.461000f,-0.024000f);
glTexCoord2d(0.502292,0.776875);glVertex3f(0.000000f,-0.526000f,0.150000f);
glTexCoord2d(0.502292,0.807708);glVertex3f(0.000000f,-0.591000f,0.107000f);
glTexCoord2d(0.566667,0.758958);glVertex3f(0.123000f,-0.508000f,0.063000f);
//80
glTexCoord2d(0.502292,0.776875);glVertex3f(0.000000f,-0.526000f,0.150000f);
glTexCoord2d(0.502292,0.807708);glVertex3f(0.000000f,-0.591000f,0.107000f);
glTexCoord2d(0.435417,0.758958);glVertex3f(-0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.627083,0.727708);glVertex3f(0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.591458,0.908333);glVertex3f(0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.566667,0.758958);glVertex3f(0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.502292,0.807708);glVertex3f(0.000000f,-0.591000f,0.107000f);
glTexCoord2d(0.591458,0.908333);glVertex3f(0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.566667,0.758958);glVertex3f(0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.374792,0.727917);glVertex3f(-0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.411250,0.908125);glVertex3f(-0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.435417,0.758958);glVertex3f(-0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.502292,0.807708);glVertex3f(0.000000f,-0.591000f,0.107000f);
glTexCoord2d(0.411250,0.908125);glVertex3f(-0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.435417,0.758958);glVertex3f(-0.123000f,-0.508000f,0.063000f);
glTexCoord2d(0.656875,0.442292);glVertex3f(0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.706875,0.760208);glVertex3f(0.470000f,-0.600000f,-0.328000f);
glTexCoord2d(0.591458,0.908333);glVertex3f(0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.682292,0.724167);glVertex3f(0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.627083,0.727708);glVertex3f(0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.591458,0.908333);glVertex3f(0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.682292,0.724167);glVertex3f(0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.756042,0.609583);glVertex3f(0.550000f,-0.250000f,-0.328000f);
glTexCoord2d(0.706875,0.760208);glVertex3f(0.470000f,-0.600000f,-0.328000f);
glTexCoord2d(0.682292,0.724167);glVertex3f(0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.627083,0.727708);glVertex3f(0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.682292,0.724167);glVertex3f(0.357000f,-0.461000f,-0.050000f);
//90
glTexCoord2d(0.592917,0.618542);glVertex3f(0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.682292,0.724167);glVertex3f(0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.756042,0.609583);glVertex3f(0.550000f,-0.250000f,-0.328000f);
glTexCoord2d(0.682292,0.724167);glVertex3f(0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.343125,0.441458);glVertex3f(-0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.291875,0.759167);glVertex3f(-0.470000f,-0.600000f,-0.328000f);
glTexCoord2d(0.411250,0.908125);glVertex3f(-0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.319521,0.723750);glVertex3f(-0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.374792,0.727917);glVertex3f(-0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.411250,0.908125);glVertex3f(-0.174000f,-0.809000f,0.000000f);
glTexCoord2d(0.319521,0.723750);glVertex3f(-0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.245417,0.608542);glVertex3f(-0.550000f,-0.250000f,-0.328000f);
glTexCoord2d(0.291875,0.759167);glVertex3f(-0.470000f,-0.600000f,-0.328000f);
glTexCoord2d(0.319521,0.723750);glVertex3f(-0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.374792,0.727917);glVertex3f(-0.246000f,-0.461000f,-0.000000f);
glTexCoord2d(0.319521,0.723750);glVertex3f(-0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.408542,0.617917);glVertex3f(-0.174000f,-0.244000f,0.037000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.319521,0.723750);glVertex3f(-0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.245417,0.608542);glVertex3f(-0.550000f,-0.250000f,-0.328000f);
glTexCoord2d(0.319521,0.723750);glVertex3f(-0.357000f,-0.461000f,-0.050000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.512917,0.378542);glVertex3f(0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.533750,0.478958);glVertex3f(0.065000f,0.028000f,0.050000f);
//100
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.558958,0.568333);glVertex3f(0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.533750,0.478958);glVertex3f(0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.558958,0.568333);glVertex3f(0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.533750,0.478958);glVertex3f(0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.490208,0.378542);glVertex3f(-0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.467917,0.476458);glVertex3f(-0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.442917,0.569583);glVertex3f(-0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.467917,0.476458);glVertex3f(-0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.442917,0.569583);glVertex3f(-0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.467917,0.476458);glVertex3f(-0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.512917,0.378542);glVertex3f(0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.533750,0.478958);glVertex3f(0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.533750,0.478958);glVertex3f(0.065000f,0.028000f,0.050000f);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
glTexCoord2d(0.502292,0.616042);glVertex3f(0.000000f,-0.222000f,0.210000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
glTexCoord2d(0.502292,0.616042);glVertex3f(0.000000f,-0.222000f,0.210000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.467917,0.476458);glVertex3f(-0.065000f,0.028000f,0.050000);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
//110
glTexCoord2d(0.490208,0.378542);glVertex3f(-0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.467917,0.476458);glVertex3f(-0.065000f,0.028000f,0.050000);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
glTexCoord2d(0.512917,0.378542);glVertex3f(0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.490208,0.378542);glVertex3f(-0.022000f,0.213000f,0.063000f);
glTexCoord2d(0.502292,0.455625);glVertex3f(0.000000f,0.068000f,0.100000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.697500,0.390208);glVertex3f(0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.697500,0.390208);glVertex3f(0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.691667,0.395417);glVertex3f(0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.695208,0.427083);glVertex3f(0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.696042,0.431875);glVertex3f(0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.696042,0.431875);glVertex3f(0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.758958,0.351250);glVertex3f(0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.661458,0.374167);glVertex3f(0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.697500,0.390208);glVertex3f(0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.661458,0.374167);glVertex3f(0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.697500,0.390208);glVertex3f(0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.697500,0.390208);glVertex3f(0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.691667,0.395417);glVertex3f(0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.656875,0.442292);glVertex3f(0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.697292,0.537500);glVertex3f(0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.696042,0.431875);glVertex3f(0.387000f,0.117000f,-0.067000f);
//120
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.656875,0.442292);glVertex3f(0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.696042,0.431875);glVertex3f(0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.695208,0.427083);glVertex3f(0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.696042,0.431875);glVertex3f(0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.611875,0.387292);glVertex3f(0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.611875,0.387292);glVertex3f(0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.612917,0.396875);glVertex3f(0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.609375,0.427083);glVertex3f(0.217000f,0.126000f,-0.013000f);
glTexCoord2d(0.608333,0.429375);glVertex3f(0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.558958,0.568333);glVertex3f(0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.608333,0.429375);glVertex3f(0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.570000,0.342708);glVertex3f(0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.661458,0.374167);glVertex3f(0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.611875,0.387292);glVertex3f(0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.661458,0.374167);glVertex3f(0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.611875,0.387292);glVertex3f(0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.611875,0.387292);glVertex3f(0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.612917,0.396875);glVertex3f(0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.609375,0.427083);glVertex3f(0.217000f,0.126000f,-0.013000f);
glTexCoord2d(0.608333,0.429375);glVertex3f(0.217000f,0.117000f,-0.024000f);

//130
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.656875,0.442292);glVertex3f(0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.608333,0.429375);glVertex3f(0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.656875,0.442292);glVertex3f(0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.558958,0.568333);glVertex3f(0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.608333,0.429375);glVertex3f(0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.388750,0.387292);glVertex3f(-0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.388750,0.387292);glVertex3f(-0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.374147,0.387292);glVertex3f(-0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.388125,0.427083);glVertex3f(0.217000f,0.126000f,-0.013000f);
glTexCoord2d(0.391667,0.431458);glVertex3f(0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.442917,0.569583);glVertex3f(-0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.391667,0.431458);glVertex3f(-0.2470000f,0.117000f,-0.024000f);
glTexCoord2d(0.431458,0.343958);glVertex3f(-0.130000f,0.278000f,0.107000f);
glTexCoord2d(0.343125,0.374167);glVertex3f(-0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.388750,0.387292);glVertex3f(-0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.343125,0.374167);glVertex3f(-0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.388750,0.387292);glVertex3f(-0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.388750,0.387292);glVertex3f(-0.217000f,0.201000f,-0.013000f);
glTexCoord2d(0.374147,0.387292);glVertex3f(-0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.388125,0.427083);glVertex3f(-0.217000f,0.126000f,-0.013000f);
glTexCoord2d(0.391667,0.431458);glVertex3f(-0.217000f,0.117000f,-0.024000f);
//140
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.343125,0.441458);glVertex3f(-0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.391667,0.431458);glVertex3f(-0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.343125,0.441458);glVertex3f(-0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.442917,0.569583);glVertex3f(-0.109000f,-0.157000f,0.037000f);
glTexCoord2d(0.391667,0.431458);glVertex3f(-0.217000f,0.117000f,-0.024000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.304375,0.391667);glVertex3f(-0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.304375,0.391667);glVertex3f(-0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.309375,0.395417);glVertex3f(-0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.308533,0.427708);glVertex3f(-0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.305833,0.434375);glVertex3f(-0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.305833,0.434375);glVertex3f(-0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.243333,0.343958);glVertex3f(-0.522000f,0.278000f,-0.111000f);
glTexCoord2d(0.343125,0.374167);glVertex3f(-0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.304375,0.391667);glVertex3f(-0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.343125,0.374167);glVertex3f(-0.304000f,0.225000f,-0.002000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.304375,0.391667);glVertex3f(-0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.304375,0.391667);glVertex3f(-0.387000f,0.201000f,-0.056000f);
glTexCoord2d(0.309375,0.395417);glVertex3f(-0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.308533,0.427708);glVertex3f(-0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.305833,0.434375);glVertex3f(-0.387000f,0.117000f,-0.067000f);
//150
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.343125,0.441458);glVertex3f(-0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.305833,0.434375);glVertex3f(-0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.343125,0.441458);glVertex3f(-0.304000f,0.104000f,-0.000000f);
glTexCoord2d(0.303958,0.538750);glVertex3f(-0.387000f,-0.100000f,-0.045000f);
glTexCoord2d(0.305833,0.434375);glVertex3f(-0.387000f,0.117000f,-0.067000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.543958,0.610208);glVertex3f(0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.563125,0.633333);glVertex3f(0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.524792,0.705833);glVertex3f(0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.563125,0.633333);glVertex3f(0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.457708,0.610208);glVertex3f(-0.080000f,-0.220000f,0.150000f);
glTexCoord2d(0.439167,0.632500);glVertex3f(-0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.502292,0.632708);glVertex3f(0.000000f,-0.265000f,0.124000f);
glTexCoord2d(0.477292,0.705625);glVertex3f(-0.043000f,-0.396000f,0.150000f);
glTexCoord2d(0.439167,0.632500);glVertex3f(-0.120000f,-0.265000f,0.100000f);
glTexCoord2d(0.333958,0.425208);glVertex3f(-0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.382500,0.388333);glVertex3f(-0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.382500,0.425208);glVertex3f(-0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.333958,0.388333);glVertex3f(-0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.333958,0.425208);glVertex3f(-0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.382500,0.388333);glVertex3f(-0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.660625,0.388333);glVertex3f(0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.660625,0.425208);glVertex3f(0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.612500,0.425208);glVertex3f(0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.660625,0.388333);glVertex3f(0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.612500,0.388333);glVertex3f(0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.612500,0.425208);glVertex3f(0.265000f,0.115000f,-0.0300000f);
//160
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.333958,0.388333);glVertex3f(-0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.333958,0.425208);glVertex3f(-0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.382500,0.388333);glVertex3f(-0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.382500,0.425208);glVertex3f(-0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.612500,0.388333);glVertex3f(0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.612500,0.425208);glVertex3f(0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.660625,0.388333);glVertex3f(0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.660625,0.425208);glVertex3f(0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.333958,0.388333);glVertex3f(-0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.309375,0.395417);glVertex3f(-0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.333958,0.388333);glVertex3f(-0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.309375,0.395417);glVertex3f(-0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.333958,0.388333);glVertex3f(-0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.382500,0.388333);glVertex3f(-0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.343958,0.387292);glVertex3f(-0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.382500,0.388333);glVertex3f(-0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.374147,0.387292);glVertex3f(-0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.382500,0.388333);glVertex3f(-0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.374147,0.387292);glVertex3f(-0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.433333,0.414792);glVertex3f(-0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.382500,0.425208);glVertex3f(-0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.388125,0.427083);glVertex3f(-0.217000f,0.126000f,-0.013000f);
//170
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.382500,0.425208);glVertex3f(-0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.388125,0.427083);glVertex3f(-0.217000f,0.126000f,-0.013000f);
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.333958,0.425208);glVertex3f(-0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.382500,0.425208);glVertex3f(-0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.308533,0.431458);glVertex3f(-0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.333958,0.425208);glVertex3f(-0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.308533,0.427708);glVertex3f(-0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.268750,0.417292);glVertex3f(-0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.333958,0.425208);glVertex3f(-0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.308533,0.427708);glVertex3f(-0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.660625,0.388333);glVertex3f(0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.691667,0.395417);glVertex3f(0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.660625,0.388333);glVertex3f(0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.691667,0.395417);glVertex3f(0.387000f,0.186000f,-0.056000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.660625,0.388333);glVertex3f(0.348000f,0.200000f,-0.0300000f);
glTexCoord2d(0.612500,0.388333);glVertex3f(0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.659167,0.387292);glVertex3f(0.304000f,0.204000f,-0.000000f);
glTexCoord2d(0.612500,0.388333);glVertex3f(0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.612917,0.396875);glVertex3f(0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.612500,0.388333);glVertex3f(0.265000f,0.200000f,-0.0300000f);
glTexCoord2d(0.612917,0.396875);glVertex3f(0.217000f,0.186000f,-0.013000f);
glTexCoord2d(0.732500,0.418125);glVertex3f(0.470000f,0.148000f,-0.111000f);
glTexCoord2d(0.660625,0.425208);glVertex3f(0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.695208,0.427083);glVertex3f(0.387000f,0.126000f,-0.056000f);
//180
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.660625,0.425208);glVertex3f(0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.695208,0.427083);glVertex3f(0.387000f,0.126000f,-0.056000f);
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.660625,0.425208);glVertex3f(0.348000f,0.115000f,-0.0300000f);
glTexCoord2d(0.612500,0.425208);glVertex3f(0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.695208,0.431458);glVertex3f(0.304000f,0.122000f,-0.000000f);
glTexCoord2d(0.612500,0.425208);glVertex3f(0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.305833,0.434375);glVertex3f(0.217000f,0.126000f,-0.013000f);
glTexCoord2d(0.567917,0.413750);glVertex3f(0.130000f,0.148000f,-0.000000f);
glTexCoord2d(0.612500,0.425208);glVertex3f(0.265000f,0.115000f,-0.0300000f);
glTexCoord2d(0.609375,0.427083);glVertex3f(0.217000f,0.126000f,-0.013000f);
glEnd();
	/*glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(3.0f, 3.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(3.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();
	// 绘制立面
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 5.0f);
	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	//绘制另外一个立面
	glBegin(GL_QUADS);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);     
	glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, 9.0f, 0.0f);		 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 9.0f, 5.0f);		 
	glTexCoord2f(2.0f, 1.0f); glVertex3f(6.0f, -3.0f, 5.0f);	 
	glEnd();*/	
	glutSwapBuffers();  
}

void spinDisplay(void)
{
spin=spin + 1.0;
if(spin>360.0)
spin=spin - 360.0;
glutPostRedisplay();
}

void reshape(int w,int h)
{
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-5.0,5.0,-5.0,5.0,-5.0,5.0);

gluLookAt(1.0,1.0,0.5,0.0,0.0,0.0,0.0,1.0,0.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void mouse(int button,int state,int x,int y)
{
switch(button)
{
case GLUT_LEFT_BUTTON :
if (state==GLUT_DOWN)
glutIdleFunc(spinDisplay); //���д���
break;
case GLUT_MIDDLE_BUTTON :
if(state==GLUT_DOWN)
glutIdleFunc(NULL);
break;
default :
break;
}
}

/*void myIdle(void)  
{     
	angle +=0.2f;    
	if( angle >= 360.0f )      
		angle = 0.0f;   
	display();  
}*/


int main(int argc, char* argv[])
{
	// GLUT初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);	
	glEnable(GL_DEPTH_TEST);  
      
	glEnable(GL_TEXTURE_2D);    // 启用纹理
	//texGround = load_texture("2.bmp");  //加载纹理
	//texWall = load_texture("lby.bmp");
       texWall = load_texture("zhengmian.bmp");
	glutDisplayFunc(&display);   //注册函数
        glutReshapeFunc(reshape);
        glutMouseFunc(mouse);
        glutKeyboardFunc(keyboard);
	//glutIdleFunc(&myIdle);  
	glutMainLoop(); //循环调用
	return 0;
}

