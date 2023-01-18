#include "stdafx.h"
#include "cMiner.h"
#include "iMinerState.h"

cMiner::cMiner()
	: m_fThirsty(0.0f)
	, m_fTired(0.0f)
	, m_fGoldNuget(0.0f)
	, m_fTotalGold(0.0f)
	, m_isMoving(false)
	, m_eStart(E_HOME)
	, m_eDest(E_MINE)
	, m_fPassedTime(0.0f)
	, m_pState(NULL)
{
}

cMiner::~cMiner()
{
}

void cMiner::Init(iMinerState* pState)
{
	m_ptPosition = g_ptPlace[m_eStart];
	m_pState = pState;
	m_pState->Init(this);
}

void cMiner::Update()
{
	m_fPassedTime += g_pTimeManager->GetElapsedTime();
	m_pState->Update(this);
}

void cMiner::Render(HDC hdc)
{
	int y = 100;
	string s = "";
	s = "목마름 : " + to_string((int)m_fThirsty);
	TextOut(hdc, 600, y, s.c_str(), s.length());

	y += 20;
	s = "피로도 : " + to_string((int)m_fTired);
	TextOut(hdc, 600, y, s.c_str(), s.length());

	y += 20;
	s = "금덩이 : " + to_string((int)m_fGoldNuget);
	TextOut(hdc, 600, y, s.c_str(), s.length());

	y += 20;
	s = "총재산 : " + to_string((int)m_fTotalGold);
	TextOut(hdc, 600, y, s.c_str(), s.length());

	RECT rc;
	rc.left = m_ptPosition.x - 10;
	rc.top = m_ptPosition.y - 10;
	rc.right = m_ptPosition.x + 10;
	rc.bottom = m_ptPosition.y + 10;

	cUtil::DrawRect(hdc, rc);
}
