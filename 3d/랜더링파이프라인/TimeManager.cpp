#include "stdafx.h"
#include "TimeManager.h"

TimeManager* TimeManager::m_pInstance = NULL;

TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	m_dwElapsedTime = 0;
	m_dwPrevTimeStamp = GetTickCount();
}

void TimeManager::Update()
{
	DWORD dwCurrTimeStamp = GetTickCount();
	m_dwElapsedTime = dwCurrTimeStamp - m_dwPrevTimeStamp;
	m_dwPrevTimeStamp = dwCurrTimeStamp;
}

float TimeManager::GetElapsedTime()
{
	return m_dwElapsedTime / 1000.f;
}

void TimeManager::Destroy()
{
	SAFE_DELETE(m_pInstance);
}
