#pragma once
class cVector3
{
public:
	cVector3(float _x = 0.0f, float _y = 0.0f , float _z = 0.0f);
	~cVector3();

	float x;
	float y;
	float z;

	cVector3 operator+(const cVector3& v);
	cVector3 operator-(const cVector3& v);
    // == 
	bool operator==(cVector3 v);
	bool operator!=(cVector3 v);
    // !=
	cVector3 operator+=(const cVector3& v);
	cVector3 operator-=(const cVector3& v);
    // +=
    // -=
	float Len();
	float LenSq();
	cVector3 Normalize();
	static cVector3 Center(const cVector3& v1, const cVector3& v2);
	static cVector3 Zero();
	static float Dot(const cVector3 & v1, const cVector3 & v2);//내적
	static cVector3 Cross(const cVector3 & v1, const cVector3 & v2);//외적
    void Print();
	// Dot
	// Cross
	// Print
};

cVector3 operator*(const float &f, const cVector3& v)
{
	return cVector3(v.x * f, v.y * f, v.z * f);
}
// v * 3, 3 * v

