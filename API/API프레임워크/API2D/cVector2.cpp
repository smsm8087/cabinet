#include "stdafx.h"
#include "cVector2.h"


cVector2::cVector2(float _x, float _y)
	: x(_x)
	, y(_y)
{
}


cVector2::~cVector2()
{
}

cVector2 cVector2::operator+(const cVector2 & v)				//외우기
{
	return cVector2(x + v.x, y + v.y);
}

cVector2 cVector2::operator-(const cVector2 & v)
{
	return cVector2(x - v.x, y - v.y);
}

cVector2 cVector2::operator*(float f)
{
	return cVector2(x * f, y * f);
}

POINT cVector2::GetPoint()										//현재내위치를 주기위해 만듬
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

float cVector2::Len()
{
	return sqrt(LenSq());
}

float cVector2::LenSq()
{
	return x * x + y * y;
}

cVector2 cVector2::Normalize()									//길이를 1로만들기위해 길이를 구한후 길이로 나눠줌 노말라이즈
{
	float l = Len();
	return cVector2(x / l, y / l);
}
