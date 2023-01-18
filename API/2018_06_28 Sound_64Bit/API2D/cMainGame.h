#pragma once

class cUIObject;

class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;

	cUIObject*		m_pUIRoot;

	System*			m_pSystem;
	Sound*			m_pSound;

	/*
	FMOD_SYSTEM*	m_pSystem;
	vector<FMOD_SOUND*>		m_vecSound;
	vector<FMOD_CHANNEL*>	m_vecChannel;
	*/

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

