#include <windows.h>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "PassengerTruck.h"


void PassengerTruck::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2){
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

void PassengerTruck::Drawsquare( float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4){
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x3,y3,z3);
	glVertex3f(x4,y4,z4);
	glEnd();
}

void PassengerTruck::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
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

void PassengerTruck::t_door(int x , int cc , int tex1 ,int tex2){
	Double_face(505, -495, 150,505, -495, 50,505, -245,50,505, -245, 150,tex1,1,1,tex2,1,1);
	Double_face(505, -495, -50,505, -495, -150,505, -245, -150,505, -245, -50,tex1,1,1,tex2,1,1);
    Double_face(505, -315, 150,505, -315, -150,505, -245, -150,505, -245, 150,tex1,1,1,tex2,1,1);
	square(515,-495,-150,515,-495,150,495,-495,150,495,-495,-150,cc,0.5,0.5);
	glPushMatrix();
	glTranslated(0,0,x);
	Double_face(505, -495, 50,505, -495, -50,505, -315,-50,505, -315,50,tex1,1,1,tex2,1,1);
	glPopMatrix();
}


void PassengerTruck::chair(int bs){
	square(95,-465,-30,95,-465,30,45,-465,30,45,-465,-30,bs,1,1);
	square(95,-465,30,95,-465,-30,115,-380,-30,115,-380,30,bs,1,1);
	glColor3f(0,0,0);
	Drawsquare(65,-465,0,85,-465,0,85,-495,0,65,-495,0);
	glColor3f(1,1,1);
	square(45,-458,30,45,-458,-30,45,-465,-30,45,-465,30,bs,1,1);
	square(88,-458,-30,88,-458,30,45,-458,30,45,-458,-30,bs,1,1);
	square(88,-458,30,88,-458,-30,108, -380,-30,108,-380,30,bs,1,1);
	Drawsquare(108,-380,30,108,-380,-30,115, -380,-30,115,-380,30);
    Drawsquare(45,-465,30,45,-458,30,88,-458,30,95,-465,30);
	Drawsquare(88, -458,30,95, -465,30,115, -380,30,108, -380,30);
	Drawsquare(45, -465,-30,45, -458,-30,88, -458,-30,95, -465,-30);
    Drawsquare(88, -458,-30,95, -465,-30,115, -380,-30,108, -380,-30);
}

void PassengerTruck::truck(float x,int p1,int p2,int f_w,int f_d,int u_f,int l_d,int r_d,int fr,int cc,int movZ){
// length = 600, width = 300, height = 250;
	//front
	////
	//square(279.5, -494, 150,504, -494, 150,504, -245, 150,279.5, -245, 150,r_f,1,1);
	square(279.5, -494, 150,310, -494, 150,310, -245, 150,279.5, -245, 150,f_w,1,1);
	square(454, -494, 150,504, -494, 150,504, -245, 150,454, -245, 150,f_w,1,1);
	square(279.5, -494, 150,504, -494, 150,504, -368, 150,279.5, -368, 150,f_d,1,1);
	////
 	//square(110.5, -494, 150,-114, -494, 150,-114, -245, 150,110.5, -245, 150,l_f,1,1);
	square(-64, -494, 150,-114, -494, 150,-114, -245, 150,-64, -245, 150,f_w,1,1);
	square(110.5, -494, 150,80, -494, 150,80, -245, 150,110.5, -245, 150,f_w,1,1);
	square(80, -494, 150,-64, -494, 150,-64, -368, 150,80, -368, 150,f_d,1,1);
	//
  	square(-114, -274.2, 150,504, -274.2, 150,504, -245, 150,-114, -245, 150,u_f,1,1);
    //back
	////
	//square(279.5, -494, 150,504, -494, 150,504, -245, 150,279.5, -245, 150,r_f,1,1);
	square(279.5, -494,-150,310, -494, -150,310, -245, -150,279.5, -245, -150,f_w,1,1);
	square(454, -494, -150,504, -494, -150,504, -245, -150,454, -245, -150,f_w,1,1);
	square(279.5, -494, -150,504, -494, -150,504, -368, -150,279.5, -368, -150,f_d,1,1);
	////
 	//square(110.5, -494, 150,-114, -494, 150,-114, -245, 150,110.5, -245, 150,l_f,1,1);
	square(-64, -494, -150,-114, -494, -150,-114, -245, -150,-64, -245, -150,f_w,1,1);
	square(110.5, -494, -150,80, -494, -150,80, -245, -150,110.5, -245, -150,f_w,1,1);
	square(80, -494, -150,-64, -494, -150,-64, -368, -150,80, -368, -150,f_d,1,1);
	//
  	square(-114, -274.2, -150,504, -274.2, -150,504, -245, -150,-114, -245, -150,u_f,1,1);
	//doors
    glPushMatrix();
    glTranslated(-x,0,0);
  	square(110.5, -494, 151,195,-494, 151,195,-274.2, 151,110.5, -274.2, 151,l_d,1,1);
	square(110.5, -494, -151,195,-494, -151,195,-274.2, -151,110.5, -274.2,-151,l_d,1,1);
	glPopMatrix();
    glPushMatrix();
    glTranslated(x,0,0);
	square(195, -494, 151,279.5,-494, 151,279.5,-274.2, 151,195, -274.2, 151,r_d,1,1);
	square(195, -494, -151,279.5,-494, -151,279.5,-274.2, -151,195, -274.2,-151,r_d,1,1);
	glPopMatrix();
	//top,down,left,right
	square(-114, -495, 150,504, -495, 150,504,-495, -150,-114,-495,-150,fr,10,10);
	square(-114, -244, 150,504, -244, 150,504, -244, -150,-114, -244, -150,cc,1,1);
	//square(495, -495, 150,495, -495, -150,495, -245, -150,495, -245, 150,cc,1,1);
	if (!(movZ<=150 && movZ>=-150))
	square(-105, -495, -150,-105, -245, -150,-105, -245, 150,-105, -495, 150,cc,1,1);
	t_door(x,cc,p1,p2);
	//windows
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0f,1.0f,1.0f,0.2f);
	Drawsquare(-64,-368,150,80,-368,150,80,-275,150,-64,-275,150);
	Drawsquare(310,-368,150,454,-368,150,454,-275,150,310,-275,150);
	glDisable(GL_BLEND);
}


void PassengerTruck::PassengersTruck(float x ,int p1,int p2,int bs,int cc,int movX ,int movY,int movZ,int f_w,int f_d,int u_f,int l_d,int r_d,int fr){
    //if (!(movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-4228 && movX>=-6045 || x!=0))
	//if (movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-4228 && movX>=-6045 || x!=0){
	glPushMatrix(); 
	glScaled(1,1,0.7);
	glTranslated(360,0,-165);
	chair(bs);
	glTranslated(0,0,70);
	chair(bs);
	glTranslated(-110,0,0);
	chair(bs);
	glTranslated(0,0,-70);
	chair(bs);
	glTranslated(-240,0,0);
	chair(bs);
	glTranslated(0,0,70);
	chair(bs);
	glTranslated(-110,0,0);
	chair(bs);
	glTranslated(0,0,-70);
	chair(bs);
	glTranslated(0,0,270);
	chair(bs);
	glTranslated(0,0,70);
	chair(bs);
	glTranslated(110,0,0);
	chair(bs);
	glTranslated(0,0,-70);
	chair(bs);
	glTranslated(240,0,0);
	chair(bs);
	glTranslated(0,0,70);
	chair(bs);
	glTranslated(110,0,0);
	chair(bs);
	glTranslated(0,0,-70);
	chair(bs);
	glPopMatrix();
	if (!(movZ<=150 && movZ>=-150 && movY<-245))
	truck(x,cc,cc,f_w,f_d,u_f,l_d,r_d,fr,cc,movZ);
	else
	truck(x,p1,p2,f_w,f_d,u_f,l_d,r_d,fr,cc,movZ);
	
}



