#pragma once

class cAirplane;

class cBullet
{
private:
	bool		m_isActive;
	cVector2	m_vPos;
	cVector2	m_vDir;
	vector<cAirplane*> m_vecTarget;

public:
	cBullet();
	~cBullet();

	void Init(cVector2 vPos, cVector2 vDir, const vector<cAirplane*>& vecTarget);
	void Update();
	void Render(HDC hdc);
	bool GetActive();
};

