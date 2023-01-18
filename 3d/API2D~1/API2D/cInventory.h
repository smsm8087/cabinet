#pragma once
class cInventory
{
protected:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

public:
	cInventory(const char * imageName);
	~cInventory();

	void Render(HDC hdc);
};

