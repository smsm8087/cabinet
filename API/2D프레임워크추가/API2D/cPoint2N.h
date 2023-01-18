#pragma once
class cPoint2N
{
public:
	cPoint2N(int _x = 0, int _y = 0);
	~cPoint2N();

	
	LONG x;
	LONG y;

	static cPoint2N Zero();

	bool operator==(const cPoint2N p);
	bool operator!=(const cPoint2N p);
	cPoint2N operator-(const cPoint2N p);
};

