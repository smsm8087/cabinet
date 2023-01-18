#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
	static TimeManager* m_pInstance;
	int m_dwPrevTimeStamp;
	int m_dwElapsedTime;

private:
	TimeManager();
	~TimeManager();

public:
	static TimeManager * GetInstance()
	{
		if (m_pInstance)
			return m_pInstance;
		m_pInstance = new TimeManager;
		m_pInstance->Init();
		return m_pInstance;
	}

	void Init();
	void Update();
	float GetElapsedTime();
	void Destroy();
};

