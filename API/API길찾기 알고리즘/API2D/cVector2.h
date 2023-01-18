#pragma once
class cVector2
{
public:
	cVector2(float _x = 0.0f, float _y = 0.0f);
	~cVector2();
	
	float x;
	float y;

	cVector2 operator+(const cVector2& v);				//연산자오버로딩 
	cVector2 operator-(const cVector2& v);
	cVector2 operator*(float f);
	POINT GetPoint();									//위치를 받아오기위해
	float Len();										//길이
	float LenSq();										//길이 루트
	cVector2 Normalize();								//노말라이즈
};

