/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  colormat.c
 *  After initialization, the program will be in
 *  ColorMaterial mode.  Interaction:  pressing the 
 *  mouse buttons will change the diffuse reflection values.
 */
#include "glut.h"
#include <stdlib.h>
#include "candide.h"
#include "glaux.h"
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
int s1=0,s2=0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
AUX_RGBImageRec *image;
unsigned char *pdata;

void FaceTexture(void)
{
	image=auxDIBImageLoad("zhengmian.bmp");

	if(!pdata!=NULL)
		free(pdata);
	pdata=(BYTE*)malloc(256*256*3*sizeof(BYTE));
	if(!pdata)
		exit(0);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	gluScaleImage(GL_RGB,image->sizeX,image->sizeY,GL_UNSIGNED_BYTE,image->data,
		256,256,GL_UNSIGNED_BYTE,pdata);

	glTexImage2D(GL_TEXTURE_2D,0,3,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,pdata);
}


void initlights(void)
{
   GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat position[] = {0.0, 0.0, 1.0, 1.0};
   GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
   GLfloat mat_specular[] = {0.0, 0.0, 1.0, 1.0};
   GLfloat mat_shininess[] = {100.0};

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
//void init(void)
//{
//   glClearColor(0.0, 0.0, 0.0, 0.0);
//   glEnable(GL_DEPTH_TEST);
//   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
//           0, 1, 12, 4, &ctrlpoints[0][0][0]);
//   glEnable(GL_MAP2_VERTEX_3);
//   glEnable(GL_AUTO_NORMAL);
//   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
//   initlights();       /* for lighted version only */
//}

void init(void) 
{

	//glClearColor(0.0,0.0,0.0,0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);

	glTexImage2D(GL_TEXTURE_2D,0,3,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,pdata);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_DECAL);
   //glClearColor (0.0, 0.0, 0.0, 0.0);
   //glShadeModel (GL_SMOOTH);
  // glEnable(GL_DEPTH_TEST);
  // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
   //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
   //initlights();
   
   //glEnable(GL_AUTO_NORMAL);
  // glColorMaterial(GL_FRONT, GL_DIFFUSE);
  // glEnable(GL_COLOR_MATERIAL);
}

void display(void)
{

	
	//int m;
 //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 //  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
 //  //	glClear (GL_COLOR_BUFFER_BIT);
 //   glPushMatrix();
	//   glTranslatef (0.0, 0.0, 0.0);
	//   glRotatef ((GLfloat) s1, 0.0, 0.0, 1.0);
	//   glRotatef ((GLfloat) s2, 0.0, 1.0, 0.0);
	//   glTranslatef (0.0, 0.0, 0.0);
	//   glPushMatrix();
	//   glBegin(GL_TRIANGLES);
	//  for( m=0;m<184;m++)
	//  {
	//	glVertex3fv(&candide_vertices[candide_list[m][0]][0]);
	//	glNormal3fv(&candide_vertices[candide_list[m][0]][0]);
	//	glVertex3fv(&candide_vertices[candide_list[m][1]][0]);
	//	glNormal3fv(&candide_vertices[candide_list[m][1]][0]);
	//	glVertex3fv(&candide_vertices[candide_list[m][2]][0]);
	//	glNormal3fv(&candide_vertices[candide_list[m][2]][0]);
	//  }
	// glEnd();
	//   glPopMatrix();


 //  glPopMatrix();
 //  glFlush ();
		//int m;
/*	glPushMatrix();*///把当前距阵压入距阵堆栈中
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  //      glTranslatef(0.0f, 0.0f, -3.0);//把当前距阵乘以变换阵
  //      glRotatef(wAngleX, 1.0f, 0.0f, 0.0f);//把当前距阵乘以旋转阵
  //      glRotatef(wAngleY, 0.0f, 1.0f, 0.0f);
  //      glRotatef(wAngleZ, 0.0f, 0.0f, 1.0f);
	 // glColor3f(1.0f,0.0f,0.0f);
	  
	/*  glBegin(GL_TRIANGLES);
	  for(m=0;m<184;m++)
	  {
		glVertex3fv(&candide_vertices[candide_list[m][0]][0]);
		glVertex3fv(&candide_vertices[candide_list[m][1]][0]);
		glVertex3fv(&candide_vertices[candide_list[m][2]][0]);
	  }
	glEnd();*/
    //glPopMatrix();
	init(); 
    FaceTexture();
	glPushMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        //glTranslatef(0.0f, 0.0f, -3.0);//把当前距阵乘以变换阵
        //glRotatef(wAngleX, 1.0f, 0.0f, 0.0f);//把当前距阵乘以旋转阵
        //glRotatef(wAngleY, 0.0f, 1.0f, 0.0f);
        //glRotatef(wAngleZ, 0.0f, 0.0f, 1.0f);
		//glBindTexture(GL_TEXTURE_2D/*, texture[0]*/);
	  //glColor3f(1.0f,0.0f,0.0f);
	glEnable(GL_TEXTURE_2D);
	glTranslatef(0.0f, 0.0f, -0.0);//把当前距阵乘以变换阵

        glRotatef(s1, 0.0f, 1.0f, 0.0f);
        glRotatef(s2, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	    glBegin(GL_TRIANGLES);

			
		    /*glColor3f(1.0,0.0,0.0);*/
			//glNormal3f(0.0,1.0,0.0);
			/*glTexCoord2d(0.25,0.25);glVertex3f(-5.0,5.0,5.0);
			glTexCoord2d(0.75,0.25);glVertex3f(-5.0,-5.0,5.0);
			glTexCoord2d(0.75,0.75);glVertex3f(-5.0,-5.0,-5.0);
			glTexCoord2d(0.25,0.75);glVertex3f(-5.0,5.0,-5.0);*/
//0
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
			glTexCoord2d(0.391667,0.431458);glVertex3f(0.217000f,0.117000f,-0.024000f);

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
	glPopMatrix();
	glFlush();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
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

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
