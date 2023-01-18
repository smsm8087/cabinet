#include "stdafx.h"
#include "cBulletManager.h"
#include "cBullet.h"

cBulletManager::cBulletManager()
{
}

cBulletManager::~cBulletManager()
{
}
void cBulletManager::Fire(cVector2 vPos, cVector2 vDir, const vector<cAirplane*>& vecTarget)
{
	cBullet* pBullet = nullptr;
	for (cBullet* p : m_vecBullet)
	{
		if (p->GetActive() == false)
		{
			pBullet = p;
			break;
		}
	}
	if (pBullet == NULL)
	{
		pBullet = new cBullet;
		m_vecBullet.push_back(pBullet);
	}

	pBullet->Init(vPos, vDir, vecTarget);
}
/*
cBullet * cBulletManager::GetBullet()
{
	if (m_lstPool.empty())
	{
		return new cBullet;
	}
	cBullet* pBullet = m_lstPool.front();
	m_lstPool.pop_front();
	return pBullet;
}


void cBulletManager::Fire(cVector2 vPos, cVector2 vDir, const vector<cAirplane*>& vecTarget)
{
	cBullet* pBullet = nullptr;
	for (cBullet* p : m_vecBullet)
	{
		if (p->GetActive() == false)
		{
			pBullet = p;
			break;
		}
	}
	if (pBullet == NULL)
	{
		pBullet = new cBullet;
		m_vecBullet.push_back(pBullet);
	}
	
	pBullet->Init(vPos, vDir, vecTarget);
}
*/
void cBulletManager::Update()
{
	for (cBullet* p : m_vecBullet)
	{
		p->Update();
	}
}

void cBulletManager::Render(HDC hdc)
{
	for (cBullet* p : m_vecBullet)
	{
		p->Render(hdc);
	}
}

void cBulletManager::Destroy()
{
	for (cBullet* p : m_vecBullet)
	{
		SAFE_DELETE(p);
	}
	m_vecBullet.clear();
}
