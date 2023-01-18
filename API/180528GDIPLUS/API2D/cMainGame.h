#pragma once

class cCrt;
class cAirplane;


class cMainGame
{
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;

	cCrt*		m_pCrt;
	cAirplane*	m_pAirplane;

	char		m_szCommand[16];
	char		m_szCopyCommand[16];
	float		m_fLastCommandTime;
	int			m_nCommandCount;
	ULONG_PTR	m_ulGdiplusToken;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

