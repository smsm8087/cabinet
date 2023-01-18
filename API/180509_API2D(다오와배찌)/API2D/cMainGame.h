#pragma once

class cAirplane;
class WormPlayer;
class Food;
class ConvexHull;

class cMainGame
{
private:
	HWND				mhWnd;
	HDC					m_hMemDC;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hOldBitmap;
	WormPlayer*			mPlayer;
	Food*				mFood;
	ConvexHull*			mConvexHull;

	bool				mbGameOver;
	float				m_fPassedIdleTime;
	float				m_fIdleTime;
	//cAirplane*			m_pPlayer;	//플레이어
	//vector<cAirplane*>	m_vecEnemy;

public:
	cMainGame();
	~cMainGame();

	void Init(HWND hwnd);
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Release();

	void InitStage(int nStage);
	void ClearEnemy();
	bool CheckCollision(cAirplane* pAirplane);
	bool CheckCollision(cAirplane* pAirplane1, cAirplane* pAirplane2);
};

