#include <windows.h>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "kitcheen.h"

void kitcheen::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2){
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


void kitcheen::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
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

void kitcheen::t_door(int x , int cc , int tex1 ,int tex2){
	Double_face(505, -495, 150,505, -495, 50,505, -245,50,505, -245, 150,tex1,1,1,tex2,1,1);
	Double_face(505, -495, -50,505, -495, -150,505, -245, -150,505, -245, -50,tex1,1,1,tex2,1,1);
    Double_face(505, -315, 150,505, -315, -150,505, -245, -150,505, -245, 150,tex1,1,1,tex2,1,1);
	square(515,-495,-150,515,-495,150,495,-495,150,495,-495,-150,cc,0.5,0.5);
	glPushMatrix();
	glTranslated(0,0,x);
	Double_face(505, -495, 50,505, -495, -50,505, -315,-50,505, -315,50,tex1,1,1,tex2,1,1);
	glPopMatrix();
}

void kitcheen::truck2(float x,int p1,int p2,int cc,int tr_b,int fr){
	t_door(x,cc,p1,p2);
	square(-105, -490, -150,495, -490, -150,495, -245, -150,-105, -245, -150,tr_b,1,1);//right
    square(-105, -490, 150,495, -490, 150,495, -245, 150,-105, -245, 150,tr_b,1,1);//left
   //top & down
	square(-114, -493, 150,504, -493, 150,504,-493, -150,-114,-493,-150,fr,10,10);
	square(-114, -244, 150,504, -244, 150,504, -244, -150,-114, -244, -150,cc,1,1);
}

void kitcheen::k_table(int wall1){
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);//up
	glTexCoord2d(0,1);
	glVertex3d(200, -430, -50);
	glTexCoord2d(1,1);
	glVertex3d(100, -430, -50);
	glTexCoord2d(0,0);
	glVertex3d(100, -430, 50);
	glTexCoord2d(1,0);
	glVertex3d(200, -430, 50);
	glEnd();
	glPopMatrix();
	//down
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(200, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, -50);
	glTexCoord2d(0,0);
	glVertex3d(100, -440, 50);
	glTexCoord2d(1,0);
	glVertex3d(200, -440, 50);
	glEnd();
	glPopMatrix();
	//back
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(200, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, -50);
	glTexCoord2d(0,0);
	glVertex3d(100, -430, -50);
	glTexCoord2d(1,0);
	glVertex3d(200, -430, -50);
	glEnd();
	glPopMatrix();
	//front
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(200, -430, 50);
	glTexCoord2d(1,1);
	glVertex3d(100, -430, 50);
	glTexCoord2d(0,0);
	glVertex3d(100, -440, 50);
	glTexCoord2d(1,0);
	glVertex3d(200, -440, 50);
	glEnd();
	glPopMatrix();
	//right
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(200, -430, -50);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, -50);
	glTexCoord2d(0,0);
	glVertex3d(200, -440, 50);
	glTexCoord2d(1,0);
	glVertex3d(200, -430, 50);
	glEnd();
	glPopMatrix();
	//left
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(100, -430, -50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, -50);
	glTexCoord2d(0,0);
	glVertex3d(100, -440, 50);
	glTexCoord2d(1,0);
	glVertex3d(100, -430, 50);
	glEnd();
	glPopMatrix();
	//leg1
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(190, -440, 50);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, 50);
	glTexCoord2d(0,0);
	glVertex3d(200, -495, 50);
	glTexCoord2d(1,0);
	glVertex3d(190, -495, 50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(190, -440, 45);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, 45);
	glTexCoord2d(0,0);
	glVertex3d(200, -495, 45);
	glTexCoord2d(1,0);
	glVertex3d(190, -495, 45);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(190, -440, 50);
	glTexCoord2d(1,1);
	glVertex3d(190, -440, 45);
	glTexCoord2d(0,0);
	glVertex3d(190, -495, 45);
	glTexCoord2d(1,0);
	glVertex3d(190, -495, 50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(200, -440, 50);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, 45);
	glTexCoord2d(0,0);
	glVertex3d(200, -495, 45);
	glTexCoord2d(1,0);
	glVertex3d(200, -495, 50);
	glEnd();
	glPopMatrix();
	//leg2///////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(110, -440, 50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, 50);
	glTexCoord2d(0,0);
	glVertex3d(100, -495, 50);
	glTexCoord2d(1,0);
	glVertex3d(110, -495, 50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(110, -440, 45);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, 45);
	glTexCoord2d(0,0);
	glVertex3d(100, -495, 45);
	glTexCoord2d(1,0);
	glVertex3d(110, -495, 45);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(100, -440, 50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, 45);
	glTexCoord2d(0,0);
	glVertex3d(100, -495, 45);
	glTexCoord2d(1,0);
	glVertex3d(100, -495, 50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(110, -440, 50);
	glTexCoord2d(1,1);
	glVertex3d(110, -440, 45);
	glTexCoord2d(0,0);
	glVertex3d(110, -495, 45);
	glTexCoord2d(1,0);
	glVertex3d(110, -495, 50);
	glEnd();
	glPopMatrix();
	//leg3/////////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(190, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, -50);
	glTexCoord2d(0,0);
	glVertex3d(200, -495, -50);
	glTexCoord2d(1,0);
	glVertex3d(190, -495, -50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(190, -440, -45);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, -45);
	glTexCoord2d(0,0);
	glVertex3d(200, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(190, -495, -45);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(200, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(200, -440, -45);
	glTexCoord2d(0,0);
	glVertex3d(200, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(200, -495, -50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(190, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(190, -440, -45);
	glTexCoord2d(0,0);
	glVertex3d(190, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(190, -495, -50);
	glEnd();
	glPopMatrix();
	//leg4////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(110, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, -50);
	glTexCoord2d(0,0);
	glVertex3d(100, -495, -50);
	glTexCoord2d(1,0);
	glVertex3d(110, -495, -50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(110, -440, -45);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, -45);
	glTexCoord2d(0,0);
	glVertex3d(100, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(110, -495, -45);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(100, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(100, -440, -45);
	glTexCoord2d(0,0);
	glVertex3d(100, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(100, -495, -50);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  wall1); 
	glBegin(GL_QUADS);
	glTexCoord2d(0,1);
	glVertex3d(110, -440, -50);
	glTexCoord2d(1,1);
	glVertex3d(110, -440, -45);
	glTexCoord2d(0,0);
	glVertex3d(110, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(110, -495, -50);
	glEnd();
	glPopMatrix();
	
}

void kitcheen::k_chair(int chaire){
    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair f
	glTexCoord2d(1,1);
	glVertex3d(170, -380, -100);
	glTexCoord2d(0,1);
	glVertex3d(120, -380, -100);
	glTexCoord2d(0,0);
	glVertex3d(120, -450, -100);
	glTexCoord2d(1,0);
	glVertex3d(170, -450, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair f
	glTexCoord2d(1,1);
	glVertex3d(170, -380, -90);
	glTexCoord2d(0,1);
	glVertex3d(120, -380, -90);
	glTexCoord2d(0,0);
	glVertex3d(120, -450, -90);
	glTexCoord2d(1,0);
	glVertex3d(170, -450, -90);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair fr
	glTexCoord2d(1,1);
	glVertex3d(170, -380, -100);
	glTexCoord2d(0,1);
	glVertex3d(170, -380, -90);
	glTexCoord2d(0,0);
	glVertex3d(170, -450, -90);
	glTexCoord2d(1,0);
	glVertex3d(170, -450, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair fl
	glTexCoord2d(1,1);
	glVertex3d(120, -380, -100);
	glTexCoord2d(0,1);
	glVertex3d(120, -380, -90);
	glTexCoord2d(0,0);
	glVertex3d(120, -450, -90);
	glTexCoord2d(1,0);
	glVertex3d(120, -450, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair ft
	glTexCoord2d(1,1);
	glVertex3d(120, -380, -100);
	glTexCoord2d(0,1);
	glVertex3d(170, -380, -90);
	glTexCoord2d(0,0);
	glVertex3d(170, -380, -90);
	glTexCoord2d(1,0);
	glVertex3d(120, -380, -100);
	glEnd();
	glPopMatrix();
	///////////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair d
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(120, -450, -100);
	glTexCoord2d(0,0);
	glVertex3d(120, -450, -40);
	glTexCoord2d(1,0);
	glVertex3d(170, -450, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair d2
	glTexCoord2d(1,1);
	glVertex3d(170, -440, -100);
	glTexCoord2d(0,1);
	glVertex3d(120, -440, -100);
	glTexCoord2d(0,0);
	glVertex3d(120, -440, -40);
	glTexCoord2d(1,0);
	glVertex3d(170, -440, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair d3
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(120, -440, -100);
	glTexCoord2d(0,0);
	glVertex3d(120, -440, -40);
	glTexCoord2d(1,0);
	glVertex3d(120, -450, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair d4
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(170, -440, -100);
	glTexCoord2d(0,0);
	glVertex3d(170, -440, -40);
	glTexCoord2d(1,0);
	glVertex3d(170, -450, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg1
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(160, -450, -100);
	glTexCoord2d(0,0);
	glVertex3d(160, -495, -100);
	glTexCoord2d(1,0);
	glVertex3d(170, -495, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg1'2'
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -95);
	glTexCoord2d(0,1);
	glVertex3d(160, -450, -95);
	glTexCoord2d(0,0);
	glVertex3d(160, -495, -95);
	glTexCoord2d(1,0);
	glVertex3d(170, -495, -95);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg1 '3'
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(170, -450, -95);
	glTexCoord2d(0,0);
	glVertex3d(170, -495, -95);
	glTexCoord2d(1,0);
	glVertex3d(170, -495, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg'4'
	glTexCoord2d(1,1);
	glVertex3d(160, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(160, -450, -95);
	glTexCoord2d(0,0);
	glVertex3d(160, -495, -95);
	glTexCoord2d(1,0);
	glVertex3d(160, -495, -100);
	glEnd();
	glPopMatrix();
	/////////////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg2
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -40);
	glTexCoord2d(0,1);
	glVertex3d(160, -450, -40);
	glTexCoord2d(0,0);
	glVertex3d(160, -495, -40);
	glTexCoord2d(1,0);
	glVertex3d(170, -495, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg2 '2'
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -45);
	glTexCoord2d(0,1);
	glVertex3d(160, -450, -45);
	glTexCoord2d(0,0);
	glVertex3d(160, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(170, -495, -45);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg2 '3'
	glTexCoord2d(1,1);
	glVertex3d(170, -450, -40);
	glTexCoord2d(0,1);
	glVertex3d(170, -450, -45);
	glTexCoord2d(0,0);
	glVertex3d(170, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(170, -495, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg2 '4'
	glTexCoord2d(1,1);
	glVertex3d(160, -450, -40);
	glTexCoord2d(0,1);
	glVertex3d(160, -450, -45);
	glTexCoord2d(0,0);
	glVertex3d(160, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(160, -495, -40);
	glEnd();
	glPopMatrix();
	/////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg3 '1'
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(130, -450, -100);
	glTexCoord2d(0,0);
	glVertex3d(130, -495, -100);
	glTexCoord2d(1,0);
	glVertex3d(120, -495, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg3 '2'
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -95);
	glTexCoord2d(0,1);
	glVertex3d(130, -450, -95);
	glTexCoord2d(0,0);
	glVertex3d(130, -495, -95);
	glTexCoord2d(1,0);
	glVertex3d(120, -495, -95);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg3 '3'
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(130, -450, -95);
	glTexCoord2d(0,0);
	glVertex3d(130, -495, -95);
	glTexCoord2d(1,0);
	glVertex3d(120, -495, -100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg3 '4'
	glTexCoord2d(1,1);
	glVertex3d(130, -450, -100);
	glTexCoord2d(0,1);
	glVertex3d(130, -450, -95);
	glTexCoord2d(0,0);
	glVertex3d(130, -495, -95);
	glTexCoord2d(1,0);
	glVertex3d(130, -495, -100);
	glEnd();
	glPopMatrix();
	///////
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg4 '1'
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -40);
	glTexCoord2d(0,1);
	glVertex3d(120, -450, -40);
	glTexCoord2d(0,0);
	glVertex3d(120, -495, -40);
	glTexCoord2d(1,0);
	glVertex3d(120, -495, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg4 '2'
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -45);
	glTexCoord2d(0,1);
	glVertex3d(130, -450, -45);
	glTexCoord2d(0,0);
	glVertex3d(130, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(120, -495, -45);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg4 '3'
	glTexCoord2d(1,1);
	glVertex3d(120, -450, -40);
	glTexCoord2d(0,1);
	glVertex3d(120, -450, -45);
	glTexCoord2d(0,0);
	glVertex3d(120, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(120, -495, -40);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  chaire);
	glBegin(GL_QUADS);//chair leg4 '4'
	glTexCoord2d(1,1);
	glVertex3d(130, -450, -40);
	glTexCoord2d(0,1);
	glVertex3d(130, -450, -45);
	glTexCoord2d(0,0);
	glVertex3d(130, -495, -45);
	glTexCoord2d(1,0);
	glVertex3d(130, -495, -40);
	glEnd();
	glPopMatrix();


}

void kitcheen::mjla(int down1,int wall1){
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //up
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(495, -410, 150);
	glTexCoord2d(1,1);
	glVertex3d(-105, -410, 150);
	glTexCoord2d(0,1);
	glVertex3d(-105, -410, 100);
	glTexCoord2d(0,0);
	glVertex3d(495, -410, 100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //down
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(495, -405, 150);
	glTexCoord2d(1,1);
	glVertex3d(-105, -405, 150);
	glTexCoord2d(0,1);
	glVertex3d(-105, -405, 100);
	glTexCoord2d(0,0);
	glVertex3d(495, -405, 100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //front
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(495, -410, 100);
	glTexCoord2d(1,1);
	glVertex3d(-105, -410, 100);
	glTexCoord2d(0,1);
	glVertex3d(-105, -405, 100);
	glTexCoord2d(0,0);
	glVertex3d(495, -405, 100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //down
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(495, -410, 150);
	glTexCoord2d(1,1);
	glVertex3d(-105, -410, 150);
	glTexCoord2d(0,1);
	glVertex3d(-105, -405, 150);
	glTexCoord2d(0,0);
	glVertex3d(495, -405, 150);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  down1);//ba
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(250, -410, 100);
	glTexCoord2d(1,1);
	glVertex3d(150, -410, 100);
	glTexCoord2d(0,1);
	glVertex3d(150, -495, 100);
	glTexCoord2d(0,0);
	glVertex3d(250, -495, 100);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	//glTranslated(c,0,-1);
	glBindTexture(GL_TEXTURE_2D,  wall1);//fro//
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(250, -410, 100);
	glTexCoord2d(1,1);
	glVertex3d(150, -410, 100);
	glTexCoord2d(0,1);
	glVertex3d(150, -495, 100);
	glTexCoord2d(0,0);
	glVertex3d(250, -495, 100);
	
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  down1);//ba
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(250, -410, 150);
	glTexCoord2d(1,1);
	glVertex3d(150, -410, 150);
	glTexCoord2d(0,1);
	glVertex3d(150, -495, 150);
	glTexCoord2d(0,0);
	glVertex3d(250, -495, 150);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  down1);//r
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(250, -410, 150);
	glTexCoord2d(1,1);
	glVertex3d(250, -410, 100);
	glTexCoord2d(0,1);
	glVertex3d(250, -495, 100);
	glTexCoord2d(0,0);
	glVertex3d(250, -495, 150);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,  down1);//l
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(150, -410, 150);
	glTexCoord2d(1,1);
	glVertex3d(150, -410, 100);
	glTexCoord2d(0,1);
	glVertex3d(150, -495, 100);
	glTexCoord2d(0,0);
	glVertex3d(150, -495, 150);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -410, 130);//wf
	glTexCoord2d(1,1);
	glVertex3d(195, -410, 130);
	glTexCoord2d(0,1);
	glVertex3d(195, -370, 130);
	glTexCoord2d(0,0);
	glVertex3d(200, -370, 130);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -410, 135);//wb
	glTexCoord2d(1,1);
	glVertex3d(195, -410, 135);
	glTexCoord2d(0,1);
	glVertex3d(195, -370, 135);
	glTexCoord2d(0,0);
	glVertex3d(200, -370, 135);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(195, -370, 135);//wr
	glTexCoord2d(1,1);
	glVertex3d(195, -370, 130);
	glTexCoord2d(0,1);
	glVertex3d(195, -410, 130);
	glTexCoord2d(0,0);
	glVertex3d(195, -410, 135);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -370, 135);//wl
	glTexCoord2d(1,1);
	glVertex3d(200, -370, 130);
	glTexCoord2d(0,1);
	glVertex3d(200, -410, 130);
	glTexCoord2d(0,0);
	glVertex3d(200, -410, 135);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -370, 130);//wu
	glTexCoord2d(1,1);
	glVertex3d(195, -370, 130);
	glTexCoord2d(0,1);
	glVertex3d(195, -370, 110);
	glTexCoord2d(0,0);
	glVertex3d(200, -370, 110);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -371, 130);//wd1
	glTexCoord2d(1,1);
	glVertex3d(195, -371, 130);
	glTexCoord2d(0,1);
	glVertex3d(195, -371, 110);
	glTexCoord2d(0,0);
	glVertex3d(200, -371, 110);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -371, 110);//wr1
	glTexCoord2d(1,1);
	glVertex3d(200, -371, 130);
	glTexCoord2d(0,1);
	glVertex3d(200, -370, 130);
	glTexCoord2d(0,0);
	glVertex3d(200, -370, 110);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(195, -370, 110);//wl1
	glTexCoord2d(1,1);
	glVertex3d(195, -370, 130);
	glTexCoord2d(0,1);
	glVertex3d(195, -371, 130);
	glTexCoord2d(0,0);
	glVertex3d(195, -371, 110);
	glEnd();
	glPopMatrix();
	glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,  down1); //water
	glBegin(GL_QUADS);
	glTexCoord2d(1,0);  
	glVertex3d(200, -380, 130);//wd//
	glTexCoord2d(1,1);
	glVertex3d(195, -380, 130);
	glTexCoord2d(0,1);
	glVertex3d(195, -390, 110);
	glTexCoord2d(0,0);
	glVertex3d(200, -390, 110);
	glEnd();
	glPopMatrix();

}


void kitcheen::fridg(int fridge1,int fridge){

  
	glPushMatrix();//front
	glBindTexture(GL_TEXTURE_2D, fridge1);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(395, -300, -80);
	glTexCoord2d(0,1);
	glVertex3d(295, -300, -80);
	glTexCoord2d(0,0);
	glVertex3d(295, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(395, -495, -80);
	glEnd();
	glPopMatrix();
	glPushMatrix();//up
	glBindTexture(GL_TEXTURE_2D, fridge);
	glBegin(GL_QUADS); 
	glTexCoord2d(1,1);
    glVertex3f(395, -300, -130);
	glTexCoord2d(0,1);
	glVertex3f(295, -300, -130);
	glTexCoord2d(0,0);
	glVertex3f(295, -300, -130);
	glTexCoord2d(1,0);
	glVertex3f(395, -300, -130);
	glEnd();
	glPopMatrix();
	glPushMatrix();//back
	glBindTexture(GL_TEXTURE_2D, fridge);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(395, -300, -130);
	glTexCoord2d(0,1);
	glVertex3d(295, -300, -130);
	glTexCoord2d(0,0);
	glVertex3d(295, -495, -130);
	glTexCoord2d(1,0);
	glVertex3d(395, -495, -130);
	glEnd();
	glPopMatrix();
	//right
	glBindTexture(GL_TEXTURE_2D, fridge);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(395, -300, -130);
	glTexCoord2d(0,1);
	glVertex3d(395, -300, -80);
	glTexCoord2d(0,0);
	glVertex3d(395, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(395, -495, -130);
	glEnd();
	glPushMatrix();//left
	glBindTexture(GL_TEXTURE_2D, fridge);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(295, -300, -130);
	glTexCoord2d(0,1);
	glVertex3d(295,-300,-80);
	glTexCoord2d(0,0);
	glVertex3d(295, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(295, -495, -130);
	glEnd();
	glPopMatrix();
	glPushMatrix();//down
	glBindTexture(GL_TEXTURE_2D, fridge);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(395, -495, -130);
	glTexCoord2d(0,1);
	glVertex3d(295, -495, -80);
	glTexCoord2d(0,0);
	glVertex3d(295, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(395, -495, -80);
	glEnd();
	glPopMatrix();


}

void kitcheen::colar(int cool,int as){

//front
	glBindTexture(GL_TEXTURE_2D, cool);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(0, -350, -80);
	glTexCoord2d(0,1);
	glVertex3d(-70, -350, -80);
	glTexCoord2d(0,0);
	glVertex3d(-70, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(0, -495, -80);
	glEnd();
	//up
	glBindTexture(GL_TEXTURE_2D, as);
	glBegin(GL_QUADS); 
	glTexCoord2d(1,1);
    glVertex3f(0, -350,-130);
	glTexCoord2d(0,1);
	glVertex3f(-70, -350, -130);
	glTexCoord2d(0,0);
	glVertex3f(-70, -350, -130);
	glTexCoord2d(1,0);
	glVertex3f(0, -350, -130);
	glEnd();
	//back
	glBindTexture(GL_TEXTURE_2D, as);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(0, -450, -130);
	glTexCoord2d(0,1);
	glVertex3d(-70, -450, -130);
	glTexCoord2d(0,0);
	glVertex3d(-70, -495, -130);
	glTexCoord2d(1,0);
	glVertex3d(0, -495, -130);
	glEnd();
	//right
	glBindTexture(GL_TEXTURE_2D, as);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(-70, -350, -130);
	glTexCoord2d(0,1);
	glVertex3d(-70, -350, -80);
	glTexCoord2d(0,0);
	glVertex3d(-70, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(-70, -495, -130);
	glEnd();
	//left
	glBindTexture(GL_TEXTURE_2D, as);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(0, -350, -130);
	glTexCoord2d(0,1);
	glVertex3d(0,-350,-80);
	glTexCoord2d(0,0);
	glVertex3d(0, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(0, -495, -130);
	glEnd();
	 //down
	glBindTexture(GL_TEXTURE_2D, as);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(-70, -495, -130);
	glTexCoord2d(0,1);
	glVertex3d(0, -495, -80);
	glTexCoord2d(0,0);
	glVertex3d(0, -495, -80);
	glTexCoord2d(1,0);
	glVertex3d(-70, -495, -80);
	glEnd();




}

void kitcheen::treasury2(int wall1,int kr){

	glPushMatrix();//r
	glBindTexture(GL_TEXTURE_2D, wall1);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(495, -495, -150);
	glTexCoord2d(0,1);
	glVertex3d(495, -300, -150);
	glTexCoord2d(0,0);
	glVertex3d(455, -300, -150);
	glTexCoord2d(1,0);
	glVertex3d(455, -495, -150);
	glEnd();
	glPopMatrix();
	glPushMatrix();//l
	glBindTexture(GL_TEXTURE_2D, wall1);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(495, -495, 10);
	glTexCoord2d(0,1);
	glVertex3d(495, -300, 10);
	glTexCoord2d(0,0);
	glVertex3d(455, -300, 10);
	glTexCoord2d(1,0);
	glVertex3d(455, -495, 10);
	glEnd();
	glPopMatrix();
	glPushMatrix();//back
	glBindTexture(GL_TEXTURE_2D, wall1);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(495, -495, -150);
	glTexCoord2d(1,1);
	glVertex3d(495, -300, -150);
	glTexCoord2d(1,0);
	glVertex3d(495, -300, 10);
	glTexCoord2d(0,1);
	glVertex3d(495, -495, 10);
	glEnd();
	glPopMatrix();
	glPushMatrix();//front
	glBindTexture(GL_TEXTURE_2D, kr);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(455, -495, -150);
	glTexCoord2d(0,1);
	glVertex3d(455, -300, -150);
	glTexCoord2d(1,1);
	glVertex3d(455, -300, 10);
	glTexCoord2d(1,0);
	glVertex3d(455, -495, 10);
	glEnd();
	glPopMatrix();
	glPushMatrix();//top
	glBindTexture(GL_TEXTURE_2D, wall1);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(455, -300, -150);
	glTexCoord2d(0,1);
	glVertex3d(455, -300, 10);
	glTexCoord2d(0,0);
	glVertex3d(495, -300, 10);
	glTexCoord2d(1,0);
	glVertex3d(495, -300, -150);
	glEnd();
	glPopMatrix();
}

void kitcheen::kitchen(float x,int p1,int p2,int movX ,int movY,int movZ,int cc ,int wall1,int tr_b,int grand,int fridge1,int fridge,int down1,int cool,int as,int chaire,int fr){
	if (!(movZ<=150 && movZ>=-150 && movX<=-500 && movX>=-2965 && movY<=-248 ))
	truck2(x,p1,p2,cc,tr_b,fr);
	if (movZ<=150 && movZ>=-150 && movX<=-500 && movX>=-2965 && movY<=-248 || x!=0){
	
	//square(495, -495, -147,495, -245, -147,495, -245, 147,495, -495, 147,wall1,1,1);
	//square(-105, -495,-147,-105, -245, -147,-105, -245,147,-105, -495,147,wall1,1,1);
	//treasury2();
	fridg(fridge1,fridge);
	mjla(down1,wall1);
	colar(cool,as);
	k_chair(chaire);
	k_table(wall1);
	Double_face(-115, -495, 150,505, -495, 150,505, -245, 150,-115, -245, 150,wall1,1,1,tr_b,1,1);
	Double_face(-115, -495,-150,505, -495, -150,505, -245,-150,-115, -245,-150,tr_b,1,1,wall1,1,1);
	square(495, -495, 150,495, -495, -150,-105, -495, -150,-105, -495, 150,grand,3,3);
	Double_face(505, -245, 150,505, -245, -150,-115, -245, -150,-115, -245, 150,wall1,1,1,cc,1,1);
	//Double_face(495, -495, -147,495, -245, -147,495, -245, 147,495, -495, 147,wall1,1,1,cc,1,1);
	//Double_face(-105, -495,-147,-105, -245, -147,-105, -245,147,-105, -495,147,wall1,1,1,cc,1,1);
	}
	if (movZ<=150 && movZ>=-150 && movX<=-500 && movX>=-2965 && movY<=-248)
		t_door(x,cc,p1,p2);
}
