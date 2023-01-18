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
	, m_dwColor(RGB(0, 0, 0))
{
	
}

cAirplane::~cAirplane()
{
}

void cAirplane::Init(const cVector2 & vPos)
{
	m_vPos = vPos;
}

void cAirplane::Update()
{
	g_pBulletManager->Update();
}

void cAirplane::Render(HDC hdc)
{
	
	/*XFORM xf;
	SetGraphicsMode(hdc, GM_ADVANCED);

	float fCos = (float)cos(m_fAngle);
	float fSin = (float)sin(m_fAngle);

	xf.eM11 = fCos;
	xf.eM12 = fSin;
	xf.eM21 = -fSin;
	xf.eM22 = fCos;
	xf.eDx = m_vPos.x;
	xf.eDy = m_vPos.y;

	SetWorldTransform(hdc, &xf);*/

	/*cVector2 vCannonEndPoint(m_fCannonLen * cosf(m_fAngle), m_fCannonLen * sinf(m_fAngle));
	MoveToEx(hdc, m_vPos.x, m_vPos.y, NULL);
	LineTo(hdc, m_vPos.x + vCannonEndPoint.x, m_vPos.y + vCannonEndPoint.y);
	cUtil::DrawEllipse(hdc, m_fRadius, m_vPos);*/

	/*HBRUSH hBrush, hOldBrush;
	hBrush = CreateSolidBrush(m_dwColor);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
*/
	/*cUtil::DrawEllipse(hdc, m_fRadius, cVector2(0,0));*/
	
	/*i_player->Render(hdc, 0, 0, m_fRadius);*/
	
	/*SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);*/

	//MoveToEx(hdc, 0, 0, NULL);
	//LineTo(hdc, m_fCannonLen,0);


	/*xf.eM11 = 1;
	xf.eM12 = 0;
	xf.eM21 = 0;
	xf.eM22 = 1;
	xf.eDx = (float)0;
	xf.eDy = (float)0;

	SetWorldTransform(hdc, &xf);

	g_pBulletManager->Render(hdc);*/
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

void cAirplane::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
