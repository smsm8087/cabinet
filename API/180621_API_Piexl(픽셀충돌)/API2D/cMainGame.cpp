#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_pImage(NULL)
	, m_pTank(NULL)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	SAFE_DELETE(m_pImage);

	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);

	assert(g_setObjectPool.empty() && "지워지지 않은 객체가 있음.");
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);

	m_pImage = new cImage("Testpixel.bmp");
	m_pImage->SetTransparentColor(RGB(255, 255, 255));
	m_pTank = new cImage("Tank.bmp");
	m_pTank->SetTransparentColor(RGB(255, 0, 255));
	
	ptTank.x = 20;
	ptTank.y = 20;
	
}


void cMainGame::Update()
{
	g_pTimeManager->Update();



	g_pAutoReleasePool->Drain();
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	
	//{
	//	ptTank.y-=1.f;
	//	//기울기판정

	//	if (sright != transparent && sleft == transparent)//기울기가올라가는언덕임
	//	{
	//		float a = atan2f((ptright.y - ptleft.y), (ptright.x - ptleft.x));
	//		a = a;
	//	}
	//	else if (sright == transparent && sleft != transparent)//기울기가내려가는 언덕임
	//	{
	//		float a = atan2f((ptright.y - ptleft.y), (ptright.x - ptleft.x));
	//		a = a;
	//	}
	//}
	m_ptPixelleft.x = (float)ptTank.x - 5;
	m_ptPixelleft.y = (float)ptTank.y + (float)(m_pTank->Getstsize().nHeight);
	m_ptPixelRight.x = (float)ptTank.x + (float)(m_pTank->Getstsize().nWidth) + 5;
	m_ptPixelRight.y = (float)ptTank.y + (float)(m_pTank->Getstsize().nHeight);

	m_cPixelleft = m_pImage->GetColor(m_ptPixelleft);
	r_left = to_string(GetRValue(m_cPixelleft));
	g_left = to_string(GetGValue(m_cPixelleft));
	b_left = to_string(GetBValue(m_cPixelleft));
	m_sColorleft = r_left + g_left + b_left;

	m_cPixelRight = m_pImage->GetColor(m_ptPixelRight);
	r_right = to_string(GetRValue(m_cPixelRight));
	g_right = to_string(GetGValue(m_cPixelRight));
	b_right = to_string(GetBValue(m_cPixelRight));
	m_sColorright = r_right + g_right + b_right;

	ptUP.x = (float)ptTank.x - 5;
	ptUP.y = (float)ptTank.y + (float)(m_pTank->Getstsize().nHeight - 2);
	COLORREF c = m_pImage->GetColor(ptUP);
	string r = to_string(GetRValue(c));
	string g = to_string(GetGValue(c));
	string b = to_string(GetBValue(c));
	string rgb = r + g + b;

	transparent = "255255255";
	ptTank.y++;
	if (m_sColorleft == transparent && m_sColorright == transparent)
	{
		m_ptPixelleft.y++;
		m_ptPixelRight.y++;
	}
	else
	{
		ptTank.y--;
		if (m_sColorleft != transparent && m_sColorright == transparent)
		{
			m_ptPixelRight.y++;
		}
		if (m_sColorleft == transparent && m_sColorright != transparent)
		{
			m_ptPixelleft.y++;
		}

	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (rgb != transparent)
		{
			float a = atan2f((m_ptPixelRight.y - m_ptPixelleft.y), (m_ptPixelRight.x - m_ptPixelleft.x));
			a = a;
		}
	}
	

}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (m_hMemDC == NULL)
	{
		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
		SetGraphicsMode(m_hMemDC, GM_ADVANCED);
	}

	FillRect(m_hMemDC, &rc, GetSysColorBrush(/*COLOR_GRAYTEXT*/COLOR_WINDOW));
	
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	m_pImage->Render(m_hMemDC, pt, true);
	
	
	m_pTank->Render(m_hMemDC, ptTank, true);

	/*TransparentBlt(m_hMemDC,)*/
	/*
	Graphics g(m_hMemDC);
	Pen p(&SolidBrush(Color::Red));

	for (auto p : m_vecNode)
	{
		p->Render(m_hMemDC);
	}
	*/
	TextOut(m_hMemDC, 10, 10, m_sColor.c_str(), m_sColor.length());
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}

void cMainGame::OnSize()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		RECT rc;
		rc.left = pt.x;
		rc.top = pt.y;
		rc.right = rc.left + 100;
		rc.bottom = rc.top + 100;
		m_pImage->SetColor(rc, RGB(255,255, 255));
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
	/*	pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);*/
		COLORREF c = m_pImage->GetColor(pt);
		string r = to_string(GetRValue(c));
		string g = to_string(GetGValue(c));
		string b = to_string(GetBValue(c));
		m_sColor = r + ", " + g + ", " + b;
	}
	case WM_RBUTTONDOWN:
	{
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
			ptTank.x -= 5;
		}
		break;
		case VK_RIGHT:
		{
			ptTank.x += 5;
		}break;
		default:
			break;
		}
	}
	}
}
