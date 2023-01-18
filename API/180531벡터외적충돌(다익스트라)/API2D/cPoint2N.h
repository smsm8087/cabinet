#pragma once
class cPoint2N
{
public:
	cPoint2N(int _x = 0, int _y = 0);
	~cPoint2N();

	
	LONG x;
	LONG y;
	
	bool operator==(const cPoint2N& p);
	bool operator!=(const cPoint2N& p);
	cPoint2N operator-(cPoint2N p);
	cPoint2N operator+(cPoint2N p);
	cPoint2N operator*(const float f);

	POINT ToPoint();

	static cPoint2N Zero();
	static cPoint2N Lerp(cPoint2N p0, cPoint2N p1, float t);
	static float Len(cPoint2N p0, cPoint2N p1);
	
};

