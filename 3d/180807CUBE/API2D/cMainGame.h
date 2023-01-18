#pragma once
#include"cMatrix.h"
#include"cVector3.h"
class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;

private:
	vector<cVector3> m_vecDot;
	vector<int>		 m_vecNum;
	cMatrix*			 m_Mat;
	float			mfAngle;
	float			fcamerax;
	float			fcameray;
	float			fcameraz;

	cMatrix					m_matWorld;
	cMatrix					m_matView;
	cMatrix					m_matProj;
	cMatrix					m_matViewport;

	cVector3				m_vEye;
	cVector3				m_vLookAt;
	cVector3				m_vUp;
	cVector3				m_vPosition;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

