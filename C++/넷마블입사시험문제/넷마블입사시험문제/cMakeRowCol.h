#pragma once
#define N  3
class cMakeRowCol
{
private:
	//������� ���������� ����
	int			m_matrix[N][N];
	int			m_aftermatrix[N][N];
public:
	cMakeRowCol();
	~cMakeRowCol();
	void make_Nmatrix();
	void make_difference();
	void printarray();
};

