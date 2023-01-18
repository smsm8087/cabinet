#include "stdafx.h"
#include "cPoint2N.h"


cPoint2N::cPoint2N(int _x, int _y)
	: x(_x)
	, y(_y)
{
}


cPoint2N::~cPoint2N()
{
}


bool cPoint2N::operator==(const cPoint2N& p)
{
	return (x == p.x && y == p.y);
}

bool cPoint2N::operator!=(const cPoint2N& p)
{
	return !(x == p.x && y == p.y);
}

cPoint2N cPoint2N::operator-(cPoint2N p)
{
	return cPoint2N(x - p.x, y - p.y);
}

cPoint2N cPoint2N::operator+(cPoint2N p)
{
	return cPoint2N(x + p.x, y + p.y);
}

cPoint2N cPoint2N::operator*(const float f)
{
	return cPoint2N(x * f, y * f);
}

POINT cPoint2N::ToPoint()
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

cPoint2N cPoint2N::Zero()
{
	return cPoint2N(0, 0);
}

cPoint2N cPoint2N::Lerp(cPoint2N p0, cPoint2N p1, float t)
{
	return p0 + (p1 - p0) * t;
}

float cPoint2N::Len(cPoint2N p0, cPoint2N p1)
{
	cPoint2N pt = p1 - p0;
	return sqrt(pt.x * pt.x + pt.y * pt.y);
}
