#pragma once
class cVector2
{
public:
	cVector2(float _x = 0.0f, float _y = 0.0f);
	cVector2(const POINT& pt);
	~cVector2();
	
	float x;
	float y;

	cVector2 operator+(const cVector2& v) const;
	cVector2 operator-(const cVector2& v);
	cVector2 operator*(float f); // v * 3, 3 * v
	cVector2 operator/(float f); // 제거
	// +
	// -
	// *
	// == 
	// !=
	// +=
	// -=
	POINT ToPoint(); // 제거
	float Len();
	float LenSq();
	cVector2 Normalize();
	static cVector2 Center(const cVector2& v1, const cVector2& v2);
	static bool CCW(const cVector2& v1, const cVector2& v2);  // 제거
	static cVector2 Zero();

	// Dot
	// Cross
	// Print
};

