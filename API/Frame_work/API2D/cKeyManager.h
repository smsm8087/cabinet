#pragma once


#define MAX_KEY_NUM		128

class cKeyManager 
{
private:
	bool	m_bDownCheck[128];
	bool	m_bUpCheck[128];
	static cKeyManager* m_pInstance;


public:
	cKeyManager();
	~cKeyManager();

public:

	//HRESULT Init(void);
	void Release();


	bool IsOnceDown(int nVkey);
	bool IsOnceUp(int nVkey);

	bool IsStayDown(int nVkey);
	static cKeyManager * GetInstance()
	{
		if (m_pInstance)
			return m_pInstance;
		m_pInstance = new cKeyManager;
		return m_pInstance;
	}

};


#define g_pKeyManager cKeyManager::GetInstance()


