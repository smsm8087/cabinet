#pragma once

class cMainGame
{
private:
	HDC					m_hMemDC;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hOldBitmap;
	ULONG_PTR			m_ulGdiplusToken;
	vector<cVector3>	m_vecVertex;
	vector<DWORD>		m_vecIndex;
	//cMatrix				 m;
	vector<cVector3>	m_vecAfterVerTex;

	cVector3			m_vEye;

private:

	float				m_fAngle;
	float				m_fPlaneAngle;
	float				m_eyeCamera;
	float				m_fSee;
	float				m_eyecameraAngle;
	float				m_eyecameraAngleSujik;

	float				m_fCameraAngleX;
	float				m_fCameraAngleY;
	//mouse select
	bool				m_isLeftRotation;
	bool				m_isRightRotation;
	bool				m_isMousemoveright;
	bool				m_isMousemoveleft;

	POINT				Mousept;

	cVector3			m_vPlaneRowRight[11];
	cVector3			m_vPlaneColUp[11];
	cVector3			m_vPlaneRowLeft[11];
	cVector3			m_vPlaneColDown[11];
	cVector3			m_vCubePosition;
	cVector3			mDir;
	cVector3			m_vLook;
	cVector3			tempeye;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

