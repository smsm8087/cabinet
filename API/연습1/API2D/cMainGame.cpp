#include "stdafx.h"
#include "cMainGame.h"
//#include "cAirplane.h"
#include"cImage.h"
#include "cAstar.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)										//핸들초기화및 플레이어클래스 동적할당
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	
{
	m_bg = new cImage("map1.bmp");
}

cMainGame::~cMainGame()										//소멸자 : 매크로함수로 써논 세이프딜리트로 동적할당된 객체를 지운다.
{
	SAFE_DELETE(m_pPlayer);
	
	ClearEnemy();

	//cTimeManager::GetInstance()->Destroy();
	g_pTimeManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()										//초기화메인게임
{
	srand((unsigned int)time(NULL));						//이거안하면 랜드함수 못씀같은값만나옴
	InitStage(1);				
	//1스테이지로 초기화
	/*m_astar = new cAstar;
	m_astar->Init();*/
	

	
}

void cMainGame::Update()									//업데이트
{
	g_pTimeManager->Update();								//싱글톤된 타임매니저를 업데이트한다.

	
	
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
	
	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_WINDOW));
	
	/*m_astar->Render(m_hMemDC);*/
	m_bg->Rendermap(m_hMemDC, rc.left, rc.top, rc.right, rc.bottom);

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
	switch (message)											//키보드이벤트처리를위해 윈도우함수를 가져온다. 
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			
		}
		break;
		}
	}
	break;
	}
}

void cMainGame::InitStage(int nStage)							//스테이지초기화
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);


}

void cMainGame::ClearEnemy()									//적군들을 지운다.
{
	for (auto p : m_vecEnemy)
	{
		SAFE_DELETE(p);
	}
	m_vecEnemy.clear();
}

void cMainGame::OutMap(HDC hDest)
{/*
	static int nX = MAPSIZEX - WINSIZE_X;

	if (nX < 0)
	{
		BitBlt(hDest, 0, -nX, WINSIZE_Y, WINSIZE_X + nX, g_Image[IMG_MAP].MemDC, 0, 0, SRCCOPY);
		BitBlt(hDest, 0, 0, WINSIZE_Y, -nX, g_Image[IMG_MAP].MemDC, MAPSIZEX+nX, 0, SRCCOPY);
	}
	else
	{
		BitBlt(hDest, 0, 0, WINSIZE_X, WINSIZE_Y, g_Image[IMG_MAP].MemDC, 0 , nX, SRCCOPY);
	}
	nX -= 5;
	if (nX + WINSIZE_X <= 0)
	{
		nX += MAPSIZEX;
	}*/
}

