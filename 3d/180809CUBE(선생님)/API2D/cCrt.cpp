#include "stdafx.h"
#include "cCrt.h"

#define CRT_SPEED 500.f

cCrt::cCrt()
{
}

cCrt::~cCrt()
{
}

void cCrt::Update()
{
	float fDeltaTime = g_pTimeManager->GetElapsedTime();
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_vWorldPos.x -= CRT_SPEED * fDeltaTime;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_vWorldPos.x += CRT_SPEED * fDeltaTime;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_vWorldPos.y -= CRT_SPEED * fDeltaTime;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_vWorldPos.y += CRT_SPEED * fDeltaTime;
	}
	if (m_vWorldPos.x < 0)
		m_vWorldPos.x = 0;
	if (m_vWorldPos.y < 0)
		m_vWorldPos.y = 0;
	if (m_vWorldPos.x > m_stMapSize.nWidth - m_stSize.nWidth)
		m_vWorldPos.x = m_stMapSize.nWidth - m_stSize.nWidth;
	if (m_vWorldPos.y > m_stMapSize.nHeight - m_stSize.nHeight)
		m_vWorldPos.y = m_stMapSize.nHeight - m_stSize.nHeight;

}

void cCrt::Render(HDC hdc, cVector2* pMapPos)
{
	cVector2 vScreen;
	vScreen = m_vWorldPos;
	if (pMapPos)
	{
		vScreen = m_vWorldPos - *pMapPos;
	}
	RECT rc = cUtil::MakeRect(vScreen.x, vScreen.y, m_stSize.nWidth, m_stSize.nHeight);
	cUtil::DrawRect(hdc, rc);
}

