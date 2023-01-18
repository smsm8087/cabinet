#pragma once
class cImage
{
protected:
	HDC		m_hMemDC;
	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBitmap;
	
	GETSET(ST_SIZE, m_stSize, stSize);
	GETSET(COLORREF, m_dwTransparentColor, TransparentColor);
	GETSET(int, alpha, alphanum);
	BLENDFUNCTION bf;

	RECT		m_Rect;
	POINT		m_Pos;
public:
	cImage(const char* szPath);
	~cImage();
	bool	m_isclicked;
	bool	 isdrawing;
	void Render(HDC hdc, RECT rcDst, POINT ptSrc);
	void TransparentRender(HDC hdc, RECT rcDst, RECT rcSrc);
	void Render(HDC hdc, RECT rc, bool isTransparent = false);
	void RenderCameramap(HDC hdc, POINT front, POINT end);
	void RenderCharater(HDC hdc, RECT rc, bool isTransparent = false);
	void Render(HDC hdc, const POINT& ptDst, bool isTransparent = false);
	void RenderCharaterFade(HDC hdc, RECT rc, bool isTransparent = false);
	void Fadein();
	void FadeOut();
	void SetColor(RECT& rc, COLORREF c);
	void SetColor(POINT pt, float fRadius, COLORREF c);
	COLORREF GetColor(POINT& pt);
	int PointAt(int x, COLORREF dwTransparent);

	void Draw(HDC hdc, int destX, int destY,
		int width, int height, int srcX, int srcY);
};

