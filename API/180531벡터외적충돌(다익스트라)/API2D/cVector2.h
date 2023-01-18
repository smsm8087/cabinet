#pragma once
class cVector2
{
public:
	cVector2(float _x = 0.0f, float _y = 0.0f);
	cVector2(const POINT& pt);
	~cVector2();
	
	float x;
	float y;

	cVector2 operator+(const cVector2& v);
	cVector2 operator-(const cVector2& v);
	cVector2 operator*(float f);
	BOOL operator!=(const cVector2& v);
	BOOL operator==(const cVector2& v);
	//포인트에 벡터의 xy를캐스팅하여복사한후 포인트를 반환
	POINT ToPoint();
	float Len();
	float LenSq();
	cVector2 Normalize();
	//벡터좌표들의 중앙잡기
	static cVector2 Center(const cVector2& v1, const cVector2& v2);
	//카운터클락와이즈 벡터외적
	static float CCW(const cVector2& v1, const cVector2& v2);
};

