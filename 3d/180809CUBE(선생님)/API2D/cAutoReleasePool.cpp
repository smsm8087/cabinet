#include "stdafx.h"
#include "cAutoReleasePool.h"


cAutoReleasePool::cAutoReleasePool()
{
}


cAutoReleasePool::~cAutoReleasePool()
{
}

void cAutoReleasePool::AddObject(cObject * pObject)
{
	m_vecPool.push_back(pObject);
}

void cAutoReleasePool::Drain()
{
	if (m_vecPool.empty()) return;
	for (auto p : m_vecPool)
	{
		SAFE_RELEASE(p);
	}
	m_vecPool.clear();
}
