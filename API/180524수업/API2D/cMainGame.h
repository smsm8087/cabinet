#pragma once

class cCrt;
class cAirplane;
class cEnemy;
class cBulletManager;
class cMainGame
{
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;
	cAirplane*  m_pPlayer;
	cAirplane*	m_pEnemy;
	cBulletManager* m_Bullet;
	/*cCrt*		m_pCrt;*/
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

