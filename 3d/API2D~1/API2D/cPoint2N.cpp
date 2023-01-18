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

cPoint2N cPoint2N::Zero()
{
	return cPoint2N(0, 0);
}

bool cPoint2N::operator==(const cPoint2N p)
{
	return (x == p.x && y == p.y);
}

bool cPoint2N::operator!=(const cPoint2N p)
{
	return !(x == p.x && y == p.y);
}

cPoint2N cPoint2N::operator-(const cPoint2N p)
{
	return cPoint2N(x - p.x, y - p.y);
}
