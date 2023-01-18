#pragma once
class cMapImage
{
protected:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

public:
	cMapImage(const char * imageName);
	~cMapImage();

	void Render(HDC hdc);
};

