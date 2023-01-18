#pragma once
#define N  3
class cMakeRowCol
{
private:
	//행과열의 값을정해줄 변수
	int			m_matrix[N][N];
	int			m_aftermatrix[N][N];
public:
	cMakeRowCol();
	~cMakeRowCol();
	void make_Nmatrix();
	void make_difference();
	void printarray();
};

