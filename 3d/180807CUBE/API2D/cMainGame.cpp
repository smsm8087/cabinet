#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	, mfAngle(0.0f)
{
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}

cMainGame::~cMainGame()
{
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
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_vecDot.push_back(cVector3(-1.0f, -1.0f, -1.0f));
	m_vecDot.push_back(cVector3(-1.0f, 1.0f, -1.0f));
	m_vecDot.push_back(cVector3(1.0f, 1.0f, -1.0f));
	m_vecDot.push_back(cVector3(1.0f, -1.0f, -1.0f));
	m_vecDot.push_back(cVector3(-1.0f, -1.0f, 1.0f));
	m_vecDot.push_back(cVector3(-1.0f, 1.0f, 1.0f));
	m_vecDot.push_back(cVector3(1.0f, 1.0f, 1.0f));
	m_vecDot.push_back(cVector3(1.0f, -1.0f, 1.0f));

	m_vecNum.push_back(0);
	m_vecNum.push_back(1);
	m_vecNum.push_back(2);

	m_vecNum.push_back(0);
	m_vecNum.push_back(2);
	m_vecNum.push_back(3);

	m_vecNum.push_back(4);
	m_vecNum.push_back(6);
	m_vecNum.push_back(5);

	m_vecNum.push_back(4);
	m_vecNum.push_back(7);
	m_vecNum.push_back(6);

	m_vecNum.push_back(4);
	m_vecNum.push_back(5);
	m_vecNum.push_back(1);

	m_vecNum.push_back(4);
	m_vecNum.push_back(1);
	m_vecNum.push_back(0);

	m_vecNum.push_back(3);
	m_vecNum.push_back(2);
	m_vecNum.push_back(6);

	m_vecNum.push_back(3);
	m_vecNum.push_back(6);
	m_vecNum.push_back(7);

	m_vecNum.push_back(1);
	m_vecNum.push_back(5);
	m_vecNum.push_back(6);

	m_vecNum.push_back(1);
	m_vecNum.push_back(6);
	m_vecNum.push_back(2);

	m_vecNum.push_back(4);
	m_vecNum.push_back(0);
	m_vecNum.push_back(3);

	m_vecNum.push_back(4);
	m_vecNum.push_back(3);
	m_vecNum.push_back(7);

	//월드, 뷰, 프로젝션 셋팅
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
	fcamerax = 0;
	fcameray = 0;
	fcameraz = -5;

}


void cMainGame::Update()
{
	g_pTimeManager->Update();

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//mfAngle += g_pTimeManager->GetElapsedTime();
	/*m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition;*/
	m_vEye = cVector3(fcamerax, fcameray, fcameraz);

	cMatrix matRX = cMatrix::RotationY(mfAngle);
	cMatrix matR = matRX;
	cMatrix matT = cMatrix::Translation(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
	m_matView = cMatrix::LookAtLH(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::PerspectiveFovLH(PI / 4.0f,
		rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
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

	FillRect(m_hMemDC, &rc, GetSysColorBrush(/*COLOR_GRAYTEXT*/COLOR_WINDOW));

	cMatrix matWVP = m_matWorld * m_matView * m_matProj * m_matViewport;

	for (size_t i = 0; i < m_vecNum.size(); i += 3)
	{
		cVector3 v1 = m_vecDot[m_vecNum[i]];
		cVector3 v2 = m_vecDot[m_vecNum[i + 1]];
		cVector3 v3 = m_vecDot[m_vecNum[i + 2]];

		v1 = v1 * matWVP;
		v2 = v2 * matWVP;
		v3 = v3 * matWVP;

		MoveToEx(m_hMemDC, v1.x, v1.y, NULL);
		LineTo(m_hMemDC, v2.x, v2.y);
		LineTo(m_hMemDC, v3.x, v3.y);
		LineTo(m_hMemDC, v1.x, v1.y);
	}
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
		switch (wParam)
		{
		case 'D':
		{
			mfAngle += 0.01f;
		}break;
		case 'A':
		{
			mfAngle -= 0.01f;

		}break;
		case 'W':
		{
			fcameray += 0.1f;
		}break;
		case 'S':
		{
			fcameray-= 0.1f;
		}break;
		default:
			break;
		}
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


