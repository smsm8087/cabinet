#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	m_dwColor = RGB(255, 0, 0);
}


cPlayer::~cPlayer()
{
}

void cPlayer::Update()
{
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}

	m_vDir = cVector2(cosf(m_fAngle), sinf(m_fAngle));

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_vPos = m_vPos + m_vDir * m_fSpeed;
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		m_vPos = m_vPos - m_vDir * m_fSpeed;
	}

	cAirplane::Update();
}
