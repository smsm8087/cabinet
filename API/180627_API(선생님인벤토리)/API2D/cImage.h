#pragma once

class cImage : public cObject
{
protected:
	static map<string, cImage*> m_mapImage;

	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	string	m_sPath;

	GET(ST_SIZE, m_stSize, Size);
	GETSET(COLORREF, m_dwTransparentColor, TransparentColor);

private:
	cImage(const char* szPath);

public:
	~cImage();

	static cImage* Create(const char* szPath);
	static void Destroy();
	void Render(HDC hdc, const POINT& ptDst, bool isTransparent = false);
	void SetColor(RECT& rc, COLORREF c);
	void SetColor(POINT pt, float fRadius, COLORREF c);
	COLORREF GetColor(POINT& pt);
	int PointAt(int x, COLORREF dwTransparent);
};

