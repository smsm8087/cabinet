#pragma once

class iMinerState;

class cMiner
{
public:
	cMiner();
	~cMiner();

	iMinerState*	m_pState;
	float			m_fThirsty;
	float			m_fTired;
	float			m_fGoldNuget;
	float			m_fTotalGold;
	bool			m_isMoving;
	POINT			m_ptPosition;
	ePlace			m_eStart;
	ePlace			m_eDest;
	float			m_fPassedTime;

	void Init(iMinerState* pState);
	void Update();
	void Render(HDC hdc);
};

