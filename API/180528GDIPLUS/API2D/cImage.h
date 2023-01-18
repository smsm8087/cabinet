#pragma once
class cImage
{
protected:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	ST_SIZE m_stSize;
	
	map<string, vector<RECT>> m_mapAnimation;
	
	GETSET(COLORREF, m_dwTransparentColor, TransparentColor);
	GETSET(float, m_fAngle, Angle);
	GETSET(float, m_fDefaultAngle, DefaultAngle);
	GETSET(cVector2, m_vPivotPoint, PivotPoint);
	GETSET(ST_SIZE, m_stRenderSize, RenderSize);

private:
	void RenderNormal(HDC hdc, const POINT& ptDst, const POINT& ptSrc, bool isTransparent = false);
	void RenderRotate(HDC hdc, const POINT& ptDst, const POINT& ptSrc, bool isTransparent = false);

public:
	cImage(const char* szPath);
	~cImage();

	void Render(HDC hdc, const POINT& ptDst, bool isTransparent = false);
	void Render(HDC hdc, const POINT& ptDst, const POINT& ptSrc, bool isTransparent = false);
	void Render(HDC hdc, RECT rcDst, POINT ptSrc);
	void TransparentRender(HDC hdc, RECT rcDst, RECT rcSrc);
};

