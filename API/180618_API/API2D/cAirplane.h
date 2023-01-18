#pragma once

#include "cBullet.h"

class cImage;

class cAirplane
{
protected:
	cVector2			m_vPos;
	cVector2			m_vDir;
	float				m_fRadius;
	float				m_fAngle;
	float				m_fAngleSpeed;
	float				m_fSpeed;
	float				m_fCannonLen;
	COLORREF			m_dwColor;
	vector<cAirplane*>	m_vecTarget;
	cImage*				m_pImage;
	//cBullet*			m_pBullet;
	GETSET_ADDREF(cBullet*, m_pBullet, Bullet);
	/*
	void SetBullet(cBullet* pBullet)
	{
		if (m_pBullet != pBullet)
		{
			SAFE_ADDREF(pBullet);
			SAFE_RELEASE(m_pBullet);
			m_pBullet = pBullet;
		}
	}
	cBullet* GetBullet()
	{
		return m_pBullet;
	}
	*/
public:
	cAirplane();
	virtual ~cAirplane();

	virtual void Init(const cVector2& vPos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Fire(cAirplane* pTarget = NULL);
	virtual float GetFullRadius();
	virtual float GetBodyRadius();
	virtual cVector2 GetPosition();
	virtual void AddTarget(cAirplane* pTarget);
};

