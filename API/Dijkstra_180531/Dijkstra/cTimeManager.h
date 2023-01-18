#pragma once

#define g_pTimeManager cTimeManager::GetTimeManager()

class cTimeManager
{
	static cTimeManager* m_pInstance;

	int m_dwPrevTimeStamp;
	int m_dwElapsedTime;
private:
	cTimeManager();
	~cTimeManager();
public:
	static cTimeManager* GetTimeManager();

	void Init();
	void Update();
	float GetElapsedTime();
	void Destroy();
};

