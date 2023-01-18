#include "stdafx.h"
#include "cLandingState.h"
#include "cCrt.h"
#include "cJumpUpState.h"


cLandingState::cLandingState()
{
}


cLandingState::~cLandingState()
{
}

void cLandingState::Update(cCrt * pCrt, const RECT& rcBox)
{
	if (!pCrt) return;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		pCrt->m_vAcc.x = -10.f;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		pCrt->m_vAcc.x = 10.f;
	}
	else 
	{
		if (pCrt->m_vVel.x < -0.001f)
		{
			pCrt->m_vAcc.x = 10.f;
		}
		else if (pCrt->m_vVel.x > 0.001f)
		{
			pCrt->m_vAcc.x = -10.f;
		}
		else 
		{
			pCrt->m_vVel.x = 0.0f;
			pCrt->m_vAcc.x = 0.0f;
		}
	}

	pCrt->m_vVel.x += pCrt->m_vAcc.x * g_pTimeManager->GetElapsedTime();

	if (pCrt->m_vVel.x > MAX_SPEED) pCrt->m_vVel.x = MAX_SPEED;
	if (pCrt->m_vVel.x < -MAX_SPEED) pCrt->m_vVel.x = -MAX_SPEED;
	
	pCrt->m_vPos.x += pCrt->m_vVel.x;
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		pCrt->m_vVel.y = -10.f;
		pCrt->m_pState = cJumpUpState::GetInstance();
	}
}
