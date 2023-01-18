#pragma once
class cVector2
{
public:
	cVector2(float _x = 0.0f, float _y = 0.0f);
	~cVector2();
	
	float x;
	float y;

	float DistanceEx(const cVector2& v);
	float Distance(const cVector2& v);
	float DisSqure(const cVector2& v);
	cVector2 operator+(const cVector2& v);
	cVector2 operator-(const cVector2& v);
	cVector2 operator*(float f);
	cVector2 operator/(float f);
	void Normalize();
	POINT GetPoint()
	{
		POINT pt;
		pt.x = x;
		pt.y = y;
		return pt;
	}
};