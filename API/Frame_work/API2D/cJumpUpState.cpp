#include "stdafx.h"
#include "cJumpUpState.h"
#include "cJumpDownState.h"
#include "cCrt.h"

cJumpUpState::cJumpUpState()
{
}


cJumpUpState::~cJumpUpState()
{
}

void cJumpUpState::Update(cCrt * pCrt, const RECT& rcBox)
{
	if (!pCrt) return;

	pCrt->m_vVel = pCrt->m_vVel + pCrt->m_vAcc * g_pTimeManager->GetElapsedTime();

	if (pCrt->m_vVel.x > MAX_SPEED) pCrt->m_vVel.x = MAX_SPEED;
	if (pCrt->m_vVel.x < -MAX_SPEED) pCrt->m_vVel.x = -MAX_SPEED;
	
	RECT rcDst = pCrt->GetDestRect();
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &rcDst, &rcBox))
	{
		if (rcTemp.right - rcTemp.left > rcTemp.bottom - rcTemp.top)
		{
			pCrt->m_vVel.y = 0.0;
		}
		else
		{
			pCrt->m_vVel.x = 0.0f;
		}
	}

	pCrt->m_vPos = pCrt->m_vPos + pCrt->m_vVel;

	if (pCrt->m_vVel.y >= 0)
	{
		pCrt->m_pState = cJumpDownState::GetInstance();
	}
}
