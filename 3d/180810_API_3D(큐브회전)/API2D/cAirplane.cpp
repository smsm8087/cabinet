#include "stdafx.h"
#include "cAirplane.h"
#include "cBulletManager.h"
#include "cImage.h"

cAirplane::cAirplane()
	: m_fRadius(40.0f)
	, m_fAngle(PI * 3 / 2.0f)
	, m_fAngleSpeed(0.1f)
	, m_fSpeed(10.f)
	, m_fCannonLen(70.f)
	, m_dwColor(RGB(255, 255, 255))
	, m_pImage(NULL)
{
}

cAirplane::~cAirplane()
{
	SAFE_RELEASE(m_pImage);
	SAFE_RELEASE(m_pBullet);
	//m_pBullet->Release();
}

void cAirplane::Init(const cVector2 & vPos)
{
	m_vPos = vPos;
	m_pImage = cImage::Create("player2.bmp");
	m_pImage->AddRef();
}

void cAirplane::Update()
{
	//m_pImage->SetAngle(m_fAngle);
	g_pBulletManager->Update();
}

void cAirplane::Render(HDC hdc)
{
	m_pImage->Render(hdc, m_vPos.ToPoint(), true);
	/*
	HBRUSH hBrush, hOldBrush;
	hBrush = CreateSolidBrush(m_dwColor);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	cVector2 vCannonEndPoint(m_fCannonLen * cosf(m_fAngle), m_fCannonLen * sinf(m_fAngle));
	MoveToEx(hdc, m_vPos.x, m_vPos.y, NULL);
	LineTo(hdc, m_vPos.x + vCannonEndPoint.x, m_vPos.y + vCannonEndPoint.y);
	cUtil::DrawEllipse(hdc, m_fRadius, m_vPos);

	g_pBulletManager->Render(hdc);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	*/
	
}

void cAirplane::Fire(cAirplane* pTarget)
{
	cVector2 vCannonEndPoint(m_fCannonLen * cosf(m_fAngle), m_fCannonLen * sinf(m_fAngle));
	vCannonEndPoint = vCannonEndPoint + m_vPos;
	cVector2 vDir(0, 0);
	
	if(pTarget)
	{
		vDir = pTarget->GetPosition() - m_vPos;
		vDir = vDir.Normalize();
	}
	else
	{
		vDir.x = cosf(m_fAngle);
		vDir.y = sinf(m_fAngle);
	}

	g_pBulletManager->Fire(vCannonEndPoint, vDir, m_vecTarget);
}


float cAirplane::GetFullRadius()
{
	return m_fCannonLen;
}

float cAirplane::GetBodyRadius()
{
	return m_fRadius;
}

cVector2 cAirplane::GetPosition()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vPos;
}

void cAirplane::AddTarget(cAirplane * pTarget)
{
	m_vecTarget.push_back(pTarget);
}
