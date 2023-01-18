#pragma once
#include "cAirplane.h"

class cPlayer : public cAirplane
{
protected:
	cImage * i_player;
	float m_fTargetAngle;
	float m_fAmount;
	float m_fAccAmount;
	ULONG_PTR	m_ulGdiplusToken;
public:
	cPlayer();
	~cPlayer();
	
	virtual void Render(HDC hdc) override;
	virtual void Update() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

