#include "stdafx.h"
#include "cMainGame.h"
#include "cMatrix.h"
#include "cCube.h"
#include "cGrid.h"
#include "cCamera.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_pCube(new cCube)
	, m_pCamera(new cCamera)
{
	m_pGrid = new cGrid();
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);

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

	m_pCamera->SetTarget(m_pCube->GetPosition());

	g_matView = cMatrix::LookAtLH(cVector3(0, 10, 0), cVector3(0, 0, 0), cVector3(0, 1, 0));
	g_matProj = cMatrix::PerspectiveFovLH(PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
	g_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}


void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	m_pCamera->Update();
	m_pCube->Update();

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

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_BACKGROUND));
	
	m_pGrid->Render(m_hMemDC);
	m_pCube->Render(m_hMemDC);

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
	if(m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_KEYDOWN:
	{
	}
	break;
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


