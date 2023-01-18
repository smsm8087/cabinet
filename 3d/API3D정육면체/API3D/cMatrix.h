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

	cMatrix();
	cMatrix(int nDimension);
	~cMatrix();

	void	Print();
	int		Dimension();

	static	cMatrix Identity(int nDimension);

	cRow&	operator[](int nIndex);
	bool	operator==(cMatrix& mat);
	bool	operator!=(cMatrix& mat);
	cMatrix operator+(cMatrix& mat);
	cMatrix operator-(cMatrix& mat);
	cMatrix operator*(cMatrix& mat);
	cMatrix operator*(float f);
	friend cMatrix operator*(float f , cMatrix &mat);
	cMatrix Transpose();
	cMatrix Inverse(OUT float& fDeterminant);
	float	Determinant();
	cMatrix Adjoint();
	float	Cofactor(int nRow, int nCol);
	float	Minor(int nRow, int nCol);

	static cMatrix Translation(float x, float y, float z);
	static cMatrix Translation(cVector3& v);
	static cMatrix RotationX(float fAngle);
	static cMatrix RotationY(float fAngle);
	static cMatrix RotationZ(float fAngle);
	static cMatrix Scaling(float x, float y, float z);
	static cMatrix LookAtLH(cVector3& vEye, cVector3& vLookAt, cVector3& vUp);
	static cMatrix PerspectiveFovLH(float fFovY, float fAspect, float fNearZ, float fFarZ);
	static cMatrix Viewport(float x, float y, float w, float h, float fMinZ, float fMaxZ);


};

