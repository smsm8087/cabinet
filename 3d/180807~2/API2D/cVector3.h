#pragma once
#include "cMatrix.h"

class cVector3
{
public:
	cVector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f);
	~cVector3();

	cVector3 operator+(const cVector3& v) const;
	cVector3 operator-(const cVector3& v) const;
	cVector3 operator*(float f) const; // v * 3, 3 * v
	cVector3 operator*(cMatrix &mat); // v * 3, 3 * v
	bool operator==(const cVector3& v) const;
	bool operator!=(const cVector3& v) const;
	cVector3& operator+=(const cVector3& v);
	cVector3& operator-=(const cVector3& v);
	float Len();
	float LenSq();
	cVector3 Normalize();
	static cVector3 Center(const cVector3& v1, const cVector3& v2);
	static cVector3 Zero();
	static float Dot(const cVector3& v1, const cVector3& v2);
	static cVector3 Cross(const cVector3& v1, const cVector3& v2);

public:
	float x;
	float y;
	float z;
};

cVector3 operator*(float f, const cVector3& v)
{
	return v * f;
}