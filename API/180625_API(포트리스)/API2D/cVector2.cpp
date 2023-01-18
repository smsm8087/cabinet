#include "stdafx.h"
#include "cVector2.h"


cVector2::cVector2(float _x, float _y)
	: x(_x)
	, y(_y)
{
}

cVector2::cVector2(const POINT& pt)
	: x(pt.x)
	, y(pt.y)
{
}

cVector2::~cVector2()
{
}

cVector2 cVector2::operator+(const cVector2 & v)
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

cVector2 cVector2::operator/(float f)
{
	return cVector2(x / f, y / f);
}

POINT cVector2::ToPoint()
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

cVector2 cVector2::Normalize()
{
	float l = Len();
	return cVector2(x / l, y / l);
}

cVector2 cVector2::Center(const cVector2 & v1, const cVector2 & v2)
{
	return cVector2((v1.x + v2.x) / 2, (v1.y + v2.y) / 2);
}

bool cVector2::CCW(const cVector2 & v1, const cVector2 & v2)
{
	return v1.x * v2.y - v1.y * v2.x < 0;
}

cVector2 cVector2::Zero()
{
	return cVector2(0, 0);
}
