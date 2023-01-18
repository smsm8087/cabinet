#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
	static cTimeManager* m_pInstance;
	int m_dwPrevTimeStamp;
	int m_dwElapsedTime;
	int m_nFPSTimer;
	int m_nFPS;
	int m_nFrameCount;
private:
	cTimeManager();
	~cTimeManager();

public:
	static cTimeManager * GetInstance()
	{
		if (m_pInstance)
			return m_pInstance;
		m_pInstance = new cTimeManager;
		m_pInstance->Init();
		return m_pInstance;
	}

	void Init();
	void Update();
	float GetElapsedTime();
	void Destroy();
};

