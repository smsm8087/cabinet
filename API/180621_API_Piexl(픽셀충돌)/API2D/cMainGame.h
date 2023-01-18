#pragma once

class cImage;

class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;

	cImage*			m_pImage;
	cImage*			m_pTank;
	string			m_sColor;
	POINT			m_ptPixelleft;
	POINT			m_ptPixelRight;
	POINT			ptTank;
	POINT			ptUP;
	POINT			ptDown;
	COLORREF		m_cPixelleft;
	COLORREF		m_cPixelRight;
	string          r_left;
	string          g_left;
	string          b_left;
	string          r_right;
	string          g_right;
	string          b_right;

	string			m_sColorleft;
	string			m_sColorright;
	string			transparent;

	float			m_fSeta;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

