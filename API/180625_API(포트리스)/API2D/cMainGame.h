#pragma once
#include "cButton.h"

class cImage;

class cMainGame : public iButtonDelegate
{
private:
	enum
	{
		E_BTN_WIND_INC,
		E_BTN_WIND_DEC,
		E_BTN_TIME_INC,
		E_BTN_TIME_DEC,
		E_BTN_COUNT
	};
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;

	cImage*			m_pBack;
	cImage*			m_pFront;
	
	cVector2		m_vTank;
	cVector2		m_vEnemy;
	cVector2		m_vBullet;
	cVector2		m_vAcc;
	cVector2		m_vVel;

	float			m_fTankAngle;
	float			m_fPassedTime;
	float			m_fInterval;
	
	cButton*		m_aButton[E_BTN_COUNT];

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// iButtonDelegate override
	virtual void OnClick(cButton* pSender) override;
};

