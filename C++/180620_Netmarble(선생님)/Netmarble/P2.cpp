#include "stdafx.h"
#include "P2.h"


P2::P2()
{
}


P2::~P2()
{
}

void P2::Excute(int nDimension, int aMatrix[][3])
{
	vector<vector<int>> vecMatrix(nDimension);

	for (size_t i = 0; i < nDimension; i++)
	{
		vecMatrix[i].resize(nDimension);
	}

	for (size_t i = 0; i < nDimension; i++)
	{
		for (size_t j = 0; j < nDimension; j++)
		{
			vecMatrix[i][j] = CalcValue(nDimension, i, j, aMatrix);
		}
	}

	for (size_t i = 0; i < nDimension; i++)
	{
		for (size_t j = 0; j < nDimension; j++)
		{
			printf("%4d", vecMatrix[i][j]);
		}
		printf("\n");
	}
}

int P2::CalcValue(int nDimension, int nRow, int nCol, int aMatrix[][3])
{
	int n = 0;
	for (size_t i = 0; i < nDimension; i++)
	{
		n += aMatrix[nRow][i];
		n += aMatrix[i][nCol];
	}
	n -= aMatrix[nRow][nCol];
	return n;
}
