#pragma once
class kitcheen
{
public:
	static void kitcheen::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2);
    static void kitcheen::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
				 float x3,float y3,float z3,float x4,float y4,float z4 , int tex1 , float r1 ,float r2, int tex2 , float r3 ,float r4);
	static void kitcheen::t_door(int x , int cc , int tex1 ,int tex2);
	static void kitcheen::truck2(float x,int p1,int p2,int cc,int tr_b,int fr);
	static void kitcheen::k_table(int wall1);
	static void kitcheen::k_chair(int chaire);
	static void kitcheen::mjla(int down1,int wall1);
	static void kitcheen::fridg(int fridge1,int fridge);
	static void kitcheen::colar(int cool,int as);
	static void kitcheen::treasury2(int wall1,int kr);
	static void kitcheen::kitchen(float x,int p1,int p2,int movX ,int movY,int movZ,int cc ,int wall1,int tr_b,int grand,int fridge1,int fridge,int down1,int cool,int as,int chaire,int fr);
};

