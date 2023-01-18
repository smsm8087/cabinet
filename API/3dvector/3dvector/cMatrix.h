#pragma once
#define OUT
class cMatrix
{
private:
	
public:
	cMatrix(int n);
	~cMatrix();
	vector<vector<float>> m_vecmatrix;

	bool operator==(cMatrix m1);
	bool operator!=(cMatrix m1);
	cMatrix operator+(cMatrix m1);
	cMatrix operator-(cMatrix m1);
	cMatrix operator*(float f) const;
	cMatrix operator*(cMatrix m1);
	friend cMatrix operator*(float f, const cMatrix& m1)
	{
		return m1 * f;
	}
	/*
	==
	!=
	+
	-
	* (scalar) 교환법칙
	* (matrix)
	*/

	cMatrix Transpose(cMatrix m1);
	float Cofactor(cMatrix m1, int row, int col);
	float Minor(cMatrix m1, int row, int col);
	float Determinenet(cMatrix m1);
	cMatrix AdJoint(cMatrix m1);
	static cMatrix Identity(int n);
	cMatrix Invserse(cMatrix m1);//OUT float& fDeterminent);
	static cMatrix Random(int n, float fMin, float fMax); // 소수 이하 3자리
	void Print();
};


