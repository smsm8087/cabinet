#include "stdafx.h"
#include "cCrt.h"
#include "cSpriteSheetAnimation.h"

//
//cCrt::cCrt(const RECT& rcDst)
//	: m_sAnimName("right")
//	, m_vVel(0.0f, 0.0f)
//	, m_vAcc(0.0f, 10.0f)
//{
//	m_vPos = cVector2(rcDst.left, rcDst.top);
//	
//	m_stSize.nWidth = rcDst.right - rcDst.left;
//	m_stSize.nHeight = rcDst.bottom - rcDst.top;
//
//	cSpriteSheetAnimation* pAnimation = new cSpriteSheetAnimation("player.bmp");
//	pAnimation->SetInterval(0.1f);
//	POINT pt;
//	pt.x = 0; pt.y = 0;
//	pAnimation->SetAnimationFrame(6, 6, pt, ST_SIZE(110, 151));
//	m_mapAnimation["left"] = pAnimation;
//
//	pAnimation = new cSpriteSheetAnimation("player.bmp");
//	pAnimation->SetInterval(0.1f);
//	pt.x = 0; pt.y = 151;
//	pAnimation->SetAnimationFrame(6, 6, pt, ST_SIZE(110, 151));
//	m_mapAnimation["right"] = pAnimation;
//
//	RECT rc;
//	GetClientRect(g_hWnd, &rc);
//	m_fGroundY = rc.bottom * 0.8f;
//
//	if(rcDst.bottom >= m_fGroundY)
//	{
//		m_pState = cLandingState::GetInstance();
//	}
//	else
//	{
//		m_pState = cJumpDownState::GetInstance();
//	}
//}
//
//cCrt::~cCrt()
//{
//}
//
//void cCrt::Update(const RECT& rcBox)
//{
//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	{
//		m_sAnimName = "left";
//	}
//	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	{
//		m_sAnimName = "right";
//	}
//
//	if(m_sAnimName != "")
//		m_mapAnimation[m_sAnimName]->Update();
//
//	if(m_pState)
//		m_pState->Update(this, rcBox);
//}
//
//void cCrt::Render(HDC hdc)
//{
//	if (m_sAnimName != "")
//	{
//		RECT rc = GetDestRect();
//		m_mapAnimation[m_sAnimName]->Render(hdc, rc);
//	}
//}
//
//RECT cCrt::GetDestRect()
//{
//	RECT rc;
//	rc.left = m_vPos.x;
//	rc.top = m_vPos.y;
//	rc.right = m_vPos.x + m_stSize.nWidth;
//	rc.bottom = m_vPos.y + m_stSize.nHeight;
//	return rc;
//}
//
