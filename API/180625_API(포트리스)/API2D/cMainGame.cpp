#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"

#define WIND_DELTA 10.0f
#define TIME_DELTA 0.5f

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_pFront(NULL)
	, m_pBack(NULL)
	, m_fTankAngle(0.0f)
	, m_fPassedTime(0.0f)
	, m_vAcc(0, 100)
	, m_vVel(0, 0)
	, m_fInterval(1.0f)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	SAFE_DELETE(m_pFront);
	SAFE_DELETE(m_pBack);

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

	m_pFront = new cImage("front.bmp");
	m_pFront->SetTransparentColor(RGB(255, 0, 255)); 

	m_pBack = new cImage("back.bmp");

	m_vTank.x = 300;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vEnemy.x = 800;

	m_vBullet = cVector2(0, 0);

	for (int i = 0; i < E_BTN_COUNT; i++)
	{
		m_aButton[i] = new cButton();
		m_aButton[i]->SetDelegate(this);
		m_aButton[i]->SetTag(i);
	}
	RECT rcBtn;
	SetRect(&rcBtn, 10, 10, 40, 40);
	m_aButton[E_BTN_WIND_DEC]->Init(rcBtn, "◀");
	SetRect(&rcBtn, 45, 10, 75, 40);
	m_aButton[E_BTN_WIND_INC]->Init(rcBtn, "▶");

	SetRect(&rcBtn, 10, 50, 40, 80);
	m_aButton[E_BTN_TIME_DEC]->Init(rcBtn, "◀");
	SetRect(&rcBtn, 45, 50, 75, 80);
	m_aButton[E_BTN_TIME_INC]->Init(rcBtn, "▶");
}


void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_vTank.x -= 1;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_vTank.x += 1;
	}
	m_vTank.y = m_pFront->PointAt(m_vTank.x, RGB(255, 0, 255));

	float fLeft = m_pFront->PointAt(m_vTank.x - 5, RGB(255, 0, 255));
	float fRight = m_pFront->PointAt(m_vTank.x + 5, RGB(255, 0, 255));
	m_fTankAngle = atan2(fRight - fLeft, 10);

	m_vEnemy.y = m_pFront->PointAt(m_vEnemy.x, RGB(255, 0, 255));
	
	m_vVel = m_vVel + m_vAcc * g_pTimeManager->GetElapsedTime();
	m_vBullet = m_vBullet + m_vVel * g_pTimeManager->GetElapsedTime();

	for (int i = 0; i < E_BTN_COUNT; i++)
	{
		m_aButton[i]->Update();
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
	
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	m_pBack->Render(m_hMemDC, pt, false);
	m_pFront->Render(m_hMemDC, pt, true);

	//m_fTankAngle
	XFORM xf;
	xf.eM11 = cosf(m_fTankAngle);
	xf.eM12 = sinf(m_fTankAngle);
	xf.eM21 = -sinf(m_fTankAngle);
	xf.eM22 = cosf(m_fTankAngle);
	xf.eDx = m_vTank.x;
	xf.eDy = m_vTank.y;
	SetWorldTransform(m_hMemDC, &xf);
	
	RECT rcTank;
	SetRect(&rcTank,-15, -20, 15, 0);
	cUtil::DrawRect(m_hMemDC, rcTank);

	xf.eM11 = 1;
	xf.eM12 = 0;
	xf.eM21 = 0;
	xf.eM22 = 1;
	xf.eDx = 0;
	xf.eDy = 0;
	SetWorldTransform(m_hMemDC, &xf);

	Graphics g(m_hMemDC);
	g.FillRectangle(&SolidBrush(Color::Red), (int)m_vEnemy.x - 15, (int)m_vEnemy.y - 20, 30, 20);
	g.FillEllipse(&SolidBrush(Color::Red), (int)m_vBullet.x - 5, (int)m_vBullet.y - 5, 10, 10);


	for (int i = 0; i < E_BTN_COUNT; i++)
	{
		m_aButton[i]->Render(m_hMemDC);
	}
	
	string s = to_string(m_vAcc.x);
	TextOut(m_hMemDC, 90, 20, s.c_str(), s.length());

	s = to_string(m_fInterval);
	TextOut(m_hMemDC, 90, 60, s.c_str(), s.length());
	/*
	Graphics g(m_hMemDC);
	Pen p(&SolidBrush(Color::Red));

	for (auto p : m_vecNode)
	{
		p->Render(m_hMemDC);
	}
	*/
	//TextOut(m_hMemDC, 10, 10, m_sColor.c_str(), m_sColor.length());
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
	for (int i = 0; i < E_BTN_COUNT; i++)
	{
		bool isProc = m_aButton[i]->WndProc(hWnd, message, wParam, lParam);
		if (isProc) return;
	}

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		/*
		RECT rc;
		rc.left = LOWORD(lParam);
		rc.top = HIWORD(lParam);
		rc.right = rc.left + 100;
		rc.bottom = rc.top + 100;

		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		m_pFront->SetColor(pt, 40, RGB(255, 0, 255));
		*/

		m_vBullet = m_vEnemy;
		m_fPassedTime = 0.0f;
		
		cVector2 vS = m_vTank - m_vEnemy;
		m_vVel = vS / m_fInterval - m_vAcc * m_fInterval / 2;
	}
	break;
	case WM_MOUSEMOVE:
	{
		/*
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		COLORREF c = m_pImage->GetColor(pt);
		string r = to_string(GetRValue(c));
		string g = to_string(GetGValue(c));
		string b = to_string(GetBValue(c));
		m_sColor = r + ", " + g + ", " + b;
		*/
	}
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

void cMainGame::OnClick(cButton * pSender)
{
	if (pSender == NULL) return;
	switch (pSender->GetTag())
	{
	case E_BTN_WIND_DEC:
	{
		m_vAcc.x -= WIND_DELTA;
	}
	break;
	case E_BTN_WIND_INC:
	{
		m_vAcc.x += WIND_DELTA;
	}
	break;
	case E_BTN_TIME_DEC:
	{
		m_fInterval -= TIME_DELTA;
	}
	break;
	case E_BTN_TIME_INC:
	{
		m_fInterval += TIME_DELTA;
	}
	break;
	default:
		break;
	}
}
