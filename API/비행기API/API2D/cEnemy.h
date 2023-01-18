#pragma once
#include "cAirplane.h"

enum eState
{
	E_IDLE,
	E_ROTATE,
};

class cEnemy : public cAirplane
{
protected:
	eState m_eState;
	float m_fIdleTime;
	float m_fPassedIdleTime;
	float m_fAmount;
	float m_fAccAmount;
	float m_fTargetAngle;
	cImage*		i_player;
	ULONG_PTR	m_ulGdiplusToken;
public:
	cEnemy();
	virtual ~cEnemy();
	
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

