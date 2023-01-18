#pragma once
class P2
{
public:
	P2();
	~P2();

	void Excute(int nDimension, int aMatrix[][3]);
	int CalcValue(int nDimension, int nRow, int nCol, int aMatrix[][3]);
};

