#include "stdafx.h"
#include "cMainGame.h"
#include "cCrt.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_pCrt(NULL)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	SAFE_DELETE(m_pCrt);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	m_pCrt = new cCrt;
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	m_pCrt->Update();
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
	}
	
	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT/*COLOR_WINDOW*/));
	
	RECT rcDst;
	SetRect(&rcDst, 100, 100, 210, 251);
	m_pCrt->Render(m_hMemDC, rcDst);

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
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
		}
		break;
		case VK_RIGHT:
		{
		}
		break;
		case VK_UP:
		{
		}
		break;
		case VK_DOWN:
		{
		}
		break;
		}
	}
	break;
	}
}

