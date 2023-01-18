#include "stdafx.h"
#include "cMainGame.h"
//#include "cAirplane.h"
#include"cImage.h"
#include "cAstar.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)										//�ڵ��ʱ�ȭ�� �÷��̾�Ŭ���� �����Ҵ�
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	
{
	m_bg = new cImage("map1.bmp");
}

cMainGame::~cMainGame()										//�Ҹ��� : ��ũ���Լ��� ��� ����������Ʈ�� �����Ҵ�� ��ü�� �����.
{
	SAFE_DELETE(m_pPlayer);
	
	ClearEnemy();

	//cTimeManager::GetInstance()->Destroy();
	g_pTimeManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()										//�ʱ�ȭ���ΰ���
{
	srand((unsigned int)time(NULL));						//�̰ž��ϸ� �����Լ� ����������������
	InitStage(1);				
	//1���������� �ʱ�ȭ
	/*m_astar = new cAstar;
	m_astar->Init();*/
	

	
}

void cMainGame::Update()									//������Ʈ
{
	g_pTimeManager->Update();								//�̱���� Ÿ�ӸŴ����� ������Ʈ�Ѵ�.

	
	
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
	switch (message)											//Ű�����̺�Ʈó�������� �������Լ��� �����´�. 
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

void cMainGame::InitStage(int nStage)							//���������ʱ�ȭ
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);


}

void cMainGame::ClearEnemy()									//�������� �����.
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

