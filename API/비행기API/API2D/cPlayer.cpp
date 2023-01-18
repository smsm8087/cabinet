#include "stdafx.h"
#include "cPlayer.h"
#include "cImage.h"
#include"cBulletManager.h"


cPlayer::cPlayer()
{
	m_dwColor = RGB(255, 0, 0);
	
	m_vPos.x = x;
	m_vPos.y = y;
	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);
}


cPlayer::~cPlayer()
{
}

void cPlayer::Render(HDC hdc)
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
	Graphics g(hdc);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	float fCos = (float)cos(m_fAngle);
	float fSin = (float)sin(m_fAngle);
	static Image* pImage = NULL;
	if (pImage == NULL)
		pImage = Image::FromFile(L"player1.bmp");
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
	g.DrawImage(pImage,rc1);
	g.ResetTransform();
	
	/*RECT rc1;
	rc1.left = -m_fRadius;
	rc1.top = -m_fRadius;
	rc1.right = m_fRadius;
	rc1.bottom = m_fRadius;*/
	//g.DrawImage(pImage,Rect(0, 0,pImage->GetWidth(),pImage->GetHeight()),
	//	0, 0,190,170,
	//	Unit::UnitPixel,&ia);
	
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

	SetWorldTransform(hdc, &xf);*/

	g_pBulletManager->Render(hdc);
}

void cPlayer::Update()
{
	cVector2 mouse;
	cVector2 vDir;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	
	if (GetAsyncKeyState(VK_LBUTTON)&0x0001)
	{
		
		
		mouse.x = pt.x;
		mouse.y = pt.y;
		 vDir = mouse - m_vPos;

		 m_fAngle = atan2(vDir.y, vDir.x);
		
	}
	if (GetAsyncKeyState('A') & 0X8000)
	{
		m_fAngle -= 0.1f;
	
	}
	else if (GetAsyncKeyState('D') & 0X8000)
	{
		m_fAngle += 0.1f;
		
	}
	m_vDir = cVector2(cosf(m_fAngle), sinf(m_fAngle));
	
	if (m_vPos.x== mouse.x&&m_vPos.y == mouse.y)
	{
		m_vPos.x = mouse.x;
		m_vPos.y = mouse.y;
	}

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

void cPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	
}
