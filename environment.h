
#pragma once
#ifndef _TOOLS_H_
#define _TOOLS_H_

class environment
{
public:
	static void environment::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2);
	static void environment::skybox(int wall , int back , int right, int top , int down);
	static void environment::skybox2(int ff, int b1 , int top1 , int tex4);
	static void environment::buildings(int tex10,int tex11,int tex12);
	static void environment::skybox3(int tex1 , int tex2 , int tex3 , int tex4 , int tex5 , int tex6 , int tex7 );
	static void environment::tree(int tex8 , int tex9);
	static void environment::trees(int tex8 , int tex9);
	static void environment::build1(int x);
	static void environment::build2(int tex10,int tex11);
	static void environment::DrawCube(float x1, float y1, float z1, float x2, float y2 , float z2, float x3, float y3,float z3,float x4,float y4,float z4,
			  float x5,float y5, float z5, float x6, float y6, float z6, float x7, float y7, float z7,float x8,float y8,float z8,
			  int pic1,int r1,int r2,int pic2,int r3,int r4,int pic3,int r5,int r6,int pic4,int r7,int r8,int pic5,int r9,int r10,int pic6,int r11,int r12);
	static void environment::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
				 float x3,float y3,float z3,float x4,float y4,float z4 , int tex1 , float r1 ,float r2, int tex2 , float r3 ,float r4);
    static void environment::env(int tex1 , int tex2 , int tex3 , int tex4 , int tex5 , int tex6 , int tex7 , int tex8 , int tex9, int tex10 , int tex11, int tex12
					  , int wall , int back , int right, int top , int down, int ff, int b1 , int top1 , int d1);
};

#endif