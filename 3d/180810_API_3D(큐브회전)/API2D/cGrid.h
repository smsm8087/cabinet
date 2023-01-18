#pragma once
class cGrid
{
private:
	cVector3			m_vFrontColumUp[7];
	cVector3			m_vFrontColumDown[7];
	cVector3			m_vFrontRowLeft[7];
	cVector3			m_vFrontRowRight[7];

	cVector3			m_vBackColumUp[7];
	cVector3			m_vBackColumDown[7];
	cVector3			m_vBackRowLeft[7];
	cVector3			m_vBackRowRight[7];

	cVector3			m_vBetweenRowLeft[11];
	cVector3			m_vBetweenRowRight[11];

	cVector3			m_vBetweenDownRowLeft[11];
	cVector3			m_vBetweenDownRowRight[11];


	cVector3			m_vPosX;
	cVector3			m_vPosZ;

public:
	cGrid();
	~cGrid();

	void Render(HDC hdc);
};

