#pragma once

class cImage;
class cSpriteSheetAnimation;
class cLoading;
class cMainFightImage;
class cMainPlay;
class cLobby;
class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;
	
	//sound
	FMOD_SYSTEM*	m_pSystem;
	FMOD_BOOL       isplay;
	vector<FMOD_SOUND*>		m_vecSound;
	vector<FMOD_CHANNEL*>	m_vecChannel;
	MAINSTATUS	   e_mainstatus;
	//2.MAINLOADING
	cLobby*		   m_pLobby;
	//3.MAINFIGHT
	cMainPlay*		 m_pMainPlay;
	bool			 m_isGamePause;
	cImage*			 m_pMouse;
	cImage*			 m_pStart;
	float			 m_fStarttime;
	bool			 m_isstart;

	RECT rcTempplayer;

	RECT		rcMap;
	cImage*		m_pBackImage;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
};

