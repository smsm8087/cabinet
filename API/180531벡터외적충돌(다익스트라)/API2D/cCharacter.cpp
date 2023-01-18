#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter(const char * imageName)
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


cCharacter::~cCharacter()
{
	DeleteObject(SelectObject(m_hMemDC, m_hBitmap));
	DeleteDC(m_hMemDC);
}

void cCharacter::Render(HDC hdc, int x, int y, int radius)
{/*
 RECT rc;
 GetClientRect(g_hWnd, &rc);
 m_iPastTime += g_pTimeManager->GetElapsedTime();
 if (m_iPastTime > m_iIdleTime)
 {
 act++;
 m_iPastTime = 0;

 }
 act %= 4;*/
}

void cCharacter::Rendermap(HDC hdc, int left, int top, int right, int bottom)
{
	TransparentBlt(hdc, left, top, right, bottom, m_hMemDC, 0, 0, 433, 364, RGB(255, 255, 255));
}
