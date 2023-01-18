#include "stdafx.h"
#include "cVector3.h"


cVector3::cVector3(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)
{
}

cVector3::~cVector3()
{
}

cVector3 cVector3::operator+(const cVector3 & v) const
{
	return cVector3(x + v.x, y + v.y, z + v.z);
}

cVector3 cVector3::operator-(const cVector3 & v) const
{
	return cVector3(x - v.x, y - v.y, z - v.z);
}

cVector3 cVector3::operator*(float f) const
{
	return cVector3(x * f, y * f, z * f);
}

cVector3 cVector3::operator*(cMatrix &mat)
{

	cVector3 m;

	m.x = x * mat[0][0] + y * mat[1][0] + z * mat[2][0] + 1.0f * mat[3][0];
	m.y = x * mat[0][1] + y * mat[1][1] + z * mat[2][1] + 1.0f * mat[3][1];
	m.z = x * mat[0][2] + y * mat[1][2] + z * mat[2][2] + 1.0f * mat[3][2];
	float w = x * mat[0][3] + y * mat[1][3] + z * mat[2][3] + 1.0f * mat[3][3];

	/*if (-EPSILON > w || EPSILON < w)
	{
		vRet.x /= w;
		vRet.y /= w;
		vRet.z /= w;
	}*/

	if (w != 0 && w != 1)
	{
		m = m * (1 / w);
	}

	return m;
}

bool cVector3::operator==(const cVector3 & v) const
{
	if (fabs(x - v.x) > EPSILON) return false;
	if (fabs(y - v.y) > EPSILON) return false;
	if (fabs(z - v.z) > EPSILON) return false;
	return true;
}

bool cVector3::operator!=(const cVector3 & v) const
{
	return !(*this == v);
}

cVector3 & cVector3::operator+=(const cVector3 & v)
{
	*this = *this + v;
	return *this;
}

cVector3 & cVector3::operator-=(const cVector3 & v)
{
	*this = *this - v;
	return *this;
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
	return cVector3(x / l, y / l, z / l);
}

cVector3 cVector3::Center(const cVector3 & v1, const cVector3 & v2)
{
	return (v1 + v2) * 0.5f;
}

cVector3 cVector3::Zero()
{
	return cVector3(0.0f, 0.0f, 0.0f);
}

float cVector3::Dot(const cVector3 & v1, const cVector3 & v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross(const cVector3 & v1, const cVector3 & v2)
{
	return cVector3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

cVector3 operator*(float f, const cVector3 & v)
{
	return v * f;
}