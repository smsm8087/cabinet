#include "stdafx.h"
#include "iMinerState.h"
#include "cMiner.h"

#define MAX_GOLD	10.0f
#define MAX_TIRED	20.0f
#define MAX_THIRSTY 30.0f

iMinerState::iMinerState()
{
}


iMinerState::~iMinerState()
{
}

/*******************************************************
 *	cMoveState
 *******************************************************/
cMoveState::cMoveState()
{
}

cMoveState::~cMoveState()
{
}

void cMoveState::Init(cMiner * pMiner)
{
	pMiner->m_ptPosition = g_ptPlace[pMiner->m_eStart];
	pMiner->m_fPassedTime = 0.0f;
}

void cMoveState::Update(cMiner * pMiner)
{
	if (pMiner->m_fPassedTime >= 1.0f)
	{
		Finish(pMiner);
		
		switch (pMiner->m_eDest)
		{
		case E_MINE:
		{
			pMiner->Init(cMineState::GetInstance());
		}
		break;
		case E_BANK:
		{
			pMiner->Init(cBankState::GetInstance());
		}
		break;
		case E_HOME:
		{
			pMiner->Init(cSleepState::GetInstance());
		}
		break;
		case E_PUB:
		{
			pMiner->Init(cDrinkState::GetInstance());
		}
		break;
		}
	}
	else
	{
		float t = pMiner->m_fPassedTime;
		float x = (1.0f - t) * g_ptPlace[pMiner->m_eStart].x + t * g_ptPlace[pMiner->m_eDest].x;
		float y = (1.0f - t) * g_ptPlace[pMiner->m_eStart].y + t * g_ptPlace[pMiner->m_eDest].y;
		pMiner->m_ptPosition.x = x;
		pMiner->m_ptPosition.y = y;
	}
}

void cMoveState::Finish(cMiner * pMiner)
{
	pMiner->m_ptPosition = g_ptPlace[pMiner->m_eDest];
	pMiner->m_eStart = pMiner->m_eDest;
}


/*******************************************************
*	cSleepState
*******************************************************/
cSleepState::cSleepState()
{
}

cSleepState::~cSleepState()
{
}

void cSleepState::Init(cMiner * pMiner)
{
}

void cSleepState::Update(cMiner * pMiner)
{
	pMiner->m_fTired -= (rand() % 1000) / 4000.f;
	if (pMiner->m_fTired < 0.0f)
	{
		pMiner->m_fTired = 0.0f;
		Finish(pMiner);
	}
}

void cSleepState::Finish(cMiner * pMiner)
{
	if (pMiner->m_fGoldNuget > MAX_GOLD)
	{
		pMiner->m_eDest = E_BANK;
	}
	else if (pMiner->m_fThirsty > MAX_THIRSTY)
	{
		pMiner->m_eDest = E_PUB;
	}
	else
	{
		pMiner->m_eDest = E_MINE;
	}
	pMiner->Init(cMoveState::GetInstance());
}

/*******************************************************
*	cDrinkState
*******************************************************/
cDrinkState::cDrinkState()
{
}

cDrinkState::~cDrinkState()
{
}

void cDrinkState::Init(cMiner * pMiner)
{
}

void cDrinkState::Update(cMiner * pMiner)
{
	pMiner->m_fThirsty -= (rand() % 1000) / 4000.f;
	if (pMiner->m_fThirsty < 0.0f)
	{
		pMiner->m_fThirsty = 0.0f;
		Finish(pMiner);
	}
}

void cDrinkState::Finish(cMiner * pMiner)
{
	if (pMiner->m_fGoldNuget > MAX_GOLD)
	{
		pMiner->m_eDest = E_BANK;
	}
	else if (pMiner->m_fTired > MAX_TIRED)
	{
		pMiner->m_eDest = E_HOME;
	}
	else 
	{
		pMiner->m_eDest = E_MINE;
	}
	pMiner->Init(cMoveState::GetInstance());
}

/*******************************************************
*	cMineState
*******************************************************/
cMineState::cMineState()
{
}

cMineState::~cMineState()
{
}

void cMineState::Init(cMiner * pMiner)
{
}

void cMineState::Update(cMiner * pMiner)
{
	pMiner->m_fGoldNuget += (rand() % 1000) / 4000.f;
	pMiner->m_fThirsty += (rand() % 1000) / 4000.f;
	pMiner->m_fTired += (rand() % 1000) / 4000.f;
	if (pMiner->m_fGoldNuget > MAX_GOLD || 
		pMiner->m_fThirsty > MAX_THIRSTY ||
		pMiner->m_fTired > MAX_TIRED)
	{
		Finish(pMiner);
	}
}

void cMineState::Finish(cMiner * pMiner)
{
	if (pMiner->m_fGoldNuget > MAX_GOLD)
	{
		pMiner->m_eDest = E_BANK;
	}
	if (pMiner->m_fThirsty > MAX_THIRSTY)
	{
		pMiner->m_eDest = E_PUB;
	}
	if (pMiner->m_fTired > MAX_TIRED)
	{
		pMiner->m_eDest = E_HOME;
	}
	pMiner->Init(cMoveState::GetInstance());
}


/*******************************************************
*	cBankState
*******************************************************/
cBankState::cBankState()
{
}

cBankState::~cBankState()
{
}

void cBankState::Init(cMiner * pMiner)
{
}

void cBankState::Update(cMiner * pMiner)
{
	float fPrev = pMiner->m_fGoldNuget;
	pMiner->m_fGoldNuget -= (rand() % 1000) / 4000.f;
	if (pMiner->m_fGoldNuget < 0.0f)
	{
		pMiner->m_fTotalGold += fPrev;
		pMiner->m_fGoldNuget = 0.0f;
		Finish(pMiner);
	}
	else
	{
		pMiner->m_fTotalGold += (fPrev - pMiner->m_fGoldNuget);
	}
}

void cBankState::Finish(cMiner * pMiner)
{
	if (pMiner->m_fThirsty > MAX_THIRSTY)
	{
		pMiner->m_eDest = E_PUB;
	}
	else if (pMiner->m_fTired > MAX_TIRED)
	{
		pMiner->m_eDest = E_HOME;
	}
	else
	{
		pMiner->m_eDest = E_MINE;
	}
	pMiner->Init(cMoveState::GetInstance());
}
