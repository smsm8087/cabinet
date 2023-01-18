#include "stdafx.h"
#include "cEnemy.h"
#include"cImage.h"
#include"cBulletManager.h"


cEnemy::cEnemy()
	: m_eState(E_IDLE)
	, m_fIdleTime(2.0f + (rand() % 200) / 100.f)
	, m_fPassedIdleTime(0.0f)
	, m_fAmount(0.0f)
	, m_fAccAmount(0.0f)
	, m_fTargetAngle(0.0f)
{
	m_dwColor = RGB(0, 0, 255);
	
	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);
}

cEnemy::~cEnemy()
{
}

void cEnemy::Update()
{
	if (m_eState == E_IDLE)
	{
		m_fPassedIdleTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedIdleTime >= m_fIdleTime)
		{
			if (m_vecTarget.empty()) return;

			// 회전량 계산
			m_eState = E_ROTATE;
			cVector2 vDir = m_vecTarget.front()->GetPosition() - m_vPos;
			m_fTargetAngle = atan2(vDir.y, vDir.x);
			m_fAmount = m_fTargetAngle - m_fAngle;
			while (m_fAmount < -PI)
				m_fAmount += 2 * PI;
			while (m_fAmount > PI)
				m_fAmount -= 2 * PI;

			m_fAngleSpeed = m_fAmount > 0 ? 0.1f : -0.1f;
			m_fAccAmount = 0.0f;
			m_fPassedIdleTime = 0.0f;
		}
	}
	else if (m_eState == E_ROTATE)
	{
		m_fAngle += m_fAngleSpeed;
		m_fAccAmount += m_fAngleSpeed;
		if (fabs(m_fAccAmount) >= fabs(m_fAmount))
		{
			m_fAngle = m_fTargetAngle;
			Fire(m_vecTarget.front());
			m_eState = E_IDLE;
		}
	}

	cAirplane::Update();
}

void cEnemy::Render(HDC hdc)
{
	Graphics g(hdc);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	float fCos = (float)cos(m_fAngle);
	float fSin = (float)sin(m_fAngle);
	static Image* pImage = NULL;
	if (pImage == NULL)
		pImage = Image::FromFile(L"enemy1.bmp");
	Rect rc1;

	//r = Rect(100, 100, 100, 100);
	Matrix mat;

	mat.SetElements(fCos, fSin, -fSin, fCos, m_vPos.x, m_vPos.y);
	//int size = 0.5;
	//mat.Scale(size, size);
	mat.Scale(0.5, 0.5);
	g.SetTransform(&mat);

	ImageAttributes ia;

	int tempx = pImage->GetWidth() / 2;
	int tempy = pImage->GetHeight() / 2;
	rc1.X = -tempx;
	rc1.Y = -tempy;
	rc1.Width = pImage->GetWidth();
	rc1.Height = pImage->GetHeight();
	g.DrawImage(pImage, rc1);
	g.ResetTransform();

	//XFORM xf;
	//SetGraphicsMode(hdc, GM_ADVANCED);

	//float fCos = (float)cos(m_fAngle);
	//float fSin = (float)sin(m_fAngle);

	//xf.eM11 = fCos;
	//xf.eM12 = fSin;
	//xf.eM21 = -fSin;
	//xf.eM22 = fCos;
	//xf.eDx = m_vPos.x;
	//xf.eDy = m_vPos.y;

	//SetWorldTransform(hdc, &xf);

	/*cVector2 vCannonEndPoint(m_fCannonLen * cosf(m_fAngle), m_fCannonLen * sinf(m_fAngle));
	MoveToEx(hdc, m_vPos.x, m_vPos.y, NULL);
	LineTo(hdc, m_vPos.x + vCannonEndPoint.x, m_vPos.y + vCannonEndPoint.y);
	cUtil::DrawEllipse(hdc, m_fRadius, m_vPos);*/

	/*HBRUSH hBrush, hOldBrush;
	hBrush = CreateSolidBrush(m_dwColor);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	*/
	/*cUtil::DrawEllipse(hdc, m_fRadius, cVector2(0,0));*/

	//i_player->Render(hdc, 0, 0, m_fRadius*2);

	/*SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);*/

	//MoveToEx(hdc, 0, 0, NULL);
	//LineTo(hdc, m_fCannonLen,0);


	//xf.eM11 = 1;
	//xf.eM12 = 0;
	//xf.eM21 = 0;
	//xf.eM22 = 1;
	//xf.eDx = (float)0;
	//xf.eDy = (float)0;

	//SetWorldTransform(hdc, &xf);

	//g_pBulletManager->Render(hdc);
}
