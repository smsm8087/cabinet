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

float cVector2::DistanceEx(const cVector2 & v)
{
	float x_dis = v.x - x;
	float y_dis = v.y - y;
	return (x_dis * x_dis + y_dis * y_dis);
}

float cVector2::Distance(const cVector2 & v)
{
	return sqrtf(DistanceEx(v));
}

float cVector2::DisSqure(const cVector2 & v)
{
	float x_dis = v.x - x;
	float y_dis = v.y - y;
	return (x_dis * x_dis + y_dis * y_dis);
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

void cVector2::Normalize()
{
	float dis = this->Distance(cVector2());
	x = x / dis;
	y = y / dis;
}
