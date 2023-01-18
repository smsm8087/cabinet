#pragma once

#define g_pAutoReleasePool cAutoReleasePool::GetInstance()

class cAutoReleasePool
{
private:
	SINGLETON(cAutoReleasePool);

private:
	vector<cObject*> m_vecPool;

public:
	void AddObject(cObject* pObject);
	void Drain();
};

