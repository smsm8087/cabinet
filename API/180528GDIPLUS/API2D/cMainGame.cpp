#include "stdafx.h"
#include "cMainGame.h"
#include "cCrt.h"
#include "cPlayer.h"
#include "cAirplane.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_pCrt(NULL)
	, m_pAirplane(NULL)
	, m_nCommandCount(0)
{
	m_fLastCommandTime = GetTickCount() / 1000.f;
}

cMainGame::~cMainGame()
{
	GdiplusShutdown(m_ulGdiplusToken);

	g_pTimeManager->Destroy();

	SAFE_DELETE(m_pCrt);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);

	RECT rcDst;
	SetRect(&rcDst, 100, 100, 210, 251);
	m_pCrt = new cCrt(rcDst);

	cPlayer* pPlayer = new cPlayer();
	pPlayer->Init(cVector2(0, 0));
	m_pAirplane = pPlayer;
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (GetTickCount() / 1000.f - m_fLastCommandTime >= 0.5f)
	{
		m_nCommandCount = 0;
	}

	RECT rcBox;
	SetRect(&rcBox, 400, 100, 550, 250);
	m_pCrt->Update(rcBox);
	
	if(m_pAirplane)
		m_pAirplane->Update();
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

	Graphics g(m_hMemDC);

	SolidBrush b(Color::Blue);
	Rect r(0, 0, rc.right, rc.bottom);
	g.FillRectangle(&b, r);

	
	//r = Rect(100, 100, 100, 100);
	
	Matrix mat;
	mat.Rotate(30);
	//g.SetTransform(&mat);

	ImageAttributes ia;
	ColorMatrix cm = {
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1
	};
	ia.SetColorMatrix(&cm);
	static Image* pImage = NULL;
	if(pImage == NULL)
		pImage = Image::FromFile(L"optimized-sprite-sheet.png");
	g.DrawImage(pImage, 
		Rect(0, 0, pImage->GetWidth(), pImage->GetHeight()),
		0, 0,
		pImage->GetWidth(), pImage->GetHeight(),
		Unit::UnitPixel, &ia);
	

	//g.FillRec
	//FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT/*COLOR_WINDOW*/));
	
	
	if (m_pAirplane)
	{
		m_pAirplane->Render(m_hMemDC);
	}

	TextOut(m_hMemDC, 100, 100, m_szCopyCommand, strlen(m_szCopyCommand));
	//m_pCrt->Render(m_hMemDC);
	
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
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
	}
	break;

	case WM_KEYUP:
	{
		/*
		if (m_nCommandCount == 0 ||
			GetTickCount() / 1000.f - m_fLastCommandTime < 0.5f)
		{
			m_szCommand[m_nCommandCount++] = wParam;
			memcpy(m_szCopyCommand, m_szCommand, m_nCommandCount);
			m_szCopyCommand[m_nCommandCount] = '\0';
			m_fLastCommandTime = GetTickCount() / 1000.f;
		}
		*/
	}
	break;
	}
}

