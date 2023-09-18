#include <windows.h>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "environment.h"


void environment::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2){
    glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(x1,y1,z1);
	glTexCoord2d(r1,0);
	glVertex3f(x2,y2,z2);
	glTexCoord2d(r1,r2);
	glVertex3f(x3,y3,z3);
	glTexCoord2d(0,r2);
	glVertex3f(x4,y4,z4);
	glEnd();
};

void environment::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
				 float x3,float y3,float z3,float x4,float y4,float z4 , int tex1 , float r1 ,float r2, int tex2 , float r3 ,float r4){

	glEnable(GL_CULL_FACE);
	glPushMatrix();
	glCullFace(GL_BACK);
	square(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,tex1,r1,r2); //back
    glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	square(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,tex2,r3,r4); //back
	glDisable(GL_CULL_FACE);
    glPopMatrix();
}

void environment::DrawCube(float x1, float y1, float z1, float x2, float y2 , float z2, float x3, float y3,float z3,float x4,float y4,float z4,
			  float x5,float y5, float z5, float x6, float y6, float z6, float x7, float y7, float z7,float x8,float y8,float z8,
			  int pic1,int r1,int r2,int pic2,int r3,int r4,int pic3,int r5,int r6,int pic4,int r7,int r8,int pic5,int r9,int r10,int pic6,int r11,int r12)
{
square(x2,y2,z2,x4,y4,z4,x3,y3,z3,x1,y1,z1,pic1,r1,r2);
square(x4,y4,z4,x6,y6,z6,x5,y5,z5,x3,y3,z3,pic2,r3,r4);
square(x6,y6,z6,x8,y8,z8,x7,y7,z7,x5,y5,z5,pic3,r5,r6);
square(x8,y8,z8,x2,y2,z2,x1,y1,z1,x7,y7,z7,pic4,r7,r8);
square(x7,y7,z7,x1,y1,z1,x3,y3,z3,x5,y5,z5,pic5,r9,r10);
//square(x8,y8,z8,x2,y2,z2,x4,y4,z4,x6,y6,z6,pic6,r11,r12);
}

void environment::skybox(int wall , int back , int right, int top , int down){
	square(-30000,-500,-8000,500,-500,-8000,500,4500,-8000,-30000,4500,-8000,wall,2,1);
	square(-30000,-500,8000,500,-500,8000,500,4500,8000,-30000,4500,8000,back,1,1);
	//square(-30000,-500,8000,-30000,-500,-8000,-30000,4500,-8000,-30000,4500,8000,tex3,1,1);
	square(-30000,4500,-8000,500,4500,-8000,500,4500,8000,-30000,4500,8000,top,1,1);
	square(-30000,-500,-8000,500,-500,-8000,500,-500,8000,-30000,-500,8000,top,50,50);
	//square(500,-500,8000,500,-500,-8000,500,4500,-8000,500,4500,8000,tex1,1,1);
}

void environment::skybox2(int ff, int b1 , int top1 , int d1){
	square(-30000,-500,-8000,500,-500,-8000,500,4500,-8000,-30000,4500,-8000,ff,2,1);
	square(-30000,-500,8000,500,-500,8000,500,4500,8000,-30000,4500,8000,b1,1,1);
	square(-30000,-500,8000,-30000,-500,-8000,-30000,4500,-8000,-30000,4500,8000,ff,1,1);
	square(-30000,4500,-8000,500,4500,-8000,500,4500,8000,-30000,4500,8000,top1,1,1);
	square(-30000,-500,-8000,500,-500,-8000,500,-500,8000,-30000,-500,8000,ff,50,50);
	//square(500,-500,8000,500,-500,-8000,500,4500,-8000,500,4500,8000,tex1,1,1);
}

void environment::skybox3(int tex1 , int tex2 , int tex3 , int tex4 , int tex5 , int tex6 , int tex7 ){

	square(-30000,-500,-8000,500,-500,-8000,500,4500,-8000,-30000,4500,-8000,tex1,2,1);
	square(-30000,-500,8000,500,-500,8000,500,4500,8000,-30000,4500,8000,tex2,1,1);
	square(-30000,-500,8000,-30000,-500,-8000,-30000,4500,-8000,-30000,4500,8000,tex3,1,1);
	square(-30000,4500,-8000,500,4500,-8000,500,4500,8000,-30000,4500,8000,tex4,1,1);
	square(-30000,-500,-8000,500,-500,-8000,500,-500,8000,-30000,-500,8000,tex5,50,50);
	square(500,-500,8000,500,-500,-8000,500,4500,-8000,500,4500,8000,tex6,1,1);
	square(500,-500,8000,500,-500,-8000,500,4500,-8000,500,4500,8000,tex3,1,1);
    square(-30005, -498, 170,1498,-498,150,1498,-498,-150, -30005,-498,-170,tex7,70,1); //rail
}

void environment::tree(int tex8,int tex9){
  glPushMatrix();
   glTranslated(0,-490,1700);
  glScaled(25,25,25);
  glBindTexture(GL_TEXTURE_2D, tex8);
  glBegin(GL_QUADS);
  //1
  glTexCoord2d(0, 0);
  glVertex3d(-1.5,7,1.5);
  glTexCoord2d(1, 0);
  glVertex3d(2.5,7,1.5);
  glTexCoord2d(1, 1);
  glVertex3d(2.5,7,-2.5);
  glTexCoord2d(0, 1);
  glVertex3d(-1.5,7,-2.5);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, tex8);
  glBegin(GL_TRIANGLES);
  //1
  glTexCoord2d(0, 0);
  glVertex3d(-1.5,7,1.5);
  glTexCoord2d(1, 0);
  glVertex3d(2.5,7,1.5);
  glTexCoord2d(1, 1);
  glVertex3d(0.5,13,-0.5);

  glTexCoord2d(0, 0);
  glVertex3d(-1.5,7,-2.5);
  glTexCoord2d(1, 0);
  glVertex3d(2.5,7,-2.5);
  glTexCoord2d(1, 1);
  glVertex3d(0.5,13,-0.5);
  
  glTexCoord2d(0, 0);
  glVertex3d(-1.5,7,1.5);
  glTexCoord2d(1, 0);
  glVertex3d(-1.5,7,-2.5);
  glTexCoord2d(1, 1);
  glVertex3d(0.5,13,-0.5);

  glTexCoord2d(0, 0);
  glVertex3d(-1.5,7,1.5);
  glTexCoord2d(1, 0);
  glVertex3d(-1.5,7,-2.5);
  glTexCoord2d(1, 1);
  glVertex3d(0.5,13,-0.5);

  glTexCoord2d(0, 0);
  glVertex3d(2.5,7,1.5);
  glTexCoord2d(1, 0);
  glVertex3d(2.5,7,-2.5);
  glTexCoord2d(1, 1);
  glVertex3d(0.5,13,-0.5);

  glEnd();
  glPushMatrix();
  glTranslated(0,-1.15,0);
  glBindTexture(GL_TEXTURE_2D,tex9);
  glBegin(GL_QUADS);
  //1
  glTexCoord2d(0, 0);
  glVertex3d(0,0,0);
  glTexCoord2d(1, 0);
  glVertex3d(1,0,0);
  glTexCoord2d(1, 1);
  glVertex3d(1,8,0);
  glTexCoord2d(0, 1);
  glVertex3d(0,8,0);
  //2
  glTexCoord2d(0, 0);
  glVertex3d(0,0,-1);
  glTexCoord2d(1, 0);
  glVertex3d(1,0,-1);
  glTexCoord2d(1, 1);
  glVertex3d(1,8,-1);
  glTexCoord2d(0, 1);
  glVertex3d(0,8,-1);
  
  //3
  glTexCoord2d(0, 0);
  glVertex3d(0,0,0);
  glTexCoord2d(1, 0);
  glVertex3d(0,0,-1);
  glTexCoord2d(1, 1);
  glVertex3d(0,8,-1);
  glTexCoord2d(0, 1);
  glVertex3d(0,8,0);
  
  //4
  glTexCoord2d(0, 0);
  glVertex3d(1,0,0);
  glTexCoord2d(1, 0);
  glVertex3d(1,0,-1);
  glTexCoord2d(1, 1);
  glVertex3d(1,8,-1);
  glTexCoord2d(0, 1);
  glVertex3d(1,8,0);
  glEnd();
   glPopMatrix();
  glPopMatrix();
}

void environment::trees(int tex8 , int tex9){
    glPushMatrix();
    for (int i=0;i<=20;i++){
		glTranslated(-1500,0,0);
		tree(tex8,tex9);
	}
	glPopMatrix();
    glPushMatrix();
	glTranslated(0,0,-3400);
	for (int i=0;i<=20;i++){
		glTranslated(-1500,0,0);
		tree(tex8,tex9);
	}
	glPopMatrix();
}

void environment::build1(int tex12){
  
  Double_face(-300,0,0,300,0,0,300,850,0,-300,850,0,tex12,1,0.5,tex12,1,0.5);
  glBindTexture(GL_TEXTURE_2D,tex12);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 0);
  glVertex3d(-300,0,-300);
  glTexCoord2d(1, 0);
  glVertex3d(300,0,-300);
  glTexCoord2d(1, 1);
  glVertex3d(300,850,-300);
  glTexCoord2d(0, 1);
  glVertex3d(-300,850,-300);
  
  //3
  glTexCoord2d(0, 0);
  glVertex3d(-299,0,0);
  glTexCoord2d(1, 0);
  glVertex3d(-299,0,-300);
  glTexCoord2d(1, 1);
  glVertex3d(-299,850,-300);
  glTexCoord2d(0, 1);
  glVertex3d(-299,850,0);
  
  //4
  glTexCoord2d(0, 0);
  glVertex3d(299,0,0);
  glTexCoord2d(1, 0);
  glVertex3d(299,0,-300);
  glTexCoord2d(1, 1);
  glVertex3d(299,850,-300);
  glTexCoord2d(0, 1);
  glVertex3d(299,850,0);

  glEnd();
}

void environment::build2(int tex10,int tex11){
	glPushMatrix();
	DrawCube(-2000,-500,2000,-2000,0,2000,-2000,-500,1500,-2000,0,1500,-2500,-500,1500,-2500,0,1500,-2500,-500,2000,-2500,0,2000,tex10,5,5,tex10,5,5,tex10,5,5,tex10,5,5,tex11,1,1,tex11,1,1);
	glPopMatrix();
}

void environment::buildings(int tex10,int tex11,int tex12){
	 glPushMatrix();
	 glTranslated(-10000,0,1000);
    for (int i=0;i<=10;i++){
		glTranslated(3000,0,0);
		build2(tex10,tex11);
	}
	glPopMatrix();
    glPushMatrix();
	glTranslated(-10000,0,-5400);
	for (int i=0;i<=10;i++){
		glTranslated(-3000,0,0);
		build2(tex10,tex11);
	}
	glPopMatrix();
    glPushMatrix();
	glTranslated(-18000,-900,-3900);
	for (int i=0;i<=10;i++){
		glTranslated(3000,0,0);
	    build1(tex12);
	}
	glTranslated(-25500,0,7800);
	for (int i=0;i<=10;i++){
		glTranslated(-3000,0,0);
	    build1(tex12);
	}
	glPopMatrix();
}


void environment::env(int tex1 , int tex2 , int tex3 , int tex4 , int tex5 , int tex6 , int tex7 , int tex8 , int tex9, int tex10 , int tex11, int tex12
					  , int wall , int back , int right, int top , int down, int ff, int b1 , int top1 , int d1){
	skybox3(tex1,tex2,tex3,tex4,tex5,tex6,tex7);
	/*glPushMatrix();
	glTranslated(-30000,0,0);
	skybox(wall ,back ,right, tex4 ,down);
	glTranslated(-30000,0,0);
	skybox2(ff,b1 ,top1 ,d1);
	glPopMatrix();*/
	trees(tex8,tex9);
	buildings(tex10,tex11,tex12);
}
