#include "stdafx.h"
#include "cEnemy.h"


cEnemy::cEnemy()
	: m_eState(E_IDLE)
	, m_fIdleTime(2.0f + (rand() % 200) / 100.f)
	, m_fPassedIdleTime(0.0f)
	, m_fAmount(0.0f)
	, m_fAccAmount(0.0f)
	, m_fTargetAngle(0.0f)
{
	m_dwColor = RGB(0, 0, 255);
}

cEnemy::~cEnemy()
{
}

void cEnemy::Update()
{
	if (m_eState == E_IDLE)
	{
		m_fPassedIdleTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedIdleTime >= m_fIdleTime)
		{
			if (m_vecTarget.empty()) return;

			// 회전량 계산
			m_eState = E_ROTATE;
			cVector2 vDir = m_vecTarget.front()->GetPosition() - m_vPos;
			m_fTargetAngle = atan2(vDir.y, vDir.x);
			m_fAmount = m_fTargetAngle - m_fAngle;
			while (m_fAmount < -PI)
				m_fAmount += 2 * PI;
			while (m_fAmount > PI)
				m_fAmount -= 2 * PI;

			m_fAngleSpeed = m_fAmount > 0 ? 0.1f : -0.1f;
			m_fAccAmount = 0.0f;
			m_fPassedIdleTime = 0.0f;
		}
	}
	else if (m_eState == E_ROTATE)
	{
		m_fAngle += m_fAngleSpeed;
		m_fAccAmount += m_fAngleSpeed;
		if (fabs(m_fAccAmount) >= fabs(m_fAmount))
		{
			m_fAngle = m_fTargetAngle;
			Fire(m_vecTarget.front());
			m_eState = E_IDLE;
		}
	}

	cAirplane::Update();
}
