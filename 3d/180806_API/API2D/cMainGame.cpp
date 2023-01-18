#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "cTile.h"



cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_isLShift(false)
	, m_pImage(NULL)
	, m_vPlayer(500, 400)
{
}

cMainGame::~cMainGame()
{
	for (auto p : m_vecTile)
	{
		SAFE_DELETE(p);
	}
	m_vecTile.clear();
	SAFE_RELEASE(m_pImage);

	g_pTimeManager->Destroy();

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
	
	for (size_t i = 0; i < TILE_V; i++)
	{
		for (size_t j = 0; j < TILE_H; j++)
		{
			cTile* pTile = new cTile(i, j, rand() % NUM_TILE_TYPE);
			m_vecTile.push_back(pTile);
		}
	}
	

	// 848 x 431
	cImage* pImage = cImage::Create("back.bmp");
	m_pImage = new cImage(ST_SIZE(300, 300));
	m_pImage->Render(pImage, ST_SIZE(300, 300));
	SAFE_RELEASE(pImage);

	for (auto p : m_vecTile)
	{
		p->m_nCheckDepth = 0;
		p->m_nTileType = rand() % NUM_TILE_TYPE;
	}
	for (auto p : m_vecTile)
	{
		p->CheckDelete(m_vecTile);
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);
}


void cMainGame::Update()
{
	g_pTimeManager->Update();

	for (auto p : m_vecTile)
	{
		p->Update();
	}

	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		m_isLShift = true;
	}
	else if (m_isLShift)
	{
		m_isLShift = false;
		MessageBoxA(g_hWnd,
			"A",
			0,
			0);
	}
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
	
	POINT pt = cUtil::MakePoint(0, 0);
	m_pImage->Render(m_hMemDC, pt, true);

	cUtil::DrawCircle(m_hMemDC, 30, m_vPlayer.ToPoint());
	
	for (size_t i = 0; i < 3; i++)
	{
		m_vBullet[i] = m_vBullet[i] + m_vBulletVel[i] * g_pTimeManager->GetElapsedTime();
		cUtil::DrawCircle(m_hMemDC, 5, m_vBullet[i].ToPoint());
	}
	
	/*
	for (auto p : m_vecTile)
	{
		p->Render(m_hMemDC);
	}
	*/

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
	case WM_KEYDOWN:
	{
		UINT_PTR temp = wParam;
		temp = temp;
	}
		break;
	case WM_LBUTTONDOWN:
	{
		cVector2 vMouse(LOWORD(lParam), HIWORD(lParam));
		m_vBulletVel[0] = (vMouse - m_vPlayer).Normalize();
		float fAngle = atan2(m_vBulletVel[0].y, m_vBulletVel[0].x);
		m_vBulletVel[1].x = cosf(fAngle + PI / 6);
		m_vBulletVel[1].y = sinf(fAngle + PI / 6);
		m_vBulletVel[2].x = cosf(fAngle - PI / 6);
		m_vBulletVel[2].y = sinf(fAngle - PI / 6);
		for (size_t i = 0; i < 3; i++)
		{
			m_vBullet[i] = m_vPlayer;
			m_vBulletVel[i] = m_vBulletVel[i] * 300;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_RBUTTONDOWN:
	{
		for (auto p : m_vecTile)
		{
			p->m_nCheckDepth = 0;
			p->m_nTileType = rand() % NUM_TILE_TYPE;
		}
		for (auto p : m_vecTile)
		{
			p->CheckDelete(m_vecTile);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	}
}


