#pragma once

#include "cBullet.h"
class cImage;
class cAirplane

{
protected:
	cVector2			m_vPos;
	cVector2			m_vDir;
	float				m_fRadius;
	
	float				m_fAngleSpeed;
	float				m_fSpeed;
	float				m_fCannonLen;
	COLORREF			m_dwColor;
	vector<cAirplane*>	m_vecTarget;
	cImage*				i_player;
	cImage*				i_enemy;
	int					x, y;
	ULONG_PTR	m_ulGdiplusToken;
public:
	cAirplane();
	virtual ~cAirplane();
	float				m_fAngle;

	virtual void Init(const cVector2& vPos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Fire(cAirplane* pTarget = NULL);
	virtual float GetFullRadius();
	virtual float GetBodyRadius();
	virtual cVector2 GetPosition();
	virtual void AddTarget(cAirplane* pTarget);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

