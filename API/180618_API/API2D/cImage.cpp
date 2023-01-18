#include "stdafx.h"
#include "cImage.h"

map<string, cImage*> cImage::m_mapImage;

cImage::cImage(const char* szPath)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_stSize(0, 0)
	, m_dwTransparentColor(RGB(255, 0, 255))
	, m_sPath(szPath)
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

cImage::cImage(Bitmap * pBitmap)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_stSize(0, 0)
	, m_dwTransparentColor(RGB(255, 0, 255))
	, m_sPath("")
{
	if (!g_hWnd) return;

	HDC hdc = GetDC(g_hWnd);

	if (!hdc) return;

	m_hMemDC = CreateCompatibleDC(hdc);
	if (pBitmap)
		pBitmap->GetHBITMAP(Color::Black, &m_hBitmap);
	//m_hBitmap = (HBITMAP)LoadImage(NULL, szPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

cImage * cImage::Create(const char * szPath)
{
	if (m_mapImage.find(szPath) == m_mapImage.end())
	{
		m_mapImage[szPath] = new cImage(szPath);
	}
	return m_mapImage[szPath];
}

void cImage::Destroy()
{
	for (auto it : m_mapImage)
	{
		SAFE_RELEASE(it.second);
	}
}

void cImage::Render(HDC hdc, const POINT & ptDst, bool isTransparent)
{
	if (isTransparent)
	{
		
		byte alpha = 255;
		BLENDFUNCTION bf = { AC_SRC_OVER,0,alpha,AC_SRC_ALPHA };
		AlphaBlend(hdc, 0, 0, 
			m_stSize.nWidth, m_stSize.nHeight,
			m_hMemDC, 0, 0, m_stSize.nWidth, m_stSize.nHeight, bf);
		/*
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
			*/
			
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
	for (size_t i = rc.top; i <= rc.bottom; i++)
	{
		for (size_t j = rc.left; j <= rc.right; j++)
		{
			SetPixel(m_hMemDC, j, i, c);
		}
	}
}

void cImage::SetColor(POINT pt, float fRadius, COLORREF c)
{
	RECT rc;
	SetRect(&rc,
		pt.x - fRadius,
		pt.y - fRadius,
		pt.x + fRadius,
		pt.y + fRadius);
	for (int i = rc.top; i <= rc.bottom; i++)
	{
		for (int j = rc.left; j <= rc.right; j++)
		{
			float dx = pt.x - j;
			float dy = pt.y - i;
			
			if (dx * dx + dy * dy <= fRadius * fRadius)
			{
				SetPixel(m_hMemDC, j, i, c);
			}
		}
	}
}

COLORREF cImage::GetColor(POINT & pt)
{
	return GetPixel(m_hMemDC, pt.x, pt.y);
}

int cImage::PointAt(int x, COLORREF dwTransparent)
{
	for (size_t i = 0; i < m_stSize.nHeight; i++)
	{
		COLORREF c = GetPixel(m_hMemDC, x, i);
		if (c != dwTransparent) return i;
	}
	return m_stSize.nHeight;
}

