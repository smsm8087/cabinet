#pragma once
class cCharater
{
private:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

	float m_iPastTime;	//지나간 시간
	float m_iIdleTime;	//대기시간
	int   act;			//시간 나누기프레임
	
public:
	cCharater(const char * imageName);
	~cCharater();
	int idir;
	void Render(HDC hdc, int x, int y, int radius);
	void Rendermap(HDC hdc, int left, int top);
	void Rendermap2(HDC hdc, int left, int top, int right, int bottom);
};

