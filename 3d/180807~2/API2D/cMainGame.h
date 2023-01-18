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

	cVector3				m_vEye;
	cVector3				m_vLookAt;
	cVector3				m_vUp;
	cVector3				m_vPosition;

	vector<cVector3> m_vVertex;
	vector<int> m_vVertexIndex;

	cMatrix					m_matWorld;
	cMatrix					m_matView;
	cMatrix					m_matProj;
	cMatrix					m_matViewport;

	float	mfAngle;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

