#pragma once


class cTile;

class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;

	vector<cTile*>	m_vecTile;
	bool			m_isLShift;

	class cImage*	m_pImage;

	cVector2		m_vPlayer;
	cVector2		m_vBullet[3];
	cVector2		m_vBulletVel[3];
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

