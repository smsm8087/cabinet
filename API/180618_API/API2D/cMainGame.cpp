#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_pImage(NULL)
	, m_pBitmap(NULL)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	//cImage::Destroy();
	SAFE_RELEASE(m_pImage);

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

	

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_pBitmap = new Bitmap(L"KakaoTalk_20180704_090834949.png");

	m_pImage = new cImage(m_pBitmap);
	m_pImage->SetTransparentColor(RGB(255, 0, 0));
}


void cMainGame::Update()
{
	g_pTimeManager->Update();



	g_pAutoReleasePool->Drain();
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

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT/*COLOR_WINDOW*/));
	
	
	//Graphics g(m_hMemDC);
	//g.DrawImage(m_pBitmap, 0, 0);
	m_pImage->Render(m_hMemDC, cUtil::MakePoint(0, 0), true);

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
	}
	break;
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_RBUTTONDOWN:
	{
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	}
}

