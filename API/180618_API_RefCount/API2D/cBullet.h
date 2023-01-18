#pragma once

class cAirplane;

class cBullet : public cObject
{
private:
	bool		m_isActive;
	cVector2	m_vPos;
	cVector2	m_vDir;
	vector<cAirplane*> m_vecTarget;

private:
	cBullet();

public:
	
	static cBullet* Create();
	virtual ~cBullet();
	
	void Init(cVector2 vPos, cVector2 vDir, const vector<cAirplane*>& vecTarget);
	void Update();
	void Render(HDC hdc);
	bool GetActive();
};

