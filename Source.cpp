#include "environment.h"
#include <windows.h>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include <3DTexture.h>
#include <Model_3ds.h>
#include <TgaLoader.h>
#include <texture.h>
#include "resturant.h"
#include "kitcheen.h"
#include "PassengerTruck.h"


HDC			hDC = NULL;
HGLRC		hRC = NULL;	
HWND		hWnd = NULL;	
HINSTANCE	hInstance;	

bool	keys[256];		
bool	active = TRUE;	
bool	fullscreen = FALSE;	

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 200000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


void square( float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2){
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
}

void Drawsquare( float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4){
	glBegin(GL_QUADS);
	glVertex3f(x1,y1,z1);
	glVertex3f(x2,y2,z2);
	glVertex3f(x3,y3,z3);
	glVertex3f(x4,y4,z4);
	glEnd();
}

void DrawCube(float x1, float y1, float z1, float x2, float y2 , float z2, float x3, float y3,float z3,float x4,float y4,float z4,
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

float angle=0,angle2=0,movZ=0,movY=-360,movX=500,lx=-10000,ly=0,lz=0;
int wall,back,front,left,right,top,down,red,yellow,silver,s_door,tr_b,fr,tr,as,f_s,f_w,f_d;
int r,l_d,r_d,r_f,l_f,u_f,gr,s2,tt,ft,sd,bs,cn,hm,c2,gps,cc,fridge1,fridge,down1,cool,ttbb;
int f1,b1,ff,r1,top1,d1,b2,ff2,l2,r2,top2,d2,tbb,ch,wallt,wallt2,wall1,p,pp,chaire,grand,kr,bu1;
int b_tree,g_tree,bb1,bb2,B,B2,B4,thing,thing2,thing3,pag,pag2,pag3,pag4,bb,m;
Model_3DS* mm;
GLTexture aa;
GLfloat LightPos[] = {320.0f,-370.0f,-150.0f,1.0f}; //truck
GLfloat LightAmb[] = {100.0f,100.0f,100.0f,20.7f};
GLfloat LightDiff[] = {2.5f,2.5f,2.5f,0.6f};
GLfloat LightSpec[] = {300.0f,300.0f,300.0f,4.5f};

GLfloat MatAmb[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat MatDif[] = {0.2f,0.6f,0.9f,1.0f};
GLfloat MatSpec[] = {0.0f,0.0f,0.0f,1.0f};
GLfloat MatShn[] = {128.0f};

void light(){
if(keys['K']){
			glLightfv(GL_LIGHT1,GL_POSITION,LightPos); 
			glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmb);
			glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiff);
			glLightfv(GL_LIGHT1,GL_SPECULAR,LightSpec);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHTING);
}
else {
	glDisable(GL_LIGHT1);

}
}
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glEnable(GL_TEXTURE_2D);
	back = LoadTexture("b.bmp");
	wall = LoadTexture("wall.bmp");
	s_door = LoadTexture("s-door.bmp");
	tr_b = LoadTexture("tr-b.bmp");
	cc = LoadTexture("cieling.bmp");
	front = LoadTexture("f.bmp");
	left = LoadTexture("l.bmp");
	b2 = LoadTexture("Back.bmp");
	ff2 = LoadTexture("Front.bmp");
	d2 = LoadTexture("Bottom.bmp");
	top2= LoadTexture("Top.bmp");
	l2 = LoadTexture("Left.bmp");
    b1 = LoadTexture("b1.bmp");
	top1 = LoadTexture("t1.bmp");
	d1 = LoadTexture("g1.bmp");
	ff = LoadTexture("ff.bmp");
    right = LoadTexture("r.bmp");
	top = LoadTexture("u.bmp");
	down = LoadTexture("g.bmp");
	red = LoadTexture("red.bmp");	
	yellow = LoadTexture("yellow.bmp");
	silver = LoadTexture("silver.bmp");
	fr = LoadTexture("floor.bmp");
	tr = LoadTexture("train.bmp");
	gr = LoadTexture("gr.bmp");
	s2 = LoadTexture("silver2.bmp");
	ft = LoadTexture("front_train.bmp");
	bs = LoadTexture("blue-sofa.bmp");
    cn = LoadTexture("counters.bmp");
	hm = LoadTexture("heat_map.bmp");
	gps = LoadTexture("gps.bmp");
    c2 = LoadTexture("c2.bmp");
	tt = LoadTexture("temp.bmp");
	sd = LoadTexture("silver_door.bmp");
    l_d = LoadTexture("l-d.bmp");
	r_d = LoadTexture("r-d.bmp");
    r_f = LoadTexture("rf-f.bmp");
	l_f = LoadTexture("lf-f.bmp");
	u_f = LoadTexture("up-f.bmp");
	r = LoadTexture("rail.bmp");
	tbb = LoadTexture("table33.bmp");  
	ch = LoadTexture("weather.bmp");            
	wallt = LoadTexture("wallt.bmp");           
	wallt2 = LoadTexture("brick.bmp");                
	p = LoadTexture("fasa1.bmp");         
	pp = LoadTexture("monaliza.bmp");         
	fridge1 = LoadTexture("fridge1.bmp");  
	fridge= LoadTexture("fridge.bmp");            
	down1 = LoadTexture("down1.bmp");
	cool = LoadTexture("colaar.bmp");
	ttbb = LoadTexture("table.bmp");         
	kr = LoadTexture("krkra.bmp");
	grand = LoadTexture("grand.bmp");
	chaire = LoadTexture("chaire.bmp");
	as = LoadTexture("as.bmp");
	wall1 = LoadTexture("wall1.bmp");
	bu1 = LoadTexture("bu1.bmp");
	f_w = LoadTexture("f_w.bmp");
	f_d = LoadTexture("f_d.bmp");
	b_tree = LoadTexture("b_tree.bmp");
	g_tree = LoadTexture("g_tree.bmp");
	bb1 = LoadTexture("building1.bmp");
	bb2 = LoadTexture("building2.bmp");
	B = LoadTexture( "Doorr.bmp "); //Box
    B2 = LoadTexture("images (1).bmp");
	thing = LoadTexture( "box1.bmp" ); //Thing
    thing2 = LoadTexture("box2.bmp" );
    thing3 = LoadTexture("box3.bmp" );
	pag = LoadTexture("pag.bmp");
	pag2 = LoadTexture("pag2.bmp");
	pag3 = LoadTexture("pag3.bmp");
	pag4 = LoadTexture("pag4.bmp");
	B4= LoadTexture("weather.bmp");
	bb = LoadTexture("bb.bmp");
	m= LoadTexture("m.bmp");

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	mm=new Model_3DS();
	mm->Load ("Luster ArteLamp Logico N260922.3DS");
	aa.LoadBMP("Luster ArteLamp Logico N260922.bmp");
	glMaterialfv(GL_FRONT,GL_AMBIENT,MatAmb);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,MatDif);
	glMaterialfv(GL_FRONT,GL_SPECULAR,MatSpec);
	glMaterialfv(GL_FRONT,GL_SHININESS,MatShn);
    glEnable(GL_COLOR_MATERIAL);
	    return TRUE;	
}

void Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
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

void t_door(int x , int tex1 , int tex2){
	Double_face(505, -495, 150,505, -495, 50,505, -245,50,505, -245, 150,tex1,1,1,tex2,1,1);
	Double_face(505, -495, -50,505, -495, -150,505, -245, -150,505, -245, -50,tex1,1,1,tex2,1,1);
    Double_face(505, -315, 150,505, -315, -150,505, -245, -150,505, -245, 150,tex1,1,1,tex2,1,1);
	square(515,-495,-150,515,-495,150,495,-495,150,495,-495,-150,cc,0.5,0.5);
	glPushMatrix();
	glTranslated(0,0,x);
	Double_face(505, -495, 50,505, -495, -50,505, -315,-50,505, -315,50,tex1,1,1,tex2,1,1);
	glPopMatrix();
}

void music(){

}

void truck(float x,int p1,int p2){
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
	t_door(x,p1,p2);
	//windows

	//glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	Drawsquare(-64,-368,150,80,-368,150,80,-275,150,-64,-275,150);
	Drawsquare(310,-368,150,454,-368,150,454,-275,150,310,-275,150);
	//glDisable(GL_BLEND);
}

void truck2(float x,int p1,int p2){
	t_door(x,p1,p2);
	square(-105, -490, -150,495, -490, -150,495, -245, -150,-105, -245, -150,tr_b,1,1);//right
    square(-105, -490, 150,495, -490, 150,495, -245, 150,-105, -245, 150,tr_b,1,1);//left
   //top & down
	square(-114, -493, 150,504, -493, 150,504,-493, -150,-114,-493,-150,fr,10,10);
	square(-114, -244, 150,504, -244, 150,504, -244, -150,-114, -244, -150,cc,1,1);
}
 
void storeehose()
{
	
	square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , B2 , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , B2 , 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B2 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B2 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B2 , 1 ,1);//back
	square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B2 , 1 ,1);//front

	glPushMatrix();
	glTranslated(250,0,0);
    square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , B2 , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , B2 , 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B2 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B2 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B2 , 1 ,1);//back
	square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B2 , 1 ,1);//front
	glPopMatrix();

	square( -90,-460,-140,-90,-460,-80,10,-460,-80,10,-460,-140 , B2 , 1 ,1); //down
	square( -90,-420,-140,-90,-420,-80,10,-420,-80,10,-420,-140 , B2 , 1 ,1);//top
	square( -90,-460,-140,-90,-460,-80,-90,-460,-80,-90,-460,-140 , B2 , 1 ,1); //left
	square( 10,-460,-80,10,-460,-140,10,-420,-140,10,-420,-80 , B2 , 1 ,1);//right
	square( -90,-460,-140,-90,-420,-140,10,-420,-140,10,-460,-140 , B2 , 1 ,1);//back
	square( -90,-460,-80,-90,-420,-80,10,-420,-80,10,-460,-80 , B2 , 1 ,1);//front

	square( -70,-490,-50,-70,-490,0,-50,-490,0,10,-490,-50 , B2 , 1 ,1); //down
	square( -70,-420,-50,-70,-420,0,10,-420,0,10,-420,-50 , B2 , 1 ,1);//top
    square( -70,-490,-50,-70,-490,0,-70,-490,0,-70,-490,-50 , B2 , 1 ,1); //left
    square( 10,-490,0,10,-490,-50,10,-420,-50,10,-420,0 , B2 , 1 ,1);//right
	square( -70,-490,-50,-70,-420,-50,10,-420,-50,10,-490,-50 , B2 , 1 ,1);//back
	square( -70,-490,0,-70,-420,0,10,-420,0,10,-490,0 , B2 , 1 ,1);//front


	glPushMatrix();
	glTranslated(0,0,10);
	square( -70,-490,-50,-70,-490,0,10,-490,0,10,-490,-50 , B2 , 1 ,1); //down
	square( -70,-420,-50,-70,-420,0,10,-420,0,10,-420,-50 , B2 , 1 ,1);//top
	square( -70,-490,-50,-70,-490,0,-70,-490,0,-70,-490,-50 , B2 , 1 ,1); //left
	square( 10,-490,0,10,-490,-50,10,-420,-50,10,-420,0 , B2 , 1 ,1);//right
	square( -70,-490,-50,-70,-420,-50,10,-420,-50,10,-490,-50 , B2 , 1 ,1);//back
	square( -70,-490,0,-70,-420,0,10,-420,0,10,-490,0 , B2 , 1 ,1);//front
	glPopMatrix();

	
	square( -70,-490,-50,-70,-490,0,10,-490,0,10,-490,-50 , B2 , 1 ,1); //down
	square( -70,-420,-50,-70,-420,0,10,-420,0,10,-420,-50 , B2 , 1 ,1);//top
	square( -70,-490,-50,-70,-490,0,-70,-490,0,-70,-490,-50 , B2 , 1 ,1); //left
	square( 10,-490,0,10,-490,-50,10,-420,-50,10,-420,0 , B2 , 1 ,1);//right
	square( -70,-490,-50,-70,-420,-50,10,-420,-50,10,-490,-50 , B2 , 1 ,1);//back
	square( -70,-490,0,-70,-420,0,10,-420,0,10,-490,0 , B2 , 1 ,1);//front

	glPushMatrix();
	glTranslated(250,0,-5);
	square( -70,-490,-50,-70,-490,0,10,-490,0,10,-490,-50 , B2 , 1 ,1); //down
	square( -70,-420,-50,-70,-420,0,10,-420,0,10,-420,-50 , B2 , 1 ,1);//top
	square( -70,-490,-50,-70,-490,0,-70,-490,0,-70,-490,-50 , B2 , 1 ,1); //left
	square( 10,-490,0,10,-490,-50,10,-420,-50,10,-420,0 , B2 , 1 ,1);//right
	square( -70,-490,-50,-70,-420,-50,10,-420,-50,10,-490,-50 , B2 , 1 ,1);//back
	square( -70,-490,0,-70,-420,0,10,-420,0,10,-490,0 , B2 , 1 ,1);//front
	glPopMatrix();


}
void Box()
{

    square( 70,-490,-50,70,-490,0,120,-490,0,120,-490,-50 , B , 1 ,1); //down
	square( 70,-420,-50,70,-420,0,120,-420,0,120,-420,-50 , B , 1 ,1);//top
	square( 70,-490,-50,70,-490,0,70,-490,0,70,-490,-50 , B , 1 ,1); //left
	square( 120,-490,0,120,-490,-50,120,-420,-50,120,-420,0 , B , 1 ,1);//right
	square( 70,-490,-50,70,-420,-50,120,-420,-50,120,-490,-50 , B , 1 ,1);//back
	square( 70,-490,0,70,-420,0,120,-420,0,120,-490,0 , B , 1 ,1);//front


	glPushMatrix();
	glTranslated(25,0,-100);
	square( 70,-490,-50,70,-490,10,120,-490,10,120,-490,-50 , B , 1 ,1); //down
	square( 70,-420,-50,70,-420,10,120,-420,10,120,-420,-50 , B , 1 ,1);//top
	square( 70,-490,-50,70,-490,10,70,-490,10,70,-490,-50 , B , 1 ,1); //left
	square( 120,-490,10,120,-490,-50,120,-420,-50,120,-420,10 , B , 1 ,1);//right
	square( 70,-490,-50,70,-420,-50,120,-420,-50,120,-490,-50 , B , 1 ,1);//back
	square( 70,-490,10,70,-420,10,120,-420,10,120,-490,10 , B, 1 ,1);//front
	glPopMatrix();

}

void treasury(){

	glPushMatrix();
	glTranslated(440,0,0);
	square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , B4 , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , B4 , 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B4 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B4 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B4 , 1 ,1);//back
	//square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B4 , 1 ,1);//front
	glPopMatrix();

	glPushMatrix();
    glTranslated(440,40,0);
	square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , wall , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , wall , 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B4 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B4 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B4 , 1 ,1);//back
	//square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B4 , 1 ,1);//front
	glPopMatrix();

	glPushMatrix();
    glTranslated(440,80,0);
	square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , wall , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , wall, 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B4 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B4 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B4 , 1 ,1);//back
	//square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B4 , 1 ,1);//front
	glPopMatrix();
	

	glPushMatrix();
    glTranslated(440,120,0);
	square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , wall , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , wall , 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B4 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B4 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B4 , 1 ,1);//back
	//square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B4 , 1 ,1);//front
	glPopMatrix();
	
	glPushMatrix();
    glTranslated(440,160,0);
	square( -90,-490,-140,-90,-490,-60,50,-490,-60,50,-490,-140 , wall , 1 ,1); //down
	square( -90,-450,-140,-90,-450,-60,50,-450,-60,50,-450,-140 , wall , 1 ,1);//top
	square( -90,-490,-140,-90,-490,-60,-90,-450,-60,-90,-450,-140 , B4 , 1 ,1); //left
	square( 50,-490,-60,50,-490,-140,50,-450,-140,50,-450,-60 , B4 , 1 ,1);//right
	square( -90,-490,-140,-90,-450,-140,50,-450,-140,50,-490,-140 , B4 , 1 ,1);//back
	//square( -90,-490,-60,-90,-490,-60,50,-490,-60,50,-490,-60 , B4 , 1 ,1);//front
	glPopMatrix();
}

  void things(){
	glPushMatrix();
    glTranslated(440,0,0);
	square( -40,-490, -100,-40, -490, -60,0, -490, -60,0, -490, -100 , thing , 1 ,1); //down
	square( -40, -480, -100,-40, -480, -60,0, -480, -60,0, -480, -100 , thing, 1 ,1);//top
	square( -40, -490, -100,-40, -490, -60,-40, -480, -60,-40, -480, -100 , thing , 1 ,1); //left
	square( 0, -490, -60,0, -490, -100,0, -480, -100,0, -480, -60, thing , 1 ,1);//right
	square( -40, -490, -100,-40, -480, -100,0, -480, -100,0, -490, -100 , thing , 1 ,1);//back
	square( -40, -490, -60,-40, -480, -60,0, -480, -60,0, -490, -60,thing, 1 ,1);//front
	glPopMatrix();


	glPushMatrix();
    glTranslated(460,40,0);
	square( -10, -490, -100,-10, -490, -60,10, -490, -60,10, -490, -100 , thing2 , 1 ,1); //down
	square( -10, -460, -100,-10, -460, -60,10, -460, -60,10, -460, -100 , thing2 , 1 ,1);//top
	square( -10, -490, -100,-10, -490, -60,-10, -460, -60,-10, -460, -100, thing2 , 1 ,1); //left
	square( 10, -490, -60,10, -490, -100,10, -460, -100,10, -460, -60, thing2 , 1 ,1);//right
	square( -10, -490, -100,-10, -460, -100,10, -460, -100,10, -490, -100 , thing2 , 1 ,1);//back
	square( -10, -490, -60,-10, -460, -60,10, -460, -60,10, -490, -60, thing2, 1 ,1);//front
	glPopMatrix();
	
	glPushMatrix();
    glTranslated(390,40,0);
	square( -20, -490, -130,-20, -490, -70,10, -490, -70,10, -490, -130, thing3 , 1 ,1); //down
	square( -20, -470, -130,-20, -470, -70,10, -470, -70,10, -470, -130 , thing3 , 1 ,1);//top
	square( -20, -490, -130,-20, -490, -70,-20, -470, -70,-20, -470, -130, thing3 , 1 ,1); //left
	square( 10, -490, -70,10, -490, -130,10, -470, -130,10, -470, -70, thing3 , 1 ,1);//right
	square( -10, -490, -100,-10, -460, -100,10, -460, -100,10, -490, -100 , thing3 , 1 ,1);//back
	square(-20, -490, -70,-20, -470, -70,10, -470, -70,10, -490, -70, thing3, 1 ,1);//front
	glPopMatrix();

	glPushMatrix();
    glTranslated(370,80,0);
	square( -10, -490, -100,-10, -490, -60,10, -490, -60,10, -490, -100 , thing2 , 1 ,1); //down
	square( -10, -460, -100,-10, -460, -60,10, -460, -60,10, -460, -100 , thing2 , 1 ,1);//top
	square( -10, -490, -100,-10, -490, -60,-10, -460, -60,-10, -460, -100, thing2 , 1 ,1); //left
	square( 10, -490, -60,10, -490, -100,10, -460, -100,10, -460, -60, thing2 , 1 ,1);//right
	square( -10, -490, -100,-10, -460, -100,10, -460, -100,10, -490, -100 , thing2 , 1 ,1);//back
	square( -10, -490, -60,-10, -460, -60,10, -460, -60,10, -490, -60, thing2, 1 ,1);//front
	glPopMatrix();
}

void  Pags(){

	square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag2 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag2, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag2 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag2 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag2, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag2, 1 ,1);//front

	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex3d(10, -450, 30);
	glVertex3d(10, -445, 30);                  //handback
	glVertex3d(20, -445, 30);
	glVertex3d(20, -450, 30);
	glColor3f(1,1,1);
	glEnd();

	   glPushMatrix();
	  glTranslated(0,0,30);
   square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag3 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag3, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag3 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag3 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag3, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag3, 1 ,1);//front
	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(0, -450, 30);
	  glVertex3d(0, -445, 30);                  //handback
	  glVertex3d(30, -445, 30);
	  glVertex3d(30, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();


	  glPushMatrix();
	  glTranslated(0,0,50);
	  glRotated(90,0,-1,0);

	   square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag4 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag4, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag4 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag4 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag4, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag4, 1 ,1);//front

     glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(10, -450, 30);
	  glVertex3d(10, -445, 30);                  //handback
	  glVertex3d(20, -445, 30);
	  glVertex3d(20, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();

	  glPushMatrix();
	  glTranslated(0,0,60);
    square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag2 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag2, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag2 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag2 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag2, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag2, 1 ,1);//front
	
	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(10, -450, 30);
	  glVertex3d(10, -445, 30);                  //handback
	  glVertex3d(20, -445, 30);
	  glVertex3d(20, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();

	   glPushMatrix();
	  glTranslated(0,0,100);

	  square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag, 1 ,1);//front

	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(0, -450, 30);
	  glVertex3d(0, -445, 30);                  //handback
	  glVertex3d(30, -445, 30);
	  glVertex3d(30, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();
     glPushMatrix();
	  glTranslated(80,0,100);
    
	  square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag4 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag4, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag4 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag4 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag4, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag4, 1 ,1);//front
	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(0, -450, 30);
	  glVertex3d(0, -445, 30);                  //handback
	  glVertex3d(30, -445, 30);
	  glVertex3d(30, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();
	   glPushMatrix();
	  glTranslated(120,0,40);
	  glRotated(90,0,-1,0);


	square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag3 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag3, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag3 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag3 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag3, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag3, 1 ,1);//front
	

	
	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(10, -450, 30);
	  glVertex3d(10, -445, 30);                  //handback
	  glVertex3d(20, -445, 30);
	  glVertex3d(20, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	glPopMatrix();

	     glPushMatrix();
	  glTranslated(170,0,40);
	  glRotated(90,0,-1,0);
	   square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag, 1 ,1);//front
	 
	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(10, -450, 30);
	  glVertex3d(10, -445, 30);                  //handback
	  glVertex3d(20, -445, 30);
	  glVertex3d(20, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();
	   glPushMatrix();
	  glTranslated(220,0,40);
	  glRotated(90,0,-1,0);


	 square( -20, -490, 20,-20, -490, 40,50, -490, 40,50, -490, 20 , pag2 , 1 ,1); //down
	square( -20, -450, 20,-20, -450, 40,50, -450, 40,50, -450, 20 , pag2, 1 ,1);//top
	square( -20, -490, 20,-20, -490, 40,-20, -450, 40,-20, -450, 20, pag2 , 1 ,1); //left
	square( 50, -490, 40,50, -490, 20,50, -450, 20,50, -450, 40, pag2 , 1 ,1);//right
	square( -20, -490, 20,-20, -450, 20,50, -450, 20,50, -490, 20 , pag2, 1 ,1);//back
	square( -20, -490, 40,-20, -450, 40,50, -450, 40,50, -490, 40, pag2, 1 ,1);//front
          	
	glLineWidth(5);
	 glBegin(GL_LINE_STRIP);
	  glVertex3d(10, -450, 30);
	  glVertex3d(10, -445, 30);                  //handback
	  glVertex3d(20, -445, 30);
	  glVertex3d(20, -450, 30);
	  glColor3f(1,1,1);
	  glEnd();
	  glPopMatrix();


}

void storage(float x,int p1,int p2){
	if(keys['L']){
			glLightfv(GL_LIGHT1,GL_POSITION,LightPos); 
			glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmb);
			glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiff);
			glLightfv(GL_LIGHT1,GL_SPECULAR,LightSpec);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHTING);
}
if(keys['K']) {
	glDisable(GL_LIGHT1);

}
	if (!(movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-100 && movX>=-1110|| x!=0))
	truck2(x,p1,p2);
	if (movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-100 && movX>=-1110 || x!=0){
	glPushMatrix();
	
	storeehose();
    //things();	 
	Box();
	//treasury();
	Pags();
	glTranslated(200,0,0);
	Pags();
	glTranslated(50,0,-80);
	Pags();
	glPopMatrix();
	Double_face(-115, -490, -150,505, -490, -150,505, -245, -150,-115, -245, -150,tr_b,1,1,gr,1,1);//right
	Double_face(-115, -490, 150,505, -490, 150,505, -245, 150,-115, -245, 150,gr,1,1,tr_b,1,1);//left
	square(-104, -492, 150,504, -492, 150,504,-492, -150,-104,-492,-150,gr,10,10);
	Double_face(-115, -244, 150,504, -244, 150,504, -244, -150,-114, -244, -150,gr,1,1,cc,1,1);
	if (movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-100 && movX>=-1110|| x!=0){
		t_door(x,p1,p2);
	}}}

void chair(){
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

float v=0;

void DriverTruck(float x, int tex1 , int tex2){
	t_door(x,tex1,tex2);
	glBindTexture(GL_TEXTURE_2D,s2);
    // length = 400, width = 300, height = 250;
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	glTexCoord2d(1,0); //right
	glVertex3d(495, -495, -150);
	glTexCoord2d(1, 1);
	glVertex3d(495, -245, -150);
	glTexCoord2d(0,1);
	glVertex3d(95, -245, -150);
	glTexCoord2d(0,0);
	glVertex3d(95, -495, -150);
	glTexCoord2d(1,0); //left
	glVertex3d(495, -495, 150); 
	glTexCoord2d(1,1);
	glVertex3d(495, -245, 150);
	glTexCoord2d(0,1);
	glVertex3d(95, -245, 150);
	glTexCoord2d(0,0);
	glVertex3d(95, -495, 150);
	/*glVertex3d(295, -495, 150); //back
	glVertex3d(295, -495, -150);
	glVertex3d(295, -245, -150);
	glVertex3d(295, -245, 150);*/
	glTexCoord2d(0, 0);	//front
	glVertex3d(95, -245, 150);
	glTexCoord2d(0,1);
	glVertex3d(95, -495, 150);
	glTexCoord2d(1,1);
	glVertex3d(95, -495, 75);
	glTexCoord2d(1, 0);
    glVertex3d(95, -245, 75);
	glTexCoord2d(1,1);
	glVertex3d(95, -245,-150);
	glTexCoord2d(1,0);
	glVertex3d(95, -495,-150);
	glTexCoord2d(0,0);
	glVertex3d(95, -495,-75);
	glTexCoord2d(0,1);
    glVertex3d(95, -245,-75);
	glTexCoord2d(1,1);
	glVertex3d(95, -245,-150);
	glTexCoord2d(0,1);
	glVertex3d(95, -245,150);
	glTexCoord2d(0,0);
	glVertex3d(95, -295,150);
	glTexCoord2d(1,0);
    glVertex3d(95, -295,-150);
	glTexCoord2d(1,0);
	glVertex3d(95, -495,-150);
	glTexCoord2d(0,0);
	glVertex3d(95, -495,150);
	glTexCoord2d(0,1);
	glVertex3d(95, -395,150);
	glTexCoord2d(1,1);
    glVertex3d(95, -395,-150);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0f,1.0f,1.0f,0.2f);
	glBegin(GL_QUADS);
	glVertex3d(95, -395,-75);
	glVertex3d(95, -295,-75);
	glVertex3d(95, -295,75);
    glVertex3d(95, -395,75);
    glEnd();
	glDisable(GL_BLEND);

	square(95, -245, 150,495, -245, 150,495, -245, -150,95, -245, -150,cc,1,1);
	square(95, -440, -135,95, -440, 135,95, -410, 135,95, -410, -135,ft,1,1);

	glBindTexture(GL_TEXTURE_2D,sd);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(370,-495,150);
	glTexCoord2d(0,1);
	glVertex3d(370, -300, 150);
	glTexCoord2d(1,1);
	glVertex3d(440, -300, 150);
	glTexCoord2d(1,0);
	glVertex3d(440, -495,150);
	glEnd();
	if (movZ<=150 && movZ>=-150 && movY<=-245 && movX<=-6066 && movX>=-6470|| x!=0){
	//table
    glBegin(GL_QUADS);
	glColor3f(0.5f,0.5f,0.5f),
	glVertex3d(100, -400,150);
	glVertex3d(100, -400,-150);
	glVertex3d(135, -400,-140);
	glVertex3d(135, -400,140);
	glVertex3d(135, -400,-140);
	glVertex3d(135, -400,140);
	glVertex3d(165, -455,120);
	glVertex3d(165, -455,-120);
	glVertex3d(165, -455,120);
	glVertex3d(165, -455,-120);
	glVertex3d(165, -475,-120);
	glVertex3d(165, -475,120);
	glColor3f(1,1,1),
	glEnd();

 	square(165, -420,10,165,-420,-10,135,-415,-10,135,-415,10,cn,1,1);  
	square(165,-420,-40,165,-420,-60,135,-415,-60,135,-415,-40,c2,1,1);
	square(165,-420,60,165,-420,40,135,-417,40,135,-417,60,gps,1,1);
	square(165,-420,-90,165,-420,-110,135,-417,-110,135,-417,-90,hm,1,1);

	glBindTexture(GL_TEXTURE_2D,tt);
	glBegin(GL_QUADS);
	glTexCoord2d(1,1);
	glVertex3d(135, -417, 90);
	glTexCoord2d(0,1);
	glVertex3d(135, -417,110);
	glTexCoord2d(0, 0);
	glVertex3d(165, -420,110);
	glTexCoord2d(1,0);
	glVertex3d(165, -420,90);
	glEnd();
	glPushMatrix();
	glTranslated(200,0,0);
	chair();
	glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,gr); //ground
	glBegin(GL_QUADS);
	glColor3f(1,1,1);
	glTexCoord2d(10,10);
	glVertex3d(495, -495, -150);
	glTexCoord2d(10, 0);
	glVertex3d(495, -495, 150);
	glTexCoord2d(0, 0);
	glVertex3d(95, -495, 150);
	glTexCoord2d(0,10);
	glVertex3d(95, -495, -150);
	glColor3f(1,1,1);
	glEnd();
	}}

float t=0,t1=0,t2=0,t3=0,t4=0,t5=0,t6=0,t7=0,t8=0,t9=0,t0=0;

void door_keys(){
    if (keys[VK_SPACE]) t+=0.4; if (keys['M']) t-=0.4;
	    if (keys['X']) t+=2.4;;

	if (keys['O'] && keys[VK_NUMPAD1]) if (t1<=90)  t1+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD1]) if (t1>=0)   t1-=0.1; 		
	if (keys['O'] && keys[VK_NUMPAD3]) if (t3<=90)  t3+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD3]) if (t3>=0)   t3-=0.1; 	
	if (keys['O'] && keys[VK_NUMPAD2]) if (t2<=90)  t2+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD2]) if (t2>=0)   t2-=0.1; 		
	if (keys['O'] && keys[VK_NUMPAD4]) if (t4<=90)  t4+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD4]) if (t4>=0)   t4-=0.1;
	if (keys['O'] && keys[VK_NUMPAD5]) if (t5<=90)  t5+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD5]) if (t5>=0)   t5-=0.1; 		
	if (keys['O'] && keys[VK_NUMPAD6]) if (t6<=90)  t6+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD6]) if (t6>=0)   t6-=0.1; 	
	if (keys['O'] && keys[VK_NUMPAD7]) if (t7<=90)  t7+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD7]) if (t7>=0)   t7-=0.1; 		
	if (keys['O'] && keys[VK_NUMPAD8]) if (t8<=90)  t8+=0.1; 		
	if (keys['C'] && keys[VK_NUMPAD8]) if (t8>=0)   t8-=0.1; 
	if (keys['O'] && keys[VK_NUMPAD9]) if (t9<=90)  t9+=0.1;
	if (keys['C'] && keys[VK_NUMPAD9]) if (t9>=0)   t9-=0.1; 
	if (keys['O'] && keys[VK_NUMPAD0]) if (t0<=90)  t0+=0.1;
	if (keys['C'] && keys[VK_NUMPAD0]) if (t0>=0)   t0-=0.1;
}

void Camera()
{
gluLookAt(movX,movY+40*fabs(cos(angle)),movZ+50*fabs(cos(angle2)),lx,ly,lz,0,1,0);
	if (keys[VK_UP]) 
		ly+= 2;  
	if (keys[VK_DOWN]) 
		ly-= 2; 
	if (keys[VK_LEFT])
	lz+=40*sin(0.1);
	lx-=40*sin(0.1);
	if (keys[VK_RIGHT])
	lz-=40*sin(0.1);
	lx+=40*sin(0.1);
	if (keys['W'])
		if (movY<=4450)
		if	(!(movY>=-285 && movY<=-253 && movX>=-6485 && movX<=-504 && movZ<=152 && movZ>=-152)) 
		movY += 0.5;
	if (keys['S'])
		if (movY>=-495)
	if	(!(movY<=-244 && movY>=-246 && movX>=-6485 && movX<=-504 && movZ<=152 && movZ>=-152)) 
         movY-= 0.5;
	if (keys['B'])
		if (movZ<=7995)
				if	(!(t1<=0.3 && movY<=-245 && movX>=-1105 && movX<=-500 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*7
				if	(!(movY<=-245 && (movX<=-500 && movX>=-505 )&& ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if (!(t1>=0 && (movX>=-507 && movX<=-505) && movY<=-245 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if	(!(movY<=-400 && movX>=-2354 && movX<=-1125 && ((movZ<=-155 && movZ>=-210)||(movZ>=42 && movZ<=48)))) //*222
				if	(!(t8<=0.3 && movY<=-245 && movX>=-5445 && movX<=-4845 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*1
				if	(!(movY<=-245 && (movX>=-5445 && movX<=-5190 )&& ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))         
				if (!((movX>=-5100 && movX<=-4595) && movY<=-245 &&((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))           
				if	(!(t9<=0.3 && movY<=-245 && movX>=-6065 && movX<=-5465 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*2
				if	(!(movY<=-245 && (movX>=-6065 && movX<=-5810 )&& ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if (!((movX>=-5720 && movX<=-5215) && movY<=-245 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if	(!(t7<=0.3 && movY<=-245 && movX>=-4825 && movX<=-4225 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*3
				if	(!(movY<=-245 && (movX>=-4825 && movX<=-4570 )&& ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if (!((movX>=-4480 && movX<=-3975) && movY<=-245 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if	(!(t6<=0.3 && movY<=-245 && movX>=-4205 && movX<=-3605 &&((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*4
				if	(!(movY<=-245 && (movX>=-4205 && movX<=-3950 )&& ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if (!((movX>=-3860 && movX<=-3355) && movY<=-245 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if	(!(t5<=0.3 && movY<=-245 && movX>=-3585 && movX<=-2985 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*5
				if	(!(movY<=-245 && (movX>=-3585 && movX<=-3330 )&& ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if (!((movX>=-3240 && movX<=-2735) && movY<=-245 && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91))))
				if	(!(t0<=0.3 && movY<=-245 && (movX<=-6065 && movX>=-6465) && ((movZ<=-155 && movZ>=-210)||(movZ>=90 && movZ<=91)))) //*8
				if (!((movZ<=-10 && movZ>=-12) & movY<=-420 && (movX<=-2365 && movX>=-3585))) //res
				if (!((movZ<=-10 && movZ>=-12) & movY<=-350 && ((movX>=-3800 && movX<=-3605)||(movX<=-4000 && movX>=-4425)||(movX<=-4600 && movX>=-5000)||(movX<=-5200 && movX>=-5390)))) //chair
       {
			angle+=0.001;
			movZ+=0.5;
		} 	

		if (keys['F'])
			if (movZ>=-7995)
				if	(!(t8<=0.3 && movY<=-245 && movX>=-5445 && movX<=-4845 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)))) //*1
				if	(!(movY<=-245 && (movX>=-5445 && movX<=-5190 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))         
				if (!((movX>=-5100 && movX<=-4595) && movY<=-245 &&((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))           
				if	(!(t9<=0.3 && movY<=-245 && movX>=-6065 && movX<=-5465 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)))) //*2
				if	(!(movY<=-245 && (movX>=-6065 && movX<=-5810 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)) ))
				if (!((movX>=-5720 && movX<=-5215) && movY<=-245 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if	(!(t7<=0.3 && movY<=-245 && movX>=-4825 && movX<=-4225 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)))) //*3
				if	(!(movY<=-245 && (movX>=-4825 && movX<=-4570 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if (!((movX>=-4480 && movX<=-3975) && movY<=-245 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if	(!(t6<=0.3 && movY<=-245 && movX>=-4205 && movX<=-3605 &&((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)))) //*4
				if	(!(movY<=-245 && (movX>=-4205 && movX<=-3950 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if (!((movX>=-3860 && movX<=-3355) && movY<=-245 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if	(!(t5<=0.3 && movY<=-245 && movX>=-3585 && movX<=-2985 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)))) //*5
				if	(!(movY<=-245 && (movX>=-3585 && movX<=-3330 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)) ))
				if (!((movX>=-3240 && movX<=-2735) && movY<=-245 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if	(!(movY<=-245 && movX>=-2345 && movX<=-1125 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150)))) //*6
				if	(!(movY<=-245 && (movX>=-1495 && movX<=-1470 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if (!((movX>=-1380 && movX<=-875) && movY<=-245 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if	(!(t1<=0.3 && movY<=-245 && (movX<=-500 && movX>=-1100) && ((movZ<=150 && movZ>=149.4)||(movZ<=-148 && movZ>=-150)))) //*7
				if	(!(t1>=0 && movY<=-245 && (movX>=-1100 && movX<=-900 )&& ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if (!(t1>=0 && (movX>=-700 && movX<=-500) && movY<=-245 && ((movZ<=152 && movZ>=150)||(movZ<=-148 && movZ>=-150))))
				if	(!(t0<=0.3 && movY<=-245 && (movX<=-6065 && movX>=-6465) && ((movZ<=150 && movZ>=149.4)||(movZ<=-148 && movZ>=-150)))) //*8 -> driver
				if (!((movZ<=-80 && movZ>= -82) & movY<=-350 && ((movX>=-3800 && movX<=-3605)||(movX<=-4000 && movX>=-4425)||(movX<=-4600 && movX>=-5000)||(movX<=-5200 && movX>=-5390)))) //chair
				if (!((movZ<=-75 && movZ>= -77) & movY<=-420 && (movX<=-2365 && movX>=-3585))) //res

		{
			angle+=0.001;
			movZ-=0.5;
		} 
			
		if (keys['A']) 
		if (movX>=(-29995+t))
			if (!(t1<=5 && (movX<=-485 && movX>=-487) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t1>=0 &&  (movX<=-485 && movX>=-487) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t1>=0 &&  (movX<=-485 && movX>=-487) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t2<=0.3 && (movX<=-1105 && movX>=-1107) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t2>=0 &&  (movX<=-1105 && movX>=-1107) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t2>=0 &&  (movX<=-1105 && movX>=-1107) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t3<=0.3 && (movX<=-1725 && movX>=-1727) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t3>=0 &&  (movX<=-1725 && movX>=-1727) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t3>=0 &&  (movX<=-1725 && movX>=-1727) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t4<=0.3 && (movX<=-2345 && movX>=-2347) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t4>=0 &&  (movX<=-2345 && movX>=-2347) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t4>=0 &&  (movX<=-2345 && movX>=-2347) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t5<=0.3 && (movX<=-2965 && movX>=-2967) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t5>=0 &&  (movX<=-2965 && movX>=-2967) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t5>=0 && (movX<=-2965 && movX>=-2967) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t6<=0.3 && (movX<=-3585 && movX>=-3587) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t6>=0 &&  (movX<=-3585 && movX>=-3587) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t6>=0 &&  (movX<=-3585 && movX>=-3587) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t7<=0.3 && (movX<=-4205 && movX>=-4207) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t7>=0 &&  (movX<=-4205 && movX>=-4207) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t7>=0 && (movX<=-4205 && movX>=-4207) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t8<=0.3 && (movX<=-4825 && movX>=-4827) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t8>=0 &&  (movX<=-4825 && movX>=-4827)  && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t8>=0 &&  (movX<=-4825 && movX>=-4827)  && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t9<=0.3 && (movX<=-5425 && movX>=-5427) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t9>=0 && (movX<=-5425 && movX>=-5427) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t9>=0 && (movX<=-5425 && movX>=-5427) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t0<=0.3 && (movX<=-6045 && movX>=-6047) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t0>=0 && (movX<=-6045 && movX>=-6047) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t9>=0 && (movX<=-6045 && movX>=-6047) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if(!((movX<=-2000 && movX>=-2002) && movY<=-435 && (movZ<=25 && movZ>=-150)))//table2
			if(!((movX<=-1380 && movX>=-1382) && movY<=-435 && (movZ<=25 && movZ>=-150)))//table
			if(!((movX<=-520 && movX>=-522) && movY<=-465 && (movZ<=150 && movZ>=-150)))//bags

		{
			angle+=0.0015;
			movX-=0.09;
		}  

		if (keys['Z']) {
			angle+=0.0035;
			movX-=3;
		}  
		if (keys['D']) 
		if (movX<=495+t)
			if (!(t1<=0.3 && (movX<=-495 && movX>=-497) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t1>=0 &&  (movX<=-495 && movX>=-497) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t1>=0 && (movX<=-495 && movX>=-497) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t2<=0.3 && (movX<=-1115 && movX>=-1117) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t2>=0 && (movX<=-1115 && movX>=-1117) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t2>=0 &&(movX<=-1115 && movX>=-1117) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t3<=0.3 && (movX<=-1735 && movX>=-1737) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t3>=0 &&(movX<=-1735 && movX>=-1737) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t3>=0 &&(movX<=-1735 && movX>=-1737) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t4<=0.3 && (movX<=-2355 && movX>=-2357) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t4>=0 &&  (movX<=-2355 && movX>=-2357)  && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t4>=0 && (movX<=-2355 && movX>=-2357)  && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t5<=0.3 && (movX<=-2975 && movX>=-2977) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t5>=0 && (movX<=-2975 && movX>=-2977)  && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t5>=0 &&(movX<=-2975 && movX>=-2977) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t6<=0.3 && (movX<=-3595 && movX>=-3597) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t6>=0 && (movX<=-3595 && movX>=-3597)&& movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t6>=0 &&  (movX<=-3595 && movX>=-3597) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t7<=0.3 && (movX<=-4215 && movX>=-4217) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t7>=0 && (movX<=-4215 && movX>=-4217) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t7>=0 && (movX<=-4215 && movX>=-4217) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t8<=0.3 && (movX<=-4835 && movX>=-4837) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t8>=0 &&(movX<=-4835 && movX>=-4837) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t8>=0 &&(movX<=-4835 && movX>=-4837) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t9<=0.3 && (movX<=-5435 && movX>=-5437) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t9>=0 && (movX<=-5435 && movX>=-5437) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t9>=0 && (movX<=-5435 && movX>=-5437) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
			if (!(t0<=0.3 && (movX<=-6055 && movX>=-6057) && movY<=-245 && (movZ<=110 && movZ>=-200)))
			if(!(t0>=0 && (movX<=-6055 && movX>=-6057) && movY<=-245 && ((movZ<=110 && movZ>=0)||(movZ<=-90 && movZ>=-200))))
			if(!(t9>=0 && (movX<=-6055 && movX>=-6057) && (movY<=-245 && movY>=-314) && ((movZ<=0 && movZ>=-90))))
		{
			angle+=0.001;
			movX+=0.5;
		}
}

int DrawGLScene(GLvoid)					
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera();
	if (keys['H']) PlaySound("Train-Horn-Sound-Effect.wav",NULL,SND_FILENAME); 		
	glPushMatrix();
	glTranslated(t,0,0);
	//e.skybox8(cc);
	environment::env(ff2,b2,l2,top2,d2,l2,r,g_tree,b_tree,bb1,cc,bu1,wall ,back ,right, top ,down,ff,b1 ,top1 ,d1);
	glPopMatrix();
	glPushMatrix();
	mm->pos.x= 0;
	mm->pos.y= 0;
	mm->pos.z= 200;
	mm->scale=0.01;
	//mm->Draw();
	mm->Materials[1].tex=aa;
	glTranslated(-1000,0,0);
	storage(t1,cc,cc);
    glTranslated(-620,0,0);
	//kitchen(t2,cc,cc);
	kitcheen::kitchen(t2,cc,cc,movX ,movY,movZ,cc ,wall1,tr_b,grand,fridge1,fridge,down1,cool,as,chaire,fr);
	kitcheen::kitchen(t2,cc,cc,movX ,movY,movZ,cc ,wall1,tr_b,grand,fridge1,fridge,down1,cool,as,chaire,fr);
	glTranslated(-620,0,0);
	kitcheen::kitchen(t3,cc,wall1,movX ,movY,movZ,cc ,wall1,tr_b,grand,fridge1,fridge,down1,cool,as,chaire,fr);
	glTranslated(-620,0,0);
	//restaurant(t4,wallt,wall1);
	resturant::restaurant(movX,movY,movZ,t4,cc,tbb,wallt,ch,tr_b,wallt2,fr,wall,wall1,p,pp);
	glTranslated(-620,0,0);
	//restaurant(t5,wallt,wallt);
	resturant::restaurant(movX,movY,movZ,t5,cc,tbb,wallt,ch,tr_b,wallt2,fr,wallt,wallt,p,pp);
    glTranslated(-620,0,0);
	//PassengersTruck(t6,cc,wallt);
	PassengerTruck::PassengersTruck(t6,cc,wallt,bs,cc, movX ,movY,movZ,f_w,f_d,u_f,l_d,r_d,fr);
    glTranslated(-620,0,0);
	PassengerTruck::PassengersTruck(t7,cc,cc,bs,cc, movX ,movY,movZ,f_w,f_d,u_f,l_d,r_d,fr);
    glTranslated(-620,0,0);
	PassengerTruck::PassengersTruck(t8,cc,cc,bs,cc, movX ,movY,movZ,f_w,f_d,u_f,l_d,r_d,fr);
	glTranslated(-620,0,0);
	PassengerTruck::PassengersTruck(t9,cc,cc,bs,cc, movX ,movY,movZ,f_w,f_d,u_f,l_d,r_d,fr);
	glTranslated(-620,0,0);
	DriverTruck(t0,s2,cc);
	glPopMatrix();
	door_keys();
    return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			
	UINT	uMsg,			
	WPARAM	wParam,			
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		
	LPSTR		lpCmdLine,		
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
														//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
														// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
