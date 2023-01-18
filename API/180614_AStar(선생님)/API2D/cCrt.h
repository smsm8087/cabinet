#pragma once

#include "iAnimation.h"
#include "cJumpUpState.h"
#include "cJumpDownState.h"
#include "cLandingState.h"

class iCrtState;

class cCrt
{
	friend class cJumpUpState;
	friend class cJumpDownState;
	friend class cLandingState;

protected:
	map<string, iAnimation*>	m_mapAnimation;
	string						m_sAnimName;
	cVector2					m_vPos;
	ST_SIZE						m_stSize;
	cVector2					m_vVel;
	cVector2					m_vAcc;
	float						m_fGroundY;
	iCrtState*					m_pState;

public:
	cCrt(const RECT& rcDst);
	virtual ~cCrt();

	void Update(const RECT& rcBox);
	void Render(HDC hdc);
	RECT GetDestRect();
};

