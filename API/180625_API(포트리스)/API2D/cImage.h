#pragma once
class cImage
{
protected:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	ST_SIZE m_stSize;
	
	GETSET(COLORREF, m_dwTransparentColor, TransparentColor);

public:
	cImage(const char* szPath);
	~cImage();

	void Render(HDC hdc, const POINT& ptDst, bool isTransparent = false);
	void SetColor(RECT& rc, COLORREF c);
	void SetColor(POINT pt, float fRadius, COLORREF c);
	COLORREF GetColor(POINT& pt);
	int PointAt(int x, COLORREF dwTransparent);
};

