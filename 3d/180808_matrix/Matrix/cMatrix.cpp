#include "stdafx.h"
#include "cMatrix.h"

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

cMatrix operator*(float f, cMatrix& m)
{
	return m * f;
}