#include "stdafx.h"
#include "cJumpDownState.h"
#include "cLandingState.h"
#include "cCrt.h"

cJumpDownState::cJumpDownState()
{
}


cJumpDownState::~cJumpDownState()
{
}

void cJumpDownState::Update(cCrt * pCrt, const RECT& rcBox)
{
	if (!pCrt) return;

	pCrt->m_vVel = pCrt->m_vVel + pCrt->m_vAcc * g_pTimeManager->GetElapsedTime();

	if (pCrt->m_vVel.x > MAX_SPEED) pCrt->m_vVel.x = MAX_SPEED;
	if (pCrt->m_vVel.x < -MAX_SPEED) pCrt->m_vVel.x = -MAX_SPEED;

	RECT rcDst = pCrt->GetDestRect();
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &rcDst, &rcBox))
	{
		pCrt->m_vVel.x = 0.0f;
	}

	pCrt->m_vPos = pCrt->m_vPos + pCrt->m_vVel;

	if (pCrt->m_vPos.y + pCrt->m_stSize.nHeight >= pCrt->m_fGroundY)
	{
		pCrt->m_pState = cLandingState::GetInstance();
	}
}
