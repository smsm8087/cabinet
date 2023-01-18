#include "stdafx.h"
#include "cImage.h"

cImage::cImage(const char* szPath)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_nWidth(0)
	, m_nHeight(0)
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
	m_nWidth = bm.bmWidth;
	m_nHeight = bm.bmHeight;
}

cImage::~cImage()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cImage::Render(HDC hdc, RECT rcDst, POINT ptSrc)
{
	BitBlt(hdc,
		rcDst.left, rcDst.top,
		rcDst.right - rcDst.left, rcDst.bottom - rcDst.top,
		m_hMemDC,
		ptSrc.x, ptSrc.y,
		SRCCOPY);
}

void cImage::TransparentRender(HDC hdc, RECT rcDst, RECT rcSrc)
{
	TransparentBlt(hdc,
		rcDst.left, rcDst.top,
		rcDst.right - rcDst.left, rcDst.bottom - rcDst.top,
		m_hMemDC,
		rcSrc.left, rcSrc.top,
		rcSrc.right - rcSrc.left, rcSrc.bottom - rcSrc.top,
		m_dwTransparentColor);
}


