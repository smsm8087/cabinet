#include "stdafx.h"
#include "cMainGame.h"

#include"cPlayer.h"
#include"cEnemy.h"
#include"cBulletManager.h"


cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	,m_pEnemy(NULL)
	,m_pPlayer(NULL)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pEnemy);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	/*RECT rcDst;
	SetRect(&rcDst, 100, 100, 210, 251);
	m_pCrt = new cCrt(rcDst);*/
	m_pPlayer = new cPlayer;
	m_pPlayer->Init(cVector2(500,500));
	m_pEnemy = new cEnemy;
	m_pEnemy->Init(cVector2(100, 500));
	
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	m_pPlayer->Update();
	m_pEnemy->Update();
	m_Bullet->Update();
	/*RECT rcBox;
	SetRect(&rcBox, 400, 100, 550, 250);*/
	//m_pCrt->Update(rcBox);
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
	m_pPlayer->Render(m_hMemDC);
	m_pEnemy->Render(m_hMemDC);
	m_Bullet->Render(m_hMemDC);
	//RECT rcBox;
	//SetRect(&rcBox, 400, 100, 550, 250);
	//cUtil::DrawRect(m_hMemDC, rcBox);
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

