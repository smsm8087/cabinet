#include "stdafx.h"
#include "cInventory.h"


cInventory::cInventory(const char * imageName)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_nWidth(0)
	, m_nHeight(0)
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


cInventory::~cInventory()
{
	DeleteObject(SelectObject(m_hMemDC, m_hBitmap));
	DeleteDC(m_hMemDC);
}

void cInventory::Render(HDC hdc)
{
	TransparentBlt(hdc, 453, 0, m_nWidth, m_nHeight, m_hMemDC, 0, 0, 169, 493, RGB(255, 0, 255));
}
