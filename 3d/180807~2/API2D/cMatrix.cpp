#include "stdafx.h"
#include "cMatrix.h"
//#include "cVector3.h"
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

cMatrix::cRow & cMatrix::operator[](int nIndex) 
{
	return m_vecRow[nIndex];
}

bool cMatrix::operator==(cMatrix & m)
{
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			if (fabs((*this)[r][c] - m[r][c]) > EPSILON) 
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix & m)
{
	return !(*this == m);
}

cMatrix cMatrix::operator+(cMatrix & m)
{
	cMatrix mat(Dimension());
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			mat[r][c] = (*this)[r][c] + m[r][c];
		}
	}
	return mat;
}

cMatrix cMatrix::operator-(cMatrix & m)
{
	cMatrix mat(Dimension());
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			mat[r][c] = (*this)[r][c] - m[r][c];
		}
	}
	return mat;
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

cMatrix cMatrix::operator*(cMatrix & m)
{
	cMatrix mat(Dimension());
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			mat[r][c] = 0.0f;
			for (int i = 0; i < Dimension(); i++)
			{
				mat[r][c] += (*this)[r][i] * m[i][c];
			}
		}
	}
	return mat;
}

cMatrix cMatrix::Transpose()
{
	cMatrix mat(Dimension());
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			mat[r][c] = (*this)[c][r];
		}
	}
	return mat;
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix mat(nDimension);
	for (int r = 0; r < nDimension; r++)
	{
		for (int c = 0; c < nDimension; c++)
		{
			mat[r][c] = (r == c) ? 1.0f : 0.0f;
		}
	}
	return mat;
}

cMatrix cMatrix::Invserse(float & fDeterminent)
{
	fDeterminent = Determinent();
	if (fabs(fDeterminent) < EPSILON)
	{
		fDeterminent = 0.0f;
		return cMatrix(0);
	}
	return Adjoint() * (1 / fDeterminent);
}

cMatrix cMatrix::Random(int nDimension, float fMin, float fMax)
{
	int nRange = (int)((fMax - fMin) * 1000);
	cMatrix mat(nDimension);
	for (int r = 0; r < nDimension; r++)
	{
		for (int c = 0; c < nDimension; c++)
		{
			mat[r][c] = (rand() % nRange) / 1000.f + fMin;
		}
	}
	return mat;
}

void cMatrix::Print()
{
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			if (fabs((*this)[r][c]) < EPSILON)
				printf("%8.3f", 0.0f);
			else
				printf("%8.3f", (*this)[r][c]);
		}
		printf("\n");
	}
}

int cMatrix::Dimension()
{
	return (int)m_vecRow.size();
}

float cMatrix::Determinent()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1]
			- (*this)[0][1] * (*this)[1][0];
	}

	float fDeterminent = 0.0f;
	for (int i = 0; i < Dimension(); i++)
	{
		fDeterminent += (*this)[i][0] * Cofactor(i, 0);
	}
	return fDeterminent;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix mat(Dimension());
	for (int r = 0; r < Dimension(); r++)
	{
		for (int c = 0; c < Dimension(); c++)
		{
			mat[r][c] = Cofactor(c, r);
		}
	}
	return mat;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = ((nRow + nCol) % 2) == 0 ? 1 : -1;
	return nConst * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix mat(Dimension() - 1);
	int mr = 0;
	int mc = 0;
	for (int r = 0; r < Dimension(); r++)
	{
		if (r == nRow) continue;
		mc = 0;
		for (int c = 0; c < Dimension(); c++)
		{
			if (c == nCol) continue;
			mat[mr][mc] = (*this)[r][c];
			mc++;
		}
		mr++;
	}
	return mat.Determinent();
}

cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix mat = Identity(4);

	mat[3][0] = x;
	mat[3][1] = y;
	mat[3][2] = z;

	return mat;
}

cMatrix cMatrix::RotationX(float fAngle)
{
	cMatrix mat = Identity(4);
	mat[1][1] = cosf(fAngle);
	mat[1][2] = sinf(fAngle);
	mat[2][1] = -sinf(fAngle);
	mat[2][2] = cosf(fAngle);
	return mat;
}

cMatrix cMatrix::RotationY(float fAngle)
{
	cMatrix mat = Identity(4);
	mat[0][0] = cosf(fAngle);
	mat[0][2] = -sinf(fAngle);
	mat[2][0] = sinf(fAngle);
	mat[2][2] = cosf(fAngle);
	return mat;
}

cMatrix cMatrix::RotationZ(float fAngle)
{
	cMatrix mat = Identity(4);
	mat[0][0] = cosf(fAngle);
	mat[0][1] = sinf(fAngle);
	mat[1][0] = -sinf(fAngle);
	mat[1][1] = cosf(fAngle);
	return mat;
}

cMatrix cMatrix::Scaling(float x, float y, float z)
{
	cMatrix mat = Identity(4);
	mat[0][0] = x;
	mat[1][1] = y;
	mat[2][2] = z;
	return mat;
}

cMatrix cMatrix::LookAtLH(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp)
{
	cVector3 look = (vLookAt - vEye).Normalize();
	cVector3 right = cVector3::Cross(vUp, look).Normalize();
	cVector3 up = cVector3::Cross(look, right).Normalize();

	cMatrix mat = cMatrix::Identity(4);
	/*
	rx  ux  lx  0
	ry  uy	ly	0
	rz	uz  lz	0
	*/
	mat[0][0] = right.x;
	mat[1][0] = right.y;
	mat[2][0] = right.z;

	mat[0][1] = up.x;
	mat[1][1] = up.y;
	mat[2][1] = up.z;

	mat[0][2] = look.x;
	mat[1][2] = look.y;
	mat[2][2] = look.z;

	mat[3][0] = -cVector3::Dot(right, vEye);
	mat[3][1] = -cVector3::Dot(up, vEye);
	mat[3][2] = -cVector3::Dot(look, vEye);


	return mat;
}

//비율에 대한 내용이 fAspect
cMatrix cMatrix::PerspectiveFovLH(float fFovY, float fAspect, float fNearZ, float fFarZ)
{
	cMatrix mat = cMatrix::Identity(4);
	float fScaleY = 1.0f / tanf(fFovY / 2.0f);
	float fScaleX = fScaleY / fAspect;
	/*
	fscale x		0		0					0
	0		fscaleY		0					0
	0			0	far/(far-near)			1
	0			0	- far*near/(far-near)	0
	*/

	mat[0][0] = fScaleX;
	mat[1][1] = fScaleY;
	mat[2][2] = fFarZ / (fFarZ - fNearZ);
	mat[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);

	mat[2][3] = 1;
	mat[3][3] = 0;
	return mat;
}

cMatrix cMatrix::Viewport(float x, float y, float w, float h, float fMinZ, float fMaxZ)
{
	cMatrix mat = cMatrix::Identity(4);
	mat[0][0] = w / 2;
	mat[1][1] = -(h / 2);
	mat[2][2] = fMaxZ - fMaxZ;
	mat[3][0] = x + (w / 2);
	mat[3][1] = y + (h / 2);
	mat[3][2] = fMaxZ;
	/*
	Width / 2			0			0			0
	0		   -(Height/2)		0			0
	0				0		MaxZ - MinZ		0
	X+(Width / 2) Y+(Height / 2) MinZ			1
	*/
	return mat;
}

cMatrix operator*(float f, cMatrix& m)
{
	return m * f;
}