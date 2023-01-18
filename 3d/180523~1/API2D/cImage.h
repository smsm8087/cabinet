#pragma once
class cImage
{
protected:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;
	map<string, vector<RECT>> m_mapAnimation;

	GETSET(COLORREF, m_dwTransparentColor, TransparentColor);

public:
	cImage(const char* szPath);
	~cImage();

	void Render(HDC hdc, RECT rcDst, POINT ptSrc);
	void TransparentRender(HDC hdc, RECT rcDst, RECT rcSrc);
};

