#include "stdafx.h"
#include "cMatrix.h"


cMatrix::cMatrix(int n)
{
	m_vecmatrix.resize(n);
	for (auto &p : m_vecmatrix)
	{
		p.resize(n);
	}
}

cMatrix::~cMatrix()
{
}

bool cMatrix::operator==(cMatrix m1)
{
	int n = m_vecmatrix.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fabs(m_vecmatrix[i][j] - m1.m_vecmatrix[i][j]) > EPSILON)
			{
				return false;
			}
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix m1)
{
	if (*this == m1)
	{
		return false;
	}
	else
		return true;
}

cMatrix cMatrix::operator+(cMatrix m1)
{
	int n = m_vecmatrix.size();
	cMatrix m = cMatrix(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m.m_vecmatrix[i][j] = m_vecmatrix[i][j] + m1.m_vecmatrix[i][j];
		}
	}
	return m;
}

cMatrix cMatrix::operator-(cMatrix m1)
{
	int n = m_vecmatrix.size();
	cMatrix m = cMatrix(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m.m_vecmatrix[i][j] = m_vecmatrix[i][j] - m1.m_vecmatrix[i][j];
		}
	}
	return m;
}

cMatrix cMatrix::operator*(float f) const
{
	int n = m_vecmatrix.size();
	cMatrix m = cMatrix(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m.m_vecmatrix[i][j] = m_vecmatrix[i][j] * f;
		}
	}
	return m;
}

cMatrix cMatrix::operator*(cMatrix m1)
{
	int n = m_vecmatrix.size();
	cMatrix m = cMatrix(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			float sum = 0.f;
			for (int k = 0; k < n; k++)
			{
				float temp = m_vecmatrix[i][k] * m1.m_vecmatrix[k][j];
				sum += temp;
			}
			m.m_vecmatrix[i][j] = sum;
		}
	}
	return m;
}

float cMatrix::Determinenet(cMatrix m1)
{
	cMatrix m = m1;
	int n = m.m_vecmatrix.size();
	float result = 0.f;
	
	for (int i = 0; i < n; i++)
	{
		if (n == 2)
		{
			float temp = Cofactor(m, i, 0);
			return temp;
		}
		float temp = Cofactor(m, i, 0);
		result += m.m_vecmatrix[i][0] * temp;
	}
	return result;
}

cMatrix cMatrix::AdJoint(cMatrix m1)
{
	cMatrix m = m1;
	int n = m.m_vecmatrix.size();
	cMatrix mConfator = cMatrix(n);
	cMatrix mTemp = cMatrix(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (n != 2)
			{
				float temp = Cofactor(m, i, j);
				mConfator.m_vecmatrix[i][j] = temp;
			}
			else
			{
				if (i == j)continue;
				m.m_vecmatrix[i][j] = -m.m_vecmatrix[i][j];
			}
		}
		m = m1;
	}
	if (n == 2)
	{
		float temp = m.m_vecmatrix[0][0];
		m.m_vecmatrix[0][0] = m.m_vecmatrix[1][1];
		m.m_vecmatrix[1][1] = temp;
		mTemp = m;
		return mTemp;

	}
	else
	{
		mTemp = mTemp.Transpose(mConfator);
		return mTemp;
	}
	
}

cMatrix cMatrix::Transpose(cMatrix m1)
{
	cMatrix mTemp = m1;

	int n = mTemp.m_vecmatrix.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)continue;
			mTemp.m_vecmatrix[i][j] = m1.m_vecmatrix[j][i];
		}
	}
	return mTemp;
}

float cMatrix::Minor(cMatrix m1,int row, int col)
{
	cMatrix m = m1;
	int n = m.m_vecmatrix.size();
	if (n == 2)
	{
		float two = m1.m_vecmatrix[0][0] * m1.m_vecmatrix[1][1] - m1.m_vecmatrix[0][1] * m1.m_vecmatrix[1][0];
		return two;
	}
	else
	{
		m.m_vecmatrix.erase(m.m_vecmatrix.begin() + row);
		for (auto &p : m.m_vecmatrix)
		{
			p.erase(p.begin() + col);
		}
		float temp = Determinenet(m);
		return temp;
		//
		/*cMatrix mTemp = cMatrix(n - 1);
		vector<float> temp;

		for (int i = 0; i < n; i++)
		{
			if (i == row)continue;
			for (int j = 0; j < n; j++)
			{
				if (j == col)continue;
				temp.push_back(m.m_vecmatrix[i][j]);
			}
		}
		int k = 0;
		for (int i = 0; i < n-1; i++)
		{
			for (int j = 0; j < n-1; j++)
			{
				mTemp.m_vecmatrix[i][j] = temp[k];
				k++;
				if (k >= (n - 1)*(n - 1))
				{
					break;
				}
			}
		}
		return Determinenet(mTemp);*/
	}
}

float cMatrix::Cofactor(cMatrix m1, int row, int col)
{
	if ((row + col) % 2 == 0)
	{
		return Minor(m1, row, col);
	}
	else
	{
		return -1 * Minor(m1, row, col);
	}
}

cMatrix cMatrix::Identity(int n)
{
	cMatrix m = cMatrix(n);
	for (int i = 0; i < n; i++)
	{
		m.m_vecmatrix[i][i] = 1;
	}
	return m;
}

cMatrix cMatrix::Invserse(cMatrix m1)//OUT float & fDeterminent)
{
	int n = m_vecmatrix.size();
	cMatrix m = m1;
	cMatrix mTemp = AdJoint(m);
	if (Determinenet(m) != 0)
	{
		float   fTemp = 1 / Determinenet(m);
		cMatrix x = fTemp * mTemp;
		return x;
	}
}

cMatrix cMatrix::Random(int n, float fMin, float fMax)
{
	cMatrix matrix = cMatrix(n);
	float randNum;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			randNum = (rand() % (int)((fMax - fMin) * 1000 )+ fMin * 1000) / 1000;
			matrix.m_vecmatrix[i][j] = randNum;
		}
	}
	return matrix;
}

void cMatrix::Print()
{
	int n = m_vecmatrix.size();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fabs(m_vecmatrix[i][j]) <= EPSILON)
			{
				printf("%.3f\t", 0.0f);
			}
			else
			{
				printf("%.3f\t", m_vecmatrix[i][j]);
			}
		}
		printf("\n");
	}
}
