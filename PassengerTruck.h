#pragma once
class PassengerTruck
{
public:
	static void PassengerTruck::square(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4 , int tex , float r1 ,float r2);
	static void PassengerTruck::Drawsquare( float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4);
	static void PassengerTruck::chair(int bs);
	static void PassengerTruck::PassengersTruck(float x ,int p1,int p2,int bs,int cc,int movX ,int movY,int movZ,int f_w,int f_d,int u_f,int l_d,int r_d,int fr);
	static void PassengerTruck::t_door(int x , int cc , int tex1 ,int tex2);
	static void PassengerTruck::Double_face(float x1,float y1,float z1,float x2,float y2,float z2,
				 float x3,float y3,float z3,float x4,float y4,float z4 , int tex1 , float r1 ,float r2, int tex2 , float r3 ,float r4);
	static void PassengerTruck::truck(float x,int p1,int p2,int f_w,int f_d,int u_f,int l_d,int r_d,int fr,int cc,int movZ);
;
};

