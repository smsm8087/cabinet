#include "stdafx.h"
#include "cImage.h"

cImage::cImage(const char* szPath)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_stSize(0, 0)
	, m_dwTransparentColor(RGB(255, 0, 255))
{	
	if (!g_hWnd) return;

	HDC hdc = GetDC(g_hWnd);

	if (!hdc) return;
	
	m_hMemDC = CreateCompatibleDC(hdc);
	m_hBitmap = (HBITMAP)LoadImage(NULL, szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	BITMAP bm;
	GetObject(m_hBitmap, sizeof(BITMAP), &bm);
	m_stSize.nWidth = bm.bmWidth;
	m_stSize.nHeight = bm.bmHeight;
}

cImage::~cImage()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cImage::Render(HDC hdc, POINT ptDst, bool isTransparent)
{
	if (isTransparent)
	{
		TransparentBlt(hdc,
			ptDst.x,
			ptDst.y,
			m_stSize.nWidth,
			m_stSize.nHeight,
			m_hMemDC,
			0, 0,
			m_stSize.nWidth,
			m_stSize.nHeight,
			m_dwTransparentColor);
	}
	else
	{
		BitBlt(hdc,
			ptDst.x,
			ptDst.y,
			m_stSize.nWidth,
			m_stSize.nHeight,
			m_hMemDC,
			0, 0,
			SRCCOPY);
	}
}



void cImage::SetColor(RECT & rc, COLORREF c)
{
	/*for (size_t i = rc.top; i <= rc.bottom; i++)
	{
		for (size_t j = rc.left; j <= rc.right; j++)
		{
			SetPixel(m_hMemDC, j, i, c);
		}
	}*/
	//int a = 0;
	//int r = (rc.bottom - rc.top) / 2;
	//for (size_t i = 0; i < r*2; i++)
	//{
	//	for (size_t j = 0; j < r*2; j++)
	//	{
	//		(r*r > (i + 0.5 - r)*(i + 0.5 - r) + (j + 0.5 - r)*(j + 0.5 - r))
	//			? SetPixel(m_hMemDC, j, i, c) : a = 1;
	//	}

	//}
	HPEN pen, oldpen;
	pen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
	oldpen = (HPEN)SelectObject(m_hMemDC, pen);
	HBRUSH hbrush, oldbrush;
	hbrush = CreateSolidBrush(RGB(255, 255, 255));
	oldbrush =(HBRUSH)SelectObject(m_hMemDC, hbrush);
	int ry = (rc.bottom - rc.top)/2;
	int rx = (rc.right - rc.left)/2;
	Ellipse(m_hMemDC, rc.left-rx, rc.top-ry, rc.right+rx, rc.bottom+ry);
	SelectObject(m_hMemDC, oldpen);
	SelectObject(m_hMemDC, oldbrush);
	DeleteObject(hbrush);
	DeleteObject(oldpen);
}

COLORREF cImage::GetColor(POINT & pt)
{
	return GetPixel(m_hMemDC, pt.x, pt.y);
}

