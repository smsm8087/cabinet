#include "stdafx.h"
#include "cCharacterImage.h"


cCharacterImage::cCharacterImage(const char * imageName)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_nWidth(0)
	, m_nHeight(0)
	, x(277)
	, y(350)
	, m_iPastTime(0.0f)
	, m_iIdleTime(0.1f)
	, IsMove(false)
	, m_MapNum(0)
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


cCharacterImage::~cCharacterImage()
{
	DeleteObject(SelectObject(m_hMemDC, m_hBitmap));
	DeleteDC(m_hMemDC);
}

void cCharacterImage::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_iPastTime += g_pTimeManager->GetElapsedTime();
	if (m_iPastTime > m_iIdleTime &&IsMove == true)
	{
		iact++;
		m_iPastTime = 0;
		IsMove = false;
	}
	iact %= 3;
	
	int MovePoint = 43;
	if (idir == DIR_UP)
	{
		switch (iact)
		{
		case 0:
			TransparentBlt(hdc,x, y, 40, 40, m_hMemDC,FrameXPoint(0) , 0, 43, 56, RGB(255, 0, 255));  //상단 1번 그림
			break;
		case 1:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(2), 0, 43, 56, RGB(255, 0, 255)); //상단 3번 그림
			break;
		case 2:			//x,y,40,40 이 레프트탑라이트 바텀	
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(1), 0, 43, 56, RGB(255, 0, 255)); //상단 2번 그림(가만히있음)
			break;
		default:
			break;
		}
	}
	else if (idir == DIR_DOWN)
	{
		switch (iact)
		{
		case 0:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(4), 0, 43, 56, RGB(255, 0, 255));  //상단 1번 그림
			break;
		case 1:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(3), 0, 43, 56, RGB(255, 0, 255)); //상단 3번 그림
			break;
		case 2:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(5), 0, 43, 56, RGB(255, 0, 255)); //상단 2번 그림(가만히있음)
			break;
		default:
			break;
		}

	}
	else if (idir == DIR_LEFT)
	{
		switch (iact)
		{
		case 0:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(4), 57, 43, 56, RGB(255, 0, 255));  //상단 1번 그림
			break;
		case 1:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(3), 57, 43, 56, RGB(255, 0, 255)); //상단 3번 그림
			break;
		case 2:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(5), 57, 43, 56, RGB(255, 0, 255)); //상단 2번 그림(가만히있음)
			break;
		default:
			break;
		}
	}
	else if (idir == DIR_RIGHT)
	{
		switch (iact)
		{
		case 0:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(0), 56, 43, 56, RGB(255, 0, 255));  //상단 1번 그림
			break;
		case 1:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(2), 56, 43, 56, RGB(255, 0, 255)); //상단 3번 그림
			break;
		case 2:
			TransparentBlt(hdc, x, y, 40, 40, m_hMemDC, FrameXPoint(1), 56, 43, 56, RGB(255, 0, 255)); //상단 2번 그림(가만히있음)
			break;
		default:
			break;
		}
	}
	
}

int cCharacterImage::FrameXPoint(int _num)
{
	int Num = 43;
	return Num = _num * Num;
}

