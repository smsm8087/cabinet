#pragma once

class cMatrix;

class cVector3
{
public:
	cVector3();
	cVector3(float _x, float _y, float _z);
	~cVector3();

	// >> : 
	float x, y, z; 

	// : 연산자 오버라이딩 해오기 
	bool operator==(cVector3& vec);
	bool operator!=(cVector3& vec);
	cVector3 operator+(cVector3& vec);
	cVector3 operator+=(cVector3& vec);
	cVector3 operator-=(cVector3& vec);
	cVector3 operator-(cVector3& vec);
	cVector3 operator*(float f);
	cVector3 operator*(cMatrix &mat);
	cVector3 operator/(float f);


	float Length();
	cVector3 Normalize();
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	cVector3 TransformNormal(cMatrix & mat);
};

