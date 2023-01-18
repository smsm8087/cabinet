#pragma once

#define g_pBulletManager cBulletManager::GetInstance()

class cBullet;
class cAirplane;

class cBulletManager
{
private:
	SINGLETON(cBulletManager);
private:
	vector<cBullet*> m_vecBullet;

public:
	//cBullet* GetBullet();
	void Fire(cVector2 vPos, cVector2 vDir, const vector<cAirplane*>& vecTarget);
	void Update();
	void Render(HDC hdc);
	void Destroy();
	void AddBullet(cBullet* pBullet);
};

