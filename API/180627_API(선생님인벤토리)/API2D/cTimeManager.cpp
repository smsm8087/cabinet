#include "stdafx.h"
#include "cTimeManager.h"

cTimeManager* cTimeManager::m_pInstance = NULL;

cTimeManager::cTimeManager()
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
}

float cTimeManager::GetElapsedTime()
{
	return m_dwElapsedTime / 1000.f;
}

void cTimeManager::Destroy()
{
	SAFE_DELETE(m_pInstance);
}
