/* 2015071 20151340 张皓霖*/
//报告在doc文件夹下
//照片在sourcefiles/face2.bmp
//在colormat基础上增删调整后，增加了光照、阴影、抗锯齿，改变了背景颜色，突出了人脸的高清效果
#include "GL/glut.h"
#include <stdlib.h>
#include "candide.h"
#include "gl/glaux.h"
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
int s1 = 0, s2 = 0;
AUX_RGBImageRec *image;
unsigned char *pdata;
void FaceTexture(void)
{
	image = auxDIBImageLoad("face2.bmp");
	if (!pdata != NULL)
		free(pdata);
	pdata = (BYTE*)malloc(256 * 256 * 3 * sizeof(BYTE));
	if (!pdata)
		exit(0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelStorei(GL_UNPACK_ALIGNMENT,1)控制的是所读取数据的对齐方式，默认4字节对齐，即一行的图像数据字节数必须是4的整数倍，即读取数据时，读取4个字节用来渲染一行，之后读取4字节数据用来渲染第二行。
	//对RGB 3字节像素而言，若一行10个像素，即30个字节，在4字节对齐模式下，OpenGL会读取32个字节的数据，若不加注意，会导致glTextImage中致函数的读取越界，从而全面崩溃。
	gluScaleImage(GL_RGB, image->sizeX, image->sizeY, GL_UNSIGNED_BYTE, image->data,
		256, 256, GL_UNSIGNED_BYTE, pdata);
	//gluScaleImage这个函数用适当的像素存储模式改变一个像素图像的大小来读取源图像的像素数据然后把像素写入新的目标图像
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, pdata);
	//glteximage2d是一个OpenGL函数，功能是根据指定的参数，生成一个2D纹理（Texture）
}
void initlights(void)
{
	GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat position[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_specular[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	////创建指定的光源,light可以是GL_LIGHT0、GL_LIGHT1，pname定义的是光源的属性，它指定了一个命名参数。params表示表示pname属性将要被设置的值  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//指定用于光照计算的当前材质属性。参数face的取值可以是GL_FRONT、GL_BACK或GL_FRONT_AND_BACK，指出材质属性将应用于物体的哪面。
}
void init(void)
{
	//OpenGl设定  抗锯齿
	glEnable(GL_BLEND);             //启用混合功能，将图形颜色同周围颜色相混合    
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POLYGON_SMOOTH);     //多边形抗锯齿    
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	glEnable(GL_LINE_SMOOTH);        //线抗锯齿    
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);       //点抗锯齿    
	glHint(GL_POINT_SMOOTH, GL_NICEST);
	// ------------启用光照计算-----------------------
	glEnable(GL_LIGHTING);
	// 指定环境光强度（RGBA）
	GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 指定散射光强度（RGBA）
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	// 指定镜面光强度（RGBA）
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 指定材料的镜面光反射属性
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// 设置光源0的环境光成分
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	// 设置光源0的散射光成分
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	// 设置光源0的镜面光成分
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	// 启用光源0
	glEnable(GL_LIGHT0);
	// 启用颜色追踪
	glEnable(GL_COLOR_MATERIAL);
	// 设置多边形正面的环境光和散射光材料属性，追踪glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	// 设置多边形正面的镜面光材料属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	// 指定镜面指数
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	// 指定清除色
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	// 法线规范化
	glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	//指定“目标像素与当前像素在z方向上值大小比较”的函数，符合该函数关系的目标像素才进行绘制，否则对目标像素不予绘制。
	glFrontFace(GL_CW);
	//glFrontFace()是opengl的初级命令，有两个基本作用，一是可以用来用在某些特殊场合（比如剔除面片），二是可以提高渲染效率。
	glShadeModel(GL_SMOOTH); 
	//设置着色模式
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, pdata);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//就是重复边界的纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void display(void)
{
	init();
	FaceTexture();
	glPushMatrix();//当你做了一些移动或旋转等变换后，使用glPushMatrix(), OpenGL 会把这个变换后的位置和角度保存起来。
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0.0f, 0.0f, -0.0);//把当前距阵乘以变换阵
	glRotatef(s1, 0.0f, 1.0f, 0.0f);//其中,angle为旋转的角度,单位为度  围绕坐标轴旋转 XYZ
	glRotatef(s2, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0.501041, 0.005000); glVertex3f(0.000000f, 1.061000f, -0.371000f); //glTexCoord*()函数设置了当前的纹理坐标.所有后续的顶点函数把这些纹理坐标与它们相关联, 直到再次调用
	glTexCoord2d(0.587917, 0.079375); glVertex3f(0.174000f, 0.800000f, -0.024000f); //glVertex3f指定一个顶点
	glTexCoord2d(0.600208, 0.014375); glVertex3f(0.217000f, 1.039000f, -0.371000f); //glTexCoord2f(s,t)设置当前纹理坐标为(s,t,0,1),
	glTexCoord2d(0.501041, 0.005000); glVertex3f(0.000000f, 1.061000f, -0.371000f);
	glTexCoord2d(0.587917, 0.079375); glVertex3f(0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.412708, 0.080208); glVertex3f(-0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.501041, 0.005000); glVertex3f(0.000000f, 1.061000f, -0.371000f);
	glTexCoord2d(0.412708, 0.080208); glVertex3f(-0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.400833, 0.014375); glVertex3f(-0.217000f, 1.039000f, -0.371000f);
	glTexCoord2d(0.587917, 0.079375); glVertex3f(0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.600208, 0.014375); glVertex3f(0.217000f, 1.039000f, -0.371000f);
	glTexCoord2d(0.712708, 0.068333); glVertex3f(0.457000f, 0.909000f, -0.328000f);
	glTexCoord2d(0.412708, 0.080208); glVertex3f(-0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.400833, 0.014375); glVertex3f(-0.217000f, 1.039000f, -0.371000f);
	glTexCoord2d(0.289167, 0.068542); glVertex3f(-0.457000f, 0.909000f, -0.328000f);
	glTexCoord2d(0.587917, 0.079375); glVertex3f(0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.712708, 0.068333); glVertex3f(0.457000f, 0.909000f, -0.328000f);
	glTexCoord2d(0.716250, 0.181458); glVertex3f(0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.587917, 0.079375); glVertex3f(0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.716250, 0.181458); glVertex3f(0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.587917, 0.079375); glVertex3f(0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.412708, 0.080208); glVertex3f(-0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.412708, 0.080208); glVertex3f(-0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.283958, 0.179792); glVertex3f(-0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.412708, 0.080208); glVertex3f(-0.174000f, 0.800000f, -0.024000f);
	glTexCoord2d(0.289167, 0.068542); glVertex3f(-0.457000f, 0.909000f, -0.328000f);
	glTexCoord2d(0.283958, 0.179792); glVertex3f(-0.435000f, 0.626000f, -0.111000f);
	//10
	glTexCoord2d(0.712708, 0.068333); glVertex3f(0.457000f, 0.909000f, -0.328000f);
	glTexCoord2d(0.716250, 0.181458); glVertex3f(0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.783958, 0.240625); glVertex3f(0.610000f, 0.539000f, -0.328000f);
	glTexCoord2d(0.716250, 0.181458); glVertex3f(0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.783958, 0.240625); glVertex3f(0.610000f, 0.539000f, -0.328000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.716250, 0.181458); glVertex3f(0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.703125, 0.295208); glVertex3f(0.391000f, 0.374000f, 0.0300000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.716250, 0.181458); glVertex3f(0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.703125, 0.295208); glVertex3f(0.391000f, 0.374000f, 0.0300000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.703125, 0.295208); glVertex3f(0.391000f, 0.374000f, 0.0300000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.502292, 0.342708); glVertex3f(0.000000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.502292, 0.342708); glVertex3f(0.000000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.298125, 0.295208); glVertex3f(-0.391000f, 0.374000f, 0.030000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.502292, 0.203542); glVertex3f(0.000000f, 0.539000f, 0.085000f);
	glTexCoord2d(0.283958, 0.179792); glVertex3f(-0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.298125, 0.295208); glVertex3f(-0.391000f, 0.374000f, 0.030000f);
	glTexCoord2d(0.283958, 0.179792); glVertex3f(-0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.298125, 0.295208); glVertex3f(-0.391000f, 0.374000f, 0.030000f);
	//20
	glTexCoord2d(0.283958, 0.179792); glVertex3f(-0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.217083, 0.239583); glVertex3f(-0.610000f, 0.539000f, -0.328000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.289167, 0.068542); glVertex3f(-0.457000f, 0.909000f, -0.328000f);
	glTexCoord2d(0.283958, 0.179792); glVertex3f(-0.435000f, 0.626000f, -0.111000f);
	glTexCoord2d(0.217083, 0.239583); glVertex3f(-0.610000f, 0.539000f, -0.328000f);
	glTexCoord2d(0.783958, 0.240625); glVertex3f(0.610000f, 0.539000f, -0.328000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.783958, 0.425625); glVertex3f(0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.783958, 0.425625); glVertex3f(0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.703333, 0.324375); glVertex3f(0.391000f, 0.322000f, 0.0300000f);
	glTexCoord2d(0.661458, 0.374167); glVertex3f(0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.703125, 0.295208); glVertex3f(0.391000f, 0.374000f, 0.0300000f);
	glTexCoord2d(0.703333, 0.324375); glVertex3f(0.391000f, 0.322000f, 0.0300000f);
	glTexCoord2d(0.703125, 0.295208); glVertex3f(0.391000f, 0.374000f, 0.0300000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.703333, 0.324375); glVertex3f(0.391000f, 0.322000f, 0.0300000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.703333, 0.324375); glVertex3f(0.391000f, 0.322000f, 0.0300000f);
	glTexCoord2d(0.661458, 0.374167); glVertex3f(0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.512917, 0.378542); glVertex3f(0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.502292, 0.342708); glVertex3f(0.000000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.512917, 0.378542); glVertex3f(0.022000f, 0.213000f, 0.063000f);
	//30
	glTexCoord2d(0.502292, 0.342708); glVertex3f(0.000000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.490208, 0.378542); glVertex3f(-0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.490208, 0.378542); glVertex3f(-0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.299167, 0.324167); glVertex3f(-0.391000f, 0.322000f, 0.030000f);
	glTexCoord2d(0.343125, 0.374167); glVertex3f(-0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.298125, 0.295208); glVertex3f(-0.391000f, 0.374000f, 0.030000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.299167, 0.324167); glVertex3f(-0.391000f, 0.322000f, 0.030000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.298125, 0.295208); glVertex3f(-0.391000f, 0.374000f, 0.030000f);
	glTexCoord2d(0.299167, 0.324167); glVertex3f(-0.391000f, 0.322000f, 0.030000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.299167, 0.324167); glVertex3f(-0.391000f, 0.322000f, 0.030000f);
	glTexCoord2d(0.343125, 0.374167); glVertex3f(-0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.218542, 0.424583); glVertex3f(-0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.217083, 0.239583); glVertex3f(-0.610000f, 0.539000f, -0.328000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.218542, 0.424583); glVertex3f(-0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.756042, 0.609583); glVertex3f(0.550000f, -0.250000f, -0.328000f);
	glTexCoord2d(0.783958, 0.425625); glVertex3f(0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.783958, 0.425625); glVertex3f(0.609000f, 0.148000f, -0.328000f);
	//40
	glTexCoord2d(0.656875, 0.442292); glVertex3f(0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.558958, 0.568333); glVertex3f(0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.343125, 0.441458); glVertex3f(-0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.442917, 0.569583); glVertex3f(-0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.218542, 0.424583); glVertex3f(-0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.245417, 0.608542); glVertex3f(-0.550000f, -0.250000f, -0.328000f);
	glTexCoord2d(0.218542, 0.424583); glVertex3f(-0.609000f, 0.148000f, -0.328000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.524792, 0.705833); glVertex3f(0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.563125, 0.633333); glVertex3f(0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.563125, 0.633333); glVertex3f(0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.558958, 0.568333); glVertex3f(0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.442917, 0.569583); glVertex3f(-0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.439167, 0.632500); glVertex3f(-0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.477292, 0.705625); glVertex3f(-0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.439167, 0.632500); glVertex3f(-0.120000f, -0.265000f, 0.100000f);
	//50
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.524792, 0.705833); glVertex3f(0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.477292, 0.705625); glVertex3f(-0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.502292, 0.807708); glVertex3f(0.000000f, -0.591000f, 0.107000f);
	glTexCoord2d(0.502292, 0.941875); glVertex3f(0.000000f, -0.852000f, 0.063000f);
	glTexCoord2d(0.591458, 0.908333); glVertex3f(0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.502292, 0.807708); glVertex3f(0.000000f, -0.591000f, 0.107000f);
	glTexCoord2d(0.502292, 0.941875); glVertex3f(0.000000f, -0.852000f, 0.063000f);
	glTexCoord2d(0.411250, 0.908125); glVertex3f(-0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.502292, 0.616042); glVertex3f(0.000000f, -0.222000f, 0.210000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.502292, 0.616042); glVertex3f(0.000000f, -0.222000f, 0.210000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.502292, 0.342708); glVertex3f(0.000000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.512917, 0.378542); glVertex3f(0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.490208, 0.378542); glVertex3f(-0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.524792, 0.705833); glVertex3f(0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.565000, 0.707083); glVertex3f(0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.565000, 0.707083); glVertex3f(0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.551875, 0.732083); glVertex3f(0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.551875, 0.732083); glVertex3f(0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.502292, 0.740625); glVertex3f(0.000000f, -0.461000f, 0.124000f);
	//60
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.477292, 0.705625); glVertex3f(-0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.436250, 0.707917); glVertex3f(-0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.436250, 0.707917); glVertex3f(-0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.449792, 0.732083); glVertex3f(-0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.502292, 0.717083); glVertex3f(0.000000f, -0.417000f, 0.142000f);
	glTexCoord2d(0.449792, 0.732083); glVertex3f(-0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.502292, 0.740625); glVertex3f(0.000000f, -0.461000f, 0.124000f);
	glTexCoord2d(0.436250, 0.707917); glVertex3f(-0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.449792, 0.732083); glVertex3f(-0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.401250, 0.728333); glVertex3f(-0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.374792, 0.727917); glVertex3f(-0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.436250, 0.707917); glVertex3f(-0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.401250, 0.728333); glVertex3f(-0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.565000, 0.707083); glVertex3f(0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.551875, 0.732083); glVertex3f(0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.596875, 0.728333); glVertex3f(-0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.627083, 0.727708); glVertex3f(0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.565000, 0.707083); glVertex3f(0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.596875, 0.728333); glVertex3f(-0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.524792, 0.705833); glVertex3f(0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.565000, 0.707083); glVertex3f(0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.627083, 0.727708); glVertex3f(0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.565000, 0.707083); glVertex3f(0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.477292, 0.705625); glVertex3f(-0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.436250, 0.707917); glVertex3f(-0.123000f, -0.410000f, 0.063000f);
	//70
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.374792, 0.727917); glVertex3f(-0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.436250, 0.707917); glVertex3f(-0.123000f, -0.410000f, 0.063000f);
	glTexCoord2d(0.550417, 0.733333); glVertex3f(0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.566667, 0.758958); glVertex3f(0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.596875, 0.728333); glVertex3f(0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.627083, 0.727708); glVertex3f(0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.566667, 0.758958); glVertex3f(0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.596875, 0.728333); glVertex3f(0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.502292, 0.776875); glVertex3f(0.000000f, -0.526000f, 0.150000f);
	glTexCoord2d(0.550417, 0.733333); glVertex3f(0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.566667, 0.758958); glVertex3f(0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.502292, 0.776875); glVertex3f(0.000000f, -0.526000f, 0.150000f);
	glTexCoord2d(0.502292, 0.740625); glVertex3f(0.000000f, -0.461000f, 0.124000f);
	glTexCoord2d(0.550417, 0.733333); glVertex3f(0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.502292, 0.776875); glVertex3f(0.000000f, -0.526000f, 0.150000f);
	glTexCoord2d(0.502292, 0.740625); glVertex3f(0.000000f, -0.461000f, 0.124000f);
	glTexCoord2d(0.449375, 0.733333); glVertex3f(-0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.502292, 0.776875); glVertex3f(0.000000f, -0.526000f, 0.150000f);
	glTexCoord2d(0.449375, 0.733333); glVertex3f(-0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.435417, 0.758958); glVertex3f(-0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.449375, 0.733333); glVertex3f(-0.100000f, -0.461000f, 0.050000f);
	glTexCoord2d(0.435417, 0.758958); glVertex3f(-0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.401250, 0.728333); glVertex3f(-0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.374792, 0.727917); glVertex3f(-0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.435417, 0.758958); glVertex3f(-0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.401250, 0.728333); glVertex3f(-0.200000f, -0.461000f, -0.024000f);
	glTexCoord2d(0.502292, 0.776875); glVertex3f(0.000000f, -0.526000f, 0.150000f);
	glTexCoord2d(0.502292, 0.807708); glVertex3f(0.000000f, -0.591000f, 0.107000f);
	glTexCoord2d(0.566667, 0.758958); glVertex3f(0.123000f, -0.508000f, 0.063000f);
	//80
	glTexCoord2d(0.502292, 0.776875); glVertex3f(0.000000f, -0.526000f, 0.150000f);
	glTexCoord2d(0.502292, 0.807708); glVertex3f(0.000000f, -0.591000f, 0.107000f);
	glTexCoord2d(0.435417, 0.758958); glVertex3f(-0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.627083, 0.727708); glVertex3f(0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.591458, 0.908333); glVertex3f(0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.566667, 0.758958); glVertex3f(0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.502292, 0.807708); glVertex3f(0.000000f, -0.591000f, 0.107000f);
	glTexCoord2d(0.591458, 0.908333); glVertex3f(0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.566667, 0.758958); glVertex3f(0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.374792, 0.727917); glVertex3f(-0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.411250, 0.908125); glVertex3f(-0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.435417, 0.758958); glVertex3f(-0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.502292, 0.807708); glVertex3f(0.000000f, -0.591000f, 0.107000f);
	glTexCoord2d(0.411250, 0.908125); glVertex3f(-0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.435417, 0.758958); glVertex3f(-0.123000f, -0.508000f, 0.063000f);
	glTexCoord2d(0.656875, 0.442292); glVertex3f(0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.706875, 0.760208); glVertex3f(0.470000f, -0.600000f, -0.328000f);
	glTexCoord2d(0.591458, 0.908333); glVertex3f(0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.682292, 0.724167); glVertex3f(0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.627083, 0.727708); glVertex3f(0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.591458, 0.908333); glVertex3f(0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.682292, 0.724167); glVertex3f(0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.756042, 0.609583); glVertex3f(0.550000f, -0.250000f, -0.328000f);
	glTexCoord2d(0.706875, 0.760208); glVertex3f(0.470000f, -0.600000f, -0.328000f);
	glTexCoord2d(0.682292, 0.724167); glVertex3f(0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.627083, 0.727708); glVertex3f(0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.682292, 0.724167); glVertex3f(0.357000f, -0.461000f, -0.050000f);
	//90
	glTexCoord2d(0.592917, 0.618542); glVertex3f(0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.682292, 0.724167); glVertex3f(0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.756042, 0.609583); glVertex3f(0.550000f, -0.250000f, -0.328000f);
	glTexCoord2d(0.682292, 0.724167); glVertex3f(0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.343125, 0.441458); glVertex3f(-0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.291875, 0.759167); glVertex3f(-0.470000f, -0.600000f, -0.328000f);
	glTexCoord2d(0.411250, 0.908125); glVertex3f(-0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.319521, 0.723750); glVertex3f(-0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.374792, 0.727917); glVertex3f(-0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.411250, 0.908125); glVertex3f(-0.174000f, -0.809000f, 0.000000f);
	glTexCoord2d(0.319521, 0.723750); glVertex3f(-0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.245417, 0.608542); glVertex3f(-0.550000f, -0.250000f, -0.328000f);
	glTexCoord2d(0.291875, 0.759167); glVertex3f(-0.470000f, -0.600000f, -0.328000f);
	glTexCoord2d(0.319521, 0.723750); glVertex3f(-0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.374792, 0.727917); glVertex3f(-0.246000f, -0.461000f, -0.000000f);
	glTexCoord2d(0.319521, 0.723750); glVertex3f(-0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.408542, 0.617917); glVertex3f(-0.174000f, -0.244000f, 0.037000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.319521, 0.723750); glVertex3f(-0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.245417, 0.608542); glVertex3f(-0.550000f, -0.250000f, -0.328000f);
	glTexCoord2d(0.319521, 0.723750); glVertex3f(-0.357000f, -0.461000f, -0.050000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.512917, 0.378542); glVertex3f(0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.533750, 0.478958); glVertex3f(0.065000f, 0.028000f, 0.050000f);
	//100
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.558958, 0.568333); glVertex3f(0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.533750, 0.478958); glVertex3f(0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.558958, 0.568333); glVertex3f(0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.533750, 0.478958); glVertex3f(0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.490208, 0.378542); glVertex3f(-0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.467917, 0.476458); glVertex3f(-0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.442917, 0.569583); glVertex3f(-0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.467917, 0.476458); glVertex3f(-0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.442917, 0.569583); glVertex3f(-0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.467917, 0.476458); glVertex3f(-0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.512917, 0.378542); glVertex3f(0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.533750, 0.478958); glVertex3f(0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.533750, 0.478958); glVertex3f(0.065000f, 0.028000f, 0.050000f);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	glTexCoord2d(0.502292, 0.616042); glVertex3f(0.000000f, -0.222000f, 0.210000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	glTexCoord2d(0.502292, 0.616042); glVertex3f(0.000000f, -0.222000f, 0.210000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.467917, 0.476458); glVertex3f(-0.065000f, 0.028000f, 0.050000);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	//110
	glTexCoord2d(0.490208, 0.378542); glVertex3f(-0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.467917, 0.476458); glVertex3f(-0.065000f, 0.028000f, 0.050000);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	glTexCoord2d(0.512917, 0.378542); glVertex3f(0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.490208, 0.378542); glVertex3f(-0.022000f, 0.213000f, 0.063000f);
	glTexCoord2d(0.502292, 0.455625); glVertex3f(0.000000f, 0.068000f, 0.100000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.697500, 0.390208); glVertex3f(0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.697500, 0.390208); glVertex3f(0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.691667, 0.395417); glVertex3f(0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.695208, 0.427083); glVertex3f(0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.696042, 0.431875); glVertex3f(0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.696042, 0.431875); glVertex3f(0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.758958, 0.351250); glVertex3f(0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.661458, 0.374167); glVertex3f(0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.697500, 0.390208); glVertex3f(0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.661458, 0.374167); glVertex3f(0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.697500, 0.390208); glVertex3f(0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.697500, 0.390208); glVertex3f(0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.691667, 0.395417); glVertex3f(0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.656875, 0.442292); glVertex3f(0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.697292, 0.537500); glVertex3f(0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.696042, 0.431875); glVertex3f(0.387000f, 0.117000f, -0.067000f);
	//120
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.656875, 0.442292); glVertex3f(0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.696042, 0.431875); glVertex3f(0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.695208, 0.427083); glVertex3f(0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.696042, 0.431875); glVertex3f(0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.611875, 0.387292); glVertex3f(0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.611875, 0.387292); glVertex3f(0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.612917, 0.396875); glVertex3f(0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.609375, 0.427083); glVertex3f(0.217000f, 0.126000f, -0.013000f);
	glTexCoord2d(0.608333, 0.429375); glVertex3f(0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.558958, 0.568333); glVertex3f(0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.608333, 0.429375); glVertex3f(0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.570000, 0.342708); glVertex3f(0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.661458, 0.374167); glVertex3f(0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.611875, 0.387292); glVertex3f(0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.661458, 0.374167); glVertex3f(0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.611875, 0.387292); glVertex3f(0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.611875, 0.387292); glVertex3f(0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.612917, 0.396875); glVertex3f(0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.609375, 0.427083); glVertex3f(0.217000f, 0.126000f, -0.013000f);
	glTexCoord2d(0.608333, 0.429375); glVertex3f(0.217000f, 0.117000f, -0.024000f);

	//130
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.656875, 0.442292); glVertex3f(0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.608333, 0.429375); glVertex3f(0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.656875, 0.442292); glVertex3f(0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.558958, 0.568333); glVertex3f(0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.608333, 0.429375); glVertex3f(0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.388750, 0.387292); glVertex3f(-0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.388750, 0.387292); glVertex3f(-0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.374147, 0.387292); glVertex3f(-0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.388125, 0.427083); glVertex3f(0.217000f, 0.126000f, -0.013000f);
	glTexCoord2d(0.391667, 0.431458); glVertex3f(0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.442917, 0.569583); glVertex3f(-0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.391667, 0.431458); glVertex3f(-0.2470000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.431458, 0.343958); glVertex3f(-0.130000f, 0.278000f, 0.107000f);
	glTexCoord2d(0.343125, 0.374167); glVertex3f(-0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.388750, 0.387292); glVertex3f(-0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.343125, 0.374167); glVertex3f(-0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.388750, 0.387292); glVertex3f(-0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.388750, 0.387292); glVertex3f(-0.217000f, 0.201000f, -0.013000f);
	glTexCoord2d(0.374147, 0.387292); glVertex3f(-0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.388125, 0.427083); glVertex3f(-0.217000f, 0.126000f, -0.013000f);
	glTexCoord2d(0.391667, 0.431458); glVertex3f(-0.217000f, 0.117000f, -0.024000f);
	//140
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.343125, 0.441458); glVertex3f(-0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.391667, 0.431458); glVertex3f(-0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.343125, 0.441458); glVertex3f(-0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.442917, 0.569583); glVertex3f(-0.109000f, -0.157000f, 0.037000f);
	glTexCoord2d(0.391667, 0.431458); glVertex3f(-0.217000f, 0.117000f, -0.024000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.304375, 0.391667); glVertex3f(-0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.304375, 0.391667); glVertex3f(-0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.309375, 0.395417); glVertex3f(-0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.308533, 0.427708); glVertex3f(-0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.305833, 0.434375); glVertex3f(-0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.305833, 0.434375); glVertex3f(-0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.243333, 0.343958); glVertex3f(-0.522000f, 0.278000f, -0.111000f);
	glTexCoord2d(0.343125, 0.374167); glVertex3f(-0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.304375, 0.391667); glVertex3f(-0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.343125, 0.374167); glVertex3f(-0.304000f, 0.225000f, -0.002000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.304375, 0.391667); glVertex3f(-0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.304375, 0.391667); glVertex3f(-0.387000f, 0.201000f, -0.056000f);
	glTexCoord2d(0.309375, 0.395417); glVertex3f(-0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.308533, 0.427708); glVertex3f(-0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.305833, 0.434375); glVertex3f(-0.387000f, 0.117000f, -0.067000f);
	//150
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.343125, 0.441458); glVertex3f(-0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.305833, 0.434375); glVertex3f(-0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.343125, 0.441458); glVertex3f(-0.304000f, 0.104000f, -0.000000f);
	glTexCoord2d(0.303958, 0.538750); glVertex3f(-0.387000f, -0.100000f, -0.045000f);
	glTexCoord2d(0.305833, 0.434375); glVertex3f(-0.387000f, 0.117000f, -0.067000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.543958, 0.610208); glVertex3f(0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.563125, 0.633333); glVertex3f(0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.524792, 0.705833); glVertex3f(0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.563125, 0.633333); glVertex3f(0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.457708, 0.610208); glVertex3f(-0.080000f, -0.220000f, 0.150000f);
	glTexCoord2d(0.439167, 0.632500); glVertex3f(-0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.502292, 0.632708); glVertex3f(0.000000f, -0.265000f, 0.124000f);
	glTexCoord2d(0.477292, 0.705625); glVertex3f(-0.043000f, -0.396000f, 0.150000f);
	glTexCoord2d(0.439167, 0.632500); glVertex3f(-0.120000f, -0.265000f, 0.100000f);
	glTexCoord2d(0.333958, 0.425208); glVertex3f(-0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.382500, 0.388333); glVertex3f(-0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.382500, 0.425208); glVertex3f(-0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.333958, 0.388333); glVertex3f(-0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.333958, 0.425208); glVertex3f(-0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.382500, 0.388333); glVertex3f(-0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.660625, 0.388333); glVertex3f(0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.660625, 0.425208); glVertex3f(0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.612500, 0.425208); glVertex3f(0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.660625, 0.388333); glVertex3f(0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.612500, 0.388333); glVertex3f(0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.612500, 0.425208); glVertex3f(0.265000f, 0.115000f, -0.0300000f);
	//160
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.333958, 0.388333); glVertex3f(-0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.333958, 0.425208); glVertex3f(-0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.382500, 0.388333); glVertex3f(-0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.382500, 0.425208); glVertex3f(-0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.612500, 0.388333); glVertex3f(0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.612500, 0.425208); glVertex3f(0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.660625, 0.388333); glVertex3f(0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.660625, 0.425208); glVertex3f(0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.333958, 0.388333); glVertex3f(-0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.309375, 0.395417); glVertex3f(-0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.333958, 0.388333); glVertex3f(-0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.309375, 0.395417); glVertex3f(-0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.333958, 0.388333); glVertex3f(-0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.382500, 0.388333); glVertex3f(-0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.343958, 0.387292); glVertex3f(-0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.382500, 0.388333); glVertex3f(-0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.374147, 0.387292); glVertex3f(-0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.382500, 0.388333); glVertex3f(-0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.374147, 0.387292); glVertex3f(-0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.433333, 0.414792); glVertex3f(-0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.382500, 0.425208); glVertex3f(-0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.388125, 0.427083); glVertex3f(-0.217000f, 0.126000f, -0.013000f);
	//170
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.382500, 0.425208); glVertex3f(-0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.388125, 0.427083); glVertex3f(-0.217000f, 0.126000f, -0.013000f);
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.333958, 0.425208); glVertex3f(-0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.382500, 0.425208); glVertex3f(-0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.308533, 0.431458); glVertex3f(-0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.333958, 0.425208); glVertex3f(-0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.308533, 0.427708); glVertex3f(-0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.268750, 0.417292); glVertex3f(-0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.333958, 0.425208); glVertex3f(-0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.308533, 0.427708); glVertex3f(-0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.660625, 0.388333); glVertex3f(0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.691667, 0.395417); glVertex3f(0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.660625, 0.388333); glVertex3f(0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.691667, 0.395417); glVertex3f(0.387000f, 0.186000f, -0.056000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.660625, 0.388333); glVertex3f(0.348000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.612500, 0.388333); glVertex3f(0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.659167, 0.387292); glVertex3f(0.304000f, 0.204000f, -0.000000f);
	glTexCoord2d(0.612500, 0.388333); glVertex3f(0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.612917, 0.396875); glVertex3f(0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.612500, 0.388333); glVertex3f(0.265000f, 0.200000f, -0.0300000f);
	glTexCoord2d(0.612917, 0.396875); glVertex3f(0.217000f, 0.186000f, -0.013000f);
	glTexCoord2d(0.732500, 0.418125); glVertex3f(0.470000f, 0.148000f, -0.111000f);
	glTexCoord2d(0.660625, 0.425208); glVertex3f(0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.695208, 0.427083); glVertex3f(0.387000f, 0.126000f, -0.056000f);
	//180
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.660625, 0.425208); glVertex3f(0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.695208, 0.427083); glVertex3f(0.387000f, 0.126000f, -0.056000f);
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.660625, 0.425208); glVertex3f(0.348000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.612500, 0.425208); glVertex3f(0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.695208, 0.431458); glVertex3f(0.304000f, 0.122000f, -0.000000f);
	glTexCoord2d(0.612500, 0.425208); glVertex3f(0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.305833, 0.434375); glVertex3f(0.217000f, 0.126000f, -0.013000f);
	glTexCoord2d(0.567917, 0.413750); glVertex3f(0.130000f, 0.148000f, -0.000000f);
	glTexCoord2d(0.612500, 0.425208); glVertex3f(0.265000f, 0.115000f, -0.0300000f);
	glTexCoord2d(0.609375, 0.427083); glVertex3f(0.217000f, 0.126000f, -0.013000f);
	glEnd();
	glPopMatrix();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //打开窗口
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	/*该函数定义一个视图矩阵，并与当前矩阵相乘。
第一组eyex, eyey,eyez 相机在世界坐标的位置
第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
第三组upx,upy,upz 相机向上的方向在世界坐标中的方向
你把相机想象成为你自己的脑袋：
第一组数据就是脑袋的位置
第二组数据就是眼睛看的物体的位置
第三组就是头顶朝向的方向（因为你可以歪着头看同一个物体）。*/
	glMatrixMode(GL_PROJECTION);//将当前矩阵指定为投影矩阵
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5*(GLfloat)h / (GLfloat)w,
		1.5*(GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-1.5*(GLfloat)w / (GLfloat)h,
		1.5*(GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);//将当前矩阵指定为模型视图
	glLoadIdentity();
}
void mouse(int button, int state, int x, int y) //鼠标交互
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			diffuseMaterial[0] += 0.1;
			if (diffuseMaterial[0] > 1.0)
				diffuseMaterial[0] = 0.0;
			glColor4fv(diffuseMaterial);
			glutPostRedisplay();
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN) {
			diffuseMaterial[1] += 0.1;
			if (diffuseMaterial[1] > 1.0)
				diffuseMaterial[1] = 0.0;
			glColor4fv(diffuseMaterial);
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			diffuseMaterial[2] += 0.1;
			if (diffuseMaterial[2] > 1.0)
				diffuseMaterial[2] = 0.0;
			glColor4fv(diffuseMaterial);
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y) //键盘交互
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);//设置初始显示模式
	glutInitWindowSize(500, 500);//设置窗口大小
	glutInitWindowPosition(100, 100);//设置初始窗口的位置
	glutCreateWindow(argv[0]);//创建一个顶级窗口
	init();//初始化
	glutDisplayFunc(display);//注册一个绘图函数， 这样操作系统在必要时刻就会对窗体进行重新绘制操作
	glutReshapeFunc(reshape);//当窗口尺寸改变时，图形比例不发生变化
	glutMouseFunc(mouse);//处理鼠标click事件
	glutKeyboardFunc(keyboard);//处理键盘click事件
	glutMainLoop();//让所有的与“事件”有关的函数调用无限循环
	return 0;
}

