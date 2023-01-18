#include "stdafx.h"
#include "cMatrix.h"
#include "cVector3.h"

cMatrix::cMatrix()
{
}

cMatrix::cMatrix(int nDimension)
{
	m_vecRow.resize(nDimension);

	for (int i = 0; i < nDimension; i++)
	{
		m_vecRow[i].Resize(nDimension);
	}
}

cMatrix::~cMatrix()
{
}



void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			printf("%8.2f", (*this)[i][j]);
		}
		printf("\n");
	}
}

int cMatrix::Dimension()
{
	return (int)m_vecRow.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matRet(nDimension);

	for (int i = 0; i < nDimension; ++i)
	{
		for (int j = 0; j < nDimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}
	return matRet;
}

// : 
cMatrix::cRow& cMatrix::operator[](int nIndex)
{
	return m_vecRow[nIndex];
}

// : 
bool cMatrix::operator==(cMatrix& mat)
{
	float fEpsilon = 0.0001f;
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if ((*this)[i][j] - fEpsilon > mat[i][j])
				return false;
			if ((*this)[i][j] + fEpsilon < mat[i][j])
				return false;
		}
	}
	return true;
}

// : 
bool cMatrix::operator!=(cMatrix& mat)
{
	return !((*this) == mat);
}

// : 
cMatrix cMatrix::operator+(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}
	return matRet;
}
// : 

// : 
cMatrix cMatrix::operator-(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0.f;
			for (int k = 0; k < Dimension(); ++k)
			{
				matRet[i][j] += ((*this)[i][k] * mat[k][j]);
			}
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix mat(Dimension());
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			mat[r][c] = (*this)[r][c] * f;
		}
	}
	return mat;
}

cMatrix cMatrix::Transpose()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}
	return matRet;
}

cMatrix cMatrix::Inverse(OUT float& fDeterminant)
{
	cMatrix matRet = cMatrix::Identity(Dimension());

	fDeterminant = Determinant();
	if (-0.0001f < fDeterminant && fDeterminant < 0.0001f)
	{
		cout << " 역행렬이 존재 하지 않음 " << endl;
		return matRet; // : 
	}
	cout << " Determinant : " << fDeterminant << endl;

	cMatrix matAdj = Adjoint();
	matRet = (1 / fDeterminant) * matAdj;
	return matRet;
}

float cMatrix::Determinant()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	}
	
	float fDeterminant = 0.0f;

	for (int i = 0; i < Dimension(); ++i)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}

	return fDeterminant;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = Cofactor(j, i); 
		}
	}
	return matRet;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;

	if ((nRow + nCol) % 2 != 0)
		nConst = -1;

	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix matMinor(Dimension() - 1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); ++i)
	{
		if (nRow == i)
			continue;

		nMinorCol = 0;

		for (int j = 0; j < Dimension(); ++j)
		{
			if (nCol == j)
				continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}

	int k = matMinor.Determinant();
	cout << k << endl;

	return matMinor.Determinant();
}

cMatrix cMatrix::Translation(float x, float y, float z)
{
	//마지막줄이 x y z 성분으로 되어있음 마지막은 1
	//정규화후
	cMatrix mat = Identity(4);
	mat[3][0] = x;
	mat[3][1] = y;
	mat[3][2] = z;

	return mat;
}

cMatrix cMatrix::Translation(cVector3 & v)
{
	cMatrix mat = Identity(4);
	mat[3][0] = v.x;
	mat[3][1] = v.y;
	mat[3][2] = v.z;
	return mat;
}

cMatrix cMatrix::RotationX(float fAngle)
{
	/*
	1 0 0 0
	0 c s 0
	0-s c 0
	0 0 0 1
	*/
	//0부터 시작이니까
	cMatrix mat = Identity(4);
	mat[1][1] = cos(fAngle);
	mat[1][2] = sin(fAngle);
	mat[2][1] = -sin(fAngle);
	mat[2][2] = cos(fAngle);

	return mat;
}

cMatrix cMatrix::RotationY(float fAngle)
{
	/*
	c 0 -s 0
	0 1  0 0
	s 0  c 0
	0 0  0 1
	*/
	cMatrix mat = Identity(4);
	mat[0][0] = cos(fAngle);
	mat[0][2] = -sin(fAngle);
	mat[2][0] = sin(fAngle);
	mat[2][2] = cos(fAngle);

	return mat;
}

cMatrix cMatrix::RotationZ(float fAngle)
{
	/*
	
	 c s 0 0
	-s c 0 0
	 0 0 1 0
	 0 0 0 1
	*/
	cMatrix mat = Identity(4);
	mat[0][0] = cos(fAngle);
	mat[0][1] = sin(fAngle);
	mat[1][0] = -sin(fAngle);
	mat[1][1] = cos(fAngle);

	return mat;
}

cMatrix cMatrix::Scaling(float x, float y, float z)
{
	/*

	x 0 0 0
	0 y 0 0
	0 0 z 0
	0 0 0 1
	
	*/
	cMatrix mat = Identity(4);
	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = z;

	return mat;
}

cMatrix cMatrix::LookAtLH(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp)
{
	/*l = Look Vector r = Right Vector u = Up Vector 
		r.x u.x l.x 0 r.y u.y l.y 0 r.z u.z l.z 0 - r∙eye - u∙eye - l∙eye 1*/

	cMatrix mat = Identity(4);

	cVector3 Look = (vEye - vLookAt).Normalize();
	cVector3 Right = cVector3::Cross(vUp, Look).Normalize();
	cVector3 Up = cVector3::Cross(Look, Right).Normalize();

	mat[0][0] = Right.x;
	mat[1][0] = Right.y;
	mat[2][0] = Right.z;

	mat[0][1] = Up.x;
	mat[1][1] = Up.y;
	mat[2][1] = Up.z;

	mat[0][2] = Look.x;
	mat[1][2] = Look.y;
	mat[2][2] = Look.z;

	mat[3][0] = -cVector3::Dot(Right, vEye);
	mat[3][1] = -cVector3::Dot(Up, vEye);
	mat[3][2] = -cVector3::Dot(Look, vEye);


	return mat;
}

cMatrix cMatrix::PerspectiveFovLH(float fFovY, float fAspect, float fNearZ, float fFarZ)
{
	cMatrix mat = cMatrix::Identity(4);
	float fSY = 1.0f / tanf(fFovY / 2.0f);
	float fSX = fSY / fAspect;

	mat[0][0] = fSX;
	mat[1][1] = fSY;
	mat[2][2] = fFarZ / (fFarZ - fNearZ);
	mat[2][3] = 1;
	mat[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);
	mat[3][3] = 0;
	return mat;
}

cMatrix cMatrix::Viewport(float x, float y, float w, float h, float fMinZ, float fMaxZ)
{
	cMatrix mat = cMatrix::Identity(4);
	mat[0][0] = w / 2;
	mat[1][1] = -(h / 2);
	mat[2][2] = fMaxZ - fMinZ;
	mat[3][0] = x + (w / 2);
	mat[3][1] = y + (h / 2);
	mat[3][2] = fMinZ;

	return mat;
}

cMatrix operator*(float f, cMatrix & mat)
{
	return mat * f;
}
