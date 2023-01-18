#pragma once

class cCrt;

class cMainGame
{
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;

	cCrt*		m_pCrt;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

