#include "stdafx.h"
#include "cImage.h"

void cImage::RenderNormal(HDC hdc, const POINT & ptDst, const POINT & ptSrc, bool isTransparent)
{
	if (isTransparent)
	{
		TransparentBlt(hdc,
			ptDst.x - m_stRenderSize.nWidth * m_vPivotPoint.x,
			ptDst.y - m_stRenderSize.nHeight * m_vPivotPoint.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			m_hMemDC,
			ptSrc.x, ptSrc.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			m_dwTransparentColor);
	}
	else
	{
		BitBlt(hdc,
			ptDst.x - m_stRenderSize.nWidth * m_vPivotPoint.x,
			ptDst.y - m_stRenderSize.nHeight * m_vPivotPoint.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			m_hMemDC,
			ptSrc.x, ptSrc.y,
			SRCCOPY);
	}
}

void cImage::RenderRotate(HDC hdc, const POINT & ptDst, const POINT & ptSrc, bool isTransparent)
{
	float fCos = (float)cos(m_fAngle - m_fDefaultAngle);
	float fSin = (float)sin(m_fAngle - m_fDefaultAngle);

	XFORM xf;
	xf.eM11 = fCos;
	xf.eM12 = fSin;
	xf.eM21 = -fSin;
	xf.eM22 = fCos;
	xf.eDx = (FLOAT)ptDst.x;
	xf.eDy = (FLOAT)ptDst.y;

	SetWorldTransform(hdc, &xf);

	if (isTransparent)
	{
		BLENDFUNCTION bf;
		bf.BlendOp = 0;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 100; // 0~255
		bf.AlphaFormat = AC_SRC_OVER;
		
		GdiAlphaBlend(hdc,
			-m_stRenderSize.nWidth * m_vPivotPoint.x,
			-m_stRenderSize.nHeight * m_vPivotPoint.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight, 
			m_hMemDC,
			ptSrc.x, ptSrc.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			bf);
		/*
		TransparentBlt(hdc,
			-m_stRenderSize.nWidth * m_vPivotPoint.x,
			-m_stRenderSize.nHeight * m_vPivotPoint.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			m_hMemDC,
			ptSrc.x, ptSrc.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			m_dwTransparentColor);
			*/
	}
	else
	{
		BitBlt(hdc,
			-m_stRenderSize.nWidth * m_vPivotPoint.x,
			-m_stRenderSize.nHeight * m_vPivotPoint.y,
			m_stRenderSize.nWidth,
			m_stRenderSize.nHeight,
			m_hMemDC,
			ptSrc.x, ptSrc.y,
			SRCCOPY);
	}

	xf.eM11 = 1;
	xf.eM12 = 0;
	xf.eM21 = 0;
	xf.eM22 = 1;
	xf.eDx = (FLOAT)0;
	xf.eDy = (FLOAT)0;
	SetWorldTransform(hdc, &xf);
}

cImage::cImage(const char* szPath)
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_stSize(0, 0)
	, m_dwTransparentColor(RGB(255, 0, 255))
	, m_fAngle(0.0f)
	, m_fDefaultAngle(0.0f)
	, m_vPivotPoint(0.5f, 0.5f)
	, m_stRenderSize(0.0f, 0.0f)
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

	m_stRenderSize.nWidth = bm.bmWidth;
	m_stRenderSize.nHeight = bm.bmHeight;
}

cImage::~cImage()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cImage::Render(HDC hdc, const POINT & ptDst, bool isTransparent)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	Render(hdc, ptDst, pt, isTransparent);
}

void cImage::Render(HDC hdc, const POINT& ptDst, const POINT& ptSrc, bool isTransparent)
{
	if (m_fAngle != 0.0f)
	{
		RenderRotate(hdc, ptDst, ptSrc, isTransparent);
	}
	else
	{
		RenderNormal(hdc, ptDst, ptSrc, isTransparent);
	}
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

