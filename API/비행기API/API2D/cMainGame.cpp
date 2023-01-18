#include "stdafx.h"
#include "cMainGame.h"
//#include "cAirplane.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cBulletManager.h"
#include"cImage.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_pPlayer(new cPlayer)
{
	
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	
	ClearEnemy();

	//cTimeManager::GetInstance()->Destroy();
	g_pTimeManager->Destroy();
	g_pBulletManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));
	InitStage(1);
	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	for (auto p : m_vecEnemy)
	{
		p->Update();
	}

	if (m_pPlayer) m_pPlayer->Update();

	g_pBulletManager->Update();
}
int x;
int y;

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
	//FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT|COLOR_WINDOW));
	Graphics g(m_hMemDC);

	SolidBrush b(Color::Blue);
	Rect r(0, 0, rc.right, rc.bottom);
	g.FillRectangle(&b,r);
	
	//회전행렬
	//char szBuf[100];

	//wsprintf(szBuf, "%d", x);

	//TextOut(m_hMemDC, 100, 100,szBuf,strlen(szBuf) );
	//wsprintf(szBuf, "%d", y);
	//TextOut(m_hMemDC, 100, 150, szBuf, strlen(szBuf));

	//플레이어 이동
	
	m_pPlayer->Render(m_hMemDC);
	for (auto p : m_vecEnemy)
	{
		
		p->Render(m_hMemDC);
	}
	g_pBulletManager->Render(m_hMemDC);
	
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
			//cTimeManager* p = new cTimeManager;
 			m_pPlayer->Fire();
			//InitStage(1);
		}
		break;
		}
	}
	break;
	}
}

void cMainGame::InitStage(int nStage)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_pPlayer->Init(cVector2(rc.right / 2, rc.bottom / 2));

	ClearEnemy();

	int nNumEnemy = 3;
	m_vecEnemy.resize(nNumEnemy);
	for (int i = 0; i < nNumEnemy; i++)
	{
		m_vecEnemy[i] = new cEnemy;
		
		m_vecEnemy[i]->AddTarget(m_pPlayer);

		m_pPlayer->AddTarget(m_vecEnemy[i]);

		do
		{
			float x = rand() % (rc.right - (int)m_vecEnemy[i]->GetFullRadius() * 2);
			x += m_vecEnemy[i]->GetFullRadius();
			float y = rand() % (rc.bottom - (int)m_vecEnemy[i]->GetFullRadius() * 2);
			y += m_vecEnemy[i]->GetFullRadius();

			cVector2 vPos(x, y);
			m_vecEnemy[i]->Init(vPos);
		} while (CheckCollision(m_vecEnemy[i]));
		
	}
}

void cMainGame::ClearEnemy()
{
	for (auto p : m_vecEnemy)
	{
		SAFE_DELETE(p);
	}
	m_vecEnemy.clear();
}

bool cMainGame::CheckCollision(cAirplane * pAirplane)
{
	if (pAirplane && CheckCollision(pAirplane, m_pPlayer))
	{
		return true;
	}

	for (auto p : m_vecEnemy)
	{
		if (p == pAirplane) continue;
		if (p == NULL) break;
		if(CheckCollision(pAirplane, p))
			return true;
	}
	return false;
}

bool cMainGame::CheckCollision(cAirplane * pAirplane1, cAirplane * pAirplane2)
{
	if (pAirplane1 && pAirplane2)
	{
		cVector2 v1 = pAirplane1->GetPosition();
		cVector2 v2 = pAirplane2->GetPosition();
		float r1 = pAirplane1->GetBodyRadius();
		float r2 = pAirplane2->GetBodyRadius();
		cVector2 v = v2 - v1;
		if ((r1 + r2) * (r1 + r2) > (v2 - v1).LenSq())
			return true;
	}
	return false;
}
