#include "stdafx.h"
#include "cMakeRowCol.h"


cMakeRowCol::cMakeRowCol()
{
	m_matrix[N][N] = { 0 };
	m_aftermatrix[N][N] = { 0 };
}


cMakeRowCol::~cMakeRowCol()
{
}

void cMakeRowCol::make_Nmatrix()
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			m_matrix[i][j] = i * N + (j+1);
		}
	}
}

void cMakeRowCol::make_difference()
{
	int k = 0; int l = 0;
	int countrow = 0; int countcol = 0;
	for (size_t countrow = 0; countrow < N; countrow++)
	{
		for (size_t countcol = 0; countcol < N; countcol++)
		{
			
			for (size_t j = 0; j < N; j++)
			{
				k += m_matrix[j][countcol];
			}

			for (size_t i = 0; i < N; i++)
			{
				l += m_matrix[countrow][i];
			}
			m_aftermatrix[countrow][countcol] = k + l - m_matrix[countrow][countcol];
			k = 0; l = 0;
		}
	}
}

void cMakeRowCol::printarray()
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			cout << m_aftermatrix[i][j];
			cout << " ";
		}
		cout << endl;
	}
}
