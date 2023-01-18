#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager* cTimeManager::m_pInstance = NULL;

cTimeManager::cTimeManager()
	: m_nFrameCount(0)
	, m_nFPS(0)
	, m_nFPSTimer(0)
{
}


cTimeManager::~cTimeManager()
{
}

void cTimeManager::Init()
{
	m_dwElapsedTime = 0;
	m_dwPrevTimeStamp = GetTickCount();
}

void cTimeManager::Update()
{
	DWORD dwCurrTimeStamp = GetTickCount();
	m_dwElapsedTime = dwCurrTimeStamp - m_dwPrevTimeStamp;
	m_dwPrevTimeStamp = dwCurrTimeStamp;

	m_nFPSTimer += m_dwElapsedTime;
	if (m_nFPSTimer > 1000)
	{
		m_nFPS = m_nFrameCount;
		m_nFrameCount = 0;
		m_nFPSTimer -= 1000;
	}

	++m_nFrameCount;
}

float cTimeManager::GetElapsedTime()
{
	return m_dwElapsedTime / 1000.f;
}

void cTimeManager::Destroy()
{
	SAFE_DELETE(m_pInstance);
}
