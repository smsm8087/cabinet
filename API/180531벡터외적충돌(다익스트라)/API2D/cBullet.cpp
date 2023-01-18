#include "stdafx.h"
#include "cBullet.h"
#include "cAirplane.h"

cBullet::cBullet()
	: m_isActive(false)
	, m_vPos(0.0f, 0.0f)
	, m_vDir(0.0f, 0.0f)
{
}

cBullet::~cBullet()
{
}

void cBullet::Init(cVector2 vPos, cVector2 vDir, const vector<cAirplane*>& vecTarget)
{
	m_vPos = vPos;
	m_vDir = vDir;
	m_isActive = true;
	m_vecTarget = vecTarget;
}

void cBullet::Update()
{
	if (!m_isActive) return;
 	m_vPos = m_vPos + m_vDir * 3.f;
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_isActive = PtInRect(&rc, m_vPos.ToPoint());
	for (auto p : m_vecTarget)
	{
		float r = p->GetBodyRadius();
		cVector2 vTargetPos = p->GetPosition();
		if ((vTargetPos - m_vPos).LenSq() < r * r)
		{
			m_isActive = false;
		}
	}
}

void cBullet::Render(HDC hdc)
{
	if (!m_isActive) return;
	cUtil::DrawCircle(hdc, 5, m_vPos);
}

bool cBullet::GetActive()
{
	return m_isActive;
}
