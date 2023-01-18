#pragma once


class cAirplane;
class cImage;
class cMainGame
{
private:
	HDC					m_hMemDC;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hOldBitmap;
	cAirplane*			m_pPlayer;
	vector<cAirplane*>	m_vecEnemy;
	ULONG_PTR	m_ulGdiplusToken;
	
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void InitStage(int nStage);
	void ClearEnemy();
	bool CheckCollision(cAirplane* pAirplane);
	bool CheckCollision(cAirplane* pAirplane1, cAirplane* pAirplane2);
};

