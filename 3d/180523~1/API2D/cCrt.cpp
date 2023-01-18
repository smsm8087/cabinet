#include "stdafx.h"
#include "cCrt.h"
#include "cSpriteSheetAnimation.h"

cCrt::cCrt()
{
	cSpriteSheetAnimation* pAnimation = new cSpriteSheetAnimation("player.bmp");
	pAnimation->SetInterval(0.1f);
	POINT pt;
	pt.x = 0; pt.y = 0;
	pAnimation->SetAnimationFrame(6, 6, pt, ST_SIZE(110, 151));
	m_mapAnimation["left"] = pAnimation;

	pAnimation = new cSpriteSheetAnimation("player.bmp");
	pAnimation->SetInterval(0.1f);
	pt.x = 0; pt.y = 151;
	pAnimation->SetAnimationFrame(6, 6, pt, ST_SIZE(110, 151));
	m_mapAnimation["right"] = pAnimation;
}


cCrt::~cCrt()
{
}

void cCrt::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_sAnimName = "left";
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_sAnimName = "right";
	}

	if(m_sAnimName != "")
		m_mapAnimation[m_sAnimName]->Update();
}

void cCrt::Render(HDC hdc, RECT rcDst)
{
	RECT rc, rc1, rc2;

	/*bool */IntersectRect(&rc, &rc1, &rc2);
	if (m_sAnimName != "")
		m_mapAnimation[m_sAnimName]->Render(hdc, rcDst);
}
