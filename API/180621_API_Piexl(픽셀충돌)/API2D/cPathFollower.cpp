#include "stdafx.h"
#include "cPathFollower.h"


cPathFollower::cPathFollower(cPoint2N ptFrom, cPoint2N ptTo, float fTime)
	: m_ptFrom(ptFrom)
	, m_ptTo(ptTo)
	, m_fTime(fTime)
	, m_fPassedTime(0.0f)
	, m_pNext(NULL)
{
}

cPathFollower::~cPathFollower()
{
}

void cPathFollower::Init(cPoint2N ptFrom, cPoint2N ptTo, float fTime)
{
	m_ptFrom = ptFrom;
	m_ptTo = ptTo;
	m_fTime = fTime;
	m_fPassedTime = 0.0f;
	m_pNext = NULL;
}

void cPathFollower::Start(float fPassedTime)
{
	m_fPassedTime = fPassedTime;
}

cPoint2N cPathFollower::Update(cPathFollower** ppThis)
{
	m_fPassedTime += g_pTimeManager->GetElapsedTime() * 64;

	float t = m_fPassedTime / m_fTime;
	if (t > 1.0f)
	{
		m_pNext->Start(m_fPassedTime - m_fTime);
		*ppThis = m_pNext;
		return m_ptTo;
	}
	return cPoint2N::Lerp(m_ptFrom , m_ptTo, t);
}
