#pragma once
class cImage
{
protected:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	GETSET(COLORREF, m_dwTransparentColor, TransparentColor);
	GETSET(ST_SIZE, m_stSize, stsize);

public:
	cImage(const char* szPath);
	~cImage();

	void Render(HDC hdc, POINT ptDst, bool isTransparent = false);
	void SetColor(RECT& rc, COLORREF c);
	COLORREF GetColor(POINT& pt);
	
};

