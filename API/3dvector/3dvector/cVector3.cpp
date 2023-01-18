#include "stdafx.h"
#include "cVector3.h"


cVector3::cVector3(float _x, float _y,float _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}
cVector3::~cVector3()
{
}

cVector3 cVector3::operator+(const cVector3 & v)
{
	return cVector3(x + v.x, y + v.y, z + v.z);
}

cVector3 cVector3::operator-(const cVector3 & v)
{
	return cVector3(x - v.x, y - v.y, z - v.z);
}

bool cVector3::operator==(cVector3  v)
{
	if (fabsf(x - v.x) <= FLT_EPSILON && fabsf(y - v.y) <= FLT_EPSILON && fabsf(z - v.z) <= FLT_EPSILON)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool cVector3::operator!=(cVector3 v)
{
	if (fabsf(x - v.x) <= FLT_EPSILON && fabsf(y - v.y) <= FLT_EPSILON && fabsf(z - v.z) <= FLT_EPSILON)
	{
		return false;
	}
	else
	{
		return true;
	}
}

cVector3 cVector3::operator+=(const cVector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return (*this);
}

cVector3 cVector3::operator-=(const cVector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return (*this);
}

float cVector3::Len()
{
	return sqrt(LenSq());
}

float cVector3::LenSq()
{
	return x * x + y * y + z * z;
}

cVector3 cVector3::Normalize()
{
	float l = Len();
	return cVector3(x / l, y / l, z/l);
}

cVector3 cVector3::Center(const cVector3 & v1, const cVector3 & v2)
{
	return cVector3((v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z)/2);
}

cVector3 cVector3::Zero()
{
	return cVector3(0, 0,0);
}

float cVector3::Dot(const cVector3 & v1, const cVector3 & v2)
{
	return float(v1.x*v2.x + v1.y * v2.y + v1.z * v2.z);
}

cVector3 cVector3::Cross(const cVector3 & v1, const cVector3 & v2)
{
	return cVector3(((v1.y * v2.z) - (v1.z * v2.y)) , ((v1.z * v2.x)
		- (v1.x * v2.z)) , ((v1.x * v2.y) - (v1.y * v2.x)));
}

void cVector3::Print()
{
	printf("%.2f,%.2f,%.2f", x, y, z);
}
