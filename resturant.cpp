#include <windows.h>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "resturant.h"


void resturant::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2){
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

void resturant::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
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

void resturant::t_door(int x , int cc , int tex1 ,int tex2){
	Double_face(505, -495, 150,505, -495, 50,505, -245,50,505, -245, 150,tex1,1,1,tex2,1,1);
	Double_face(505, -495, -50,505, -495, -150,505, -245, -150,505, -245, -50,tex1,1,1,tex2,1,1);
    Double_face(505, -315, 150,505, -315, -150,505, -245, -150,505, -245, 150,tex1,1,1,tex2,1,1);
	square(515,-495,-150,515,-495,150,495,-495,150,495,-495,-150,cc,0.5,0.5);
	glPushMatrix();
	glTranslated(0,0,x);
	Double_face(505, -495, 50,505, -495, -50,505, -315,-50,505, -315,50,tex1,1,1,tex2,1,1);
	glPopMatrix();
}

void resturant::truck2(float x,int p1,int p2,int cc,int tr_b,int fr){
	t_door(x,cc,p1,p2);
	square(-105, -490, -150,495, -490, -150,495, -245, -150,-105, -245, -150,tr_b,1,1);//right
    square(-105, -490, 150,495, -490, 150,495, -245, 150,-105, -245, 150,tr_b,1,1);//left
   //top & down
	square(-114, -493, 150,504, -493, 150,504,-493, -150,-114,-493,-150,fr,10,10);
	square(-114, -244, 150,504, -244, 150,504, -244, -150,-114, -244, -150,cc,1,1);
}

void resturant::chairs(int wallt,int ch){
	glPushMatrix();
	glTranslated(20,-450,-10);
		
	square(-5, -5, 5,5, -5,5,5, -5,-5,-5, -5, -5,wallt,1,1);
	square(-5, -7, 5,5, -7,5,5, -7,-5,-5, -7, -5,wallt,1,1);
	square(5, -7,-5,5, -7,5,5,-5,5,5, -5, -5,wallt,1,1);
	square(-5, -7, -5,-5, -7,5,-5, -5,5,-5, -5, -5,wallt,1,1);
	square(-5, -7, -5,5, -7,5,5, -5,5,-5, -5, 5,wallt,1,1);
	square(-5, -7, 5,5, -7,5,5, -5,-5,-5, -5, -5,wallt,1,1);
	square(5, -5, -5,5, -5,5,5,20,5,5,20,-5,ch,1,1);

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3d(5, -5,-5);     //a
	glVertex3d(5, -40, -5);
	glVertex3d(5, -5, 5);     //a`
	glVertex3d(5, -40, 5);
	glVertex3d(-5, -5, -5);   //d
	glVertex3d(-5, -40, -5);
	glVertex3d(-5, -5, 5);
	glVertex3d(-5, -40, 5);
	glColor3f(1,1,1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20,-450,-10);

	square(-5, -5, 5,5, -5,5,5, -5,-5,-5, -5, -5,wallt,1,1);
	square(-5, -7, 5,5, -7,5,5, -7,-5,-5, -7, -5,wallt,1,1);
	square(5, -7,-5,5, -7,5,5,-5,5,5, -5, -5,wallt,1,1);
	square(-5, -7, -5,-5, -7,5,-5, -5,5,-5, -5, -5,wallt,1,1);
	square(-5, -7, -5,5, -7,5,5, -5,5,-5, -5, 5,wallt,1,1);
	square(-5, -7, 5,5, -7,5,5, -5,-5,-5, -5, -5,wallt,1,1);
	square(-5, -5,5,-5, -5,-5,-5,20,-5,-5,20,5,ch,1,1);

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3d(-5,-5,5);     //a
	glVertex3d(-5, -40, 5);
	glVertex3d(-5, -5, -5);     //a`
	glVertex3d(-5, -40,- 5);
	glVertex3d(5, -5, 5);   //d
	glVertex3d(5, -40, 5);
	glVertex3d(5, -5, -5);    //d`
	glVertex3d(5, -40, -5);
	glColor3f(1,1,1);
	glEnd();
	glPopMatrix();
 }


void resturant::table(int tbb,int wallt,int ch)
  {
	glPushMatrix();
	glTranslated(0,-440,0);
	square(-5, -10, -20,20, -10,-20,20, -5, -20,-5, -5, -20,tbb,1,1);
	square(-5, -10, 20,20, -10,20,20, -5, 20,-5, -5,20,tbb,1,1);
	square(-5, -10, -20,20, -10,-20,20, -10, 20,-5, -10,20,tbb,10,10);
	square(20, -10,20,20, -10,-20,20, -5, -20,20, -5, -20,tbb,1,1);
	square(-5, -10, 20,-5, -10,-20,-5, -5,-20,-5, -5,20,tbb,1,1);
	square(20,-5, -20,20, -5,20,-5, -5, 20,-5, -5,-20,tbb,1,1);

	glLineWidth(7);
	glBegin(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3d(20, -10, 20);    //a`
	glVertex3d(20, -50, 20);
	glVertex3d(20, -10, -20);   //a
	glVertex3d(20, -50, -20);
	glVertex3d(-5, -10, -20);   //d
	glVertex3d(-5, -50, -20);
	glVertex3d(-5, -10, 20);     //d`
	glVertex3d(-5, -50, 20);
	glColor3f(1,1,1);
	glEnd();
    glPopMatrix();
    glPushMatrix();
    chairs(wallt,ch);
	glTranslated(0,0,18);
	chairs(wallt,ch);
	glPopMatrix();
  } 

void resturant::restaurant(int movX ,int movY,int movZ,int x,int cc,int tbb,int wallt,int ch,int tr_b,int wallt2,int fr,int p1,int p2,int p,int pp){
	if (!(movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-1700 && movX>=-4105))
	truck2(x,p1,p2,cc,tr_b,fr);
	if (movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-1125 && movX>=-4205|| x!=0){
	glPushMatrix();
	glTranslated(20,-10,85);
	glScaled(1.8,1,1.8);
    table(tbb,wallt,ch);
	glTranslated(95,0,0);
    table(tbb,wallt,ch);
	glTranslated(95,0,0);
    table(tbb,wallt,ch);
	 glTranslated(0,0,-88);
    table(tbb,wallt,ch);
	glTranslated(-95,0,0);
    table(tbb,wallt,ch);
	 glTranslated(-95,0,0);
    table(tbb,wallt,ch);
	 glPopMatrix();
    Double_face(-115, -495, -150,505, -495, -150,505, -245, -150,-115, -245, -150,tr_b,1,1,wallt,5,5);//back
    square(-105, -495, 150,495, -495, 150,495, -495, -150,-105, -495, -150,wallt2,10,10); //bottom
	//Double_face(495, -245, 150,495, -495, 150,495, -495, -150,495, -245, -150,wallt,5,5,cc,1,1);//right
	//square(-105, -495, -150,-105, -495, 150,-105, -245, 150,-105, -245,-150,wallt,5,5); //left
	Double_face(505, -245, -150,505, -248, 150,-115, -248, 150,-115, -245, -150,cc,1,1,wallt,2,2);//top
	Double_face(-115, -495,150,505, -495,150,505, -245,150,-115, -245,150,wallt,1,1,tr_b,1,1);

	 //pictures
	square(360, -370, -135,460, -370, -135,460, -300, -135,360, -300,-135,p,1,1);
    glLineWidth(7);
    glBegin(GL_LINE_LOOP);
	glVertex3d(460, -370, -135);
	glVertex3d(460, -300, -135);
	glVertex3d(360, -300,-135);
	glVertex3d(360, -370, -135);
	glEnd();

	square(45, -370, -135,-55, -370, -135,-55, -300, -135,45, -300,-135,p,1,1);
	glLineWidth(7);
	glBegin(GL_LINE_LOOP);
	glVertex3d(-55, -370, -135);
	glVertex3d(-55, -300, -135);
	glVertex3d(45, -300,-135);
	glVertex3d(45, -370, -135);
	glEnd();

	square(260, -440, -135,180, -440, -135,180, -300, -135,260, -300,-135,pp,1,1);
	}
	if (movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-1125 && movX>=-4205|| x!=0){
	t_door(x,cc,p1,p2);
	
	}}
