#pragma once
class cZigZagMatrix
{
public:
	cZigZagMatrix();
	~cZigZagMatrix();
	unsigned long long **matrix;
	unsigned long long makezigzag(int _n, int _rowindex, int _colindex);
};

