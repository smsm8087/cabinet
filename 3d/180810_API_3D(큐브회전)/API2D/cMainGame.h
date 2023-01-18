#pragma once

class cMainGame
{
private:
	HDC					m_hMemDC;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hOldBitmap;
	ULONG_PTR			m_ulGdiplusToken;
	class cCube*		m_pCube;
	class cGrid*		m_pGrid;
	class cCamera*		m_pCamera;

private:

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

