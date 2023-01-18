#include "stdafx.h"
#include "cCharater.h"


cCharater::cCharater(const char * imageName)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_nWidth(0)
	, m_nHeight(0)
	,idir(moveidleright)
{
	if (!g_hWnd) return;

	HDC hdc = GetDC(g_hWnd);

	if (!hdc) return;

	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitmap = (HBITMAP)LoadImage(NULL, imageName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	BITMAP bm;

	GetObject(m_hBitmap, sizeof(BITMAP), &bm);
	m_nWidth = bm.bmWidth;
	m_nHeight = bm.bmHeight;
}


cCharater::~cCharater()
{
	DeleteObject(SelectObject(m_hMemDC, m_hBitmap));
	DeleteDC(m_hMemDC);
}

//void cCharater::Update()
//{
//}

void cCharater::Render(HDC hdc,int x, int y, int radius)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_iPastTime += g_pTimeManager->GetElapsedTime();
	if (m_iPastTime > m_iIdleTime)
	{
		act++;
		m_iPastTime = 0;
		
	}
	act %= 4;
	//왼쪽무빙
	if (idir == moveleft)
	{
		switch (act)
		{
		case 0:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 3, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		case 1:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 2, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		case 2:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 1, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		case 3:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 0, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		default:
			break;
		}

	}
	//오른쪽 무빙
	if (idir == moveright)
	{
		switch (act)
		{
		case 0:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 4, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		case 1:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 5, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		case 2:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 6, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		case 3:
		{
			TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 7, 0, 29, 37, RGB(255, 0, 255));
		}
		break;
		default:
			break;
		}
	}
	//아무것도하지않는 상태
	if (idir == moveidleright)
	{
		TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 4, 0, 29, 37, RGB(255, 0, 255));
	}
	if (idir == moveidleleft)
	{
		TransparentBlt(hdc, x, y, radius, radius, m_hMemDC, 29 * 3, 0, 29, 37, RGB(255, 0, 255));
	}

}

void cCharater::Rendermap(HDC hdc, int left, int top)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	TransparentBlt(hdc, left, top, rc.right, 400, m_hMemDC, 0, 0, 778,344,RGB(255, 0, 255));
}

void cCharater::Rendermap2(HDC hdc, int left, int top,int right,int bottom)
{

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	TransparentBlt(hdc, left, top, right, bottom, m_hMemDC, 0, 0, 551, 90, RGB(255, 0, 255));
}

