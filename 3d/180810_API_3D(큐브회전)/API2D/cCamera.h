#pragma once
class cCamera
{
	cVector3	m_vEye;
	cVector3	m_vLookAt;
	cVector3	m_vUp;
	cVector3*	m_pvTarget;

	bool		m_isLButtonDown;
	POINT		m_ptPrevMouse;
	float		m_fAngleY;
	float		m_fAngleX;
	float		m_fDist;

public:
	cCamera();
	~cCamera();

	void SetTarget(cVector3* pvTarget);
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

