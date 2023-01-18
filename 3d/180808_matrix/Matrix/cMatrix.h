#pragma once

class cVector3;

class cMatrix
{
private:
	class cRow
	{
	private:
		vector<float> m_vecCol;
	public:
		cRow(int nDimension = 0)
		{
			Resize(nDimension);
		}

		float& operator[](int nIndex)
		{
			return m_vecCol[nIndex];
		}

		void Resize(int nDimension)
		{
			m_vecCol.resize(nDimension);
		}
	};

	vector<cRow> m_vecRow;

public:
	cMatrix(int nDimension);
	~cMatrix();

	cRow& operator[](int nIndex);
	bool operator==(cMatrix& m);
	bool operator!=(cMatrix& m);
	cMatrix operator+(cMatrix& m);
	cMatrix operator-(cMatrix& m);
	cMatrix operator*(float f);
	cMatrix operator*(cMatrix& m);
	cMatrix Transpose();
	static cMatrix Identity(int nDimension);
	cMatrix Invserse(float& fDeterminent);
	static cMatrix Random(int nDimension, float fMin, float fMax); // �Ҽ� ���� 3�ڸ�
	void Print();
	int Dimension();
	float Determinent();
	cMatrix Adjoint();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);

	static cMatrix Translation(float x, float y, float z);
	static cMatrix RotationX(float fAngle);
	static cMatrix RotationY(float fAngle);
	static cMatrix RotationZ(float fAngle);
	static cMatrix Scaling(float x, float y, float z);
	static cMatrix LookAtLH(cVector3& vEye, cVector3& vLookAt, cVector3& vUp);
	static cMatrix PerspectiveFovLH(float fFovY, float fAspect, float fNearZ, float fFarZ);
	static cMatrix Viewport(float x, float y, float w, float h, float fMinZ, float fMaxZ);
};

cMatrix operator*(float f, cMatrix& m);
