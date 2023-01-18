#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: m_nRefCount(1)
{
	g_setObjectPool.insert(this);
}

cObject::~cObject()
{
	g_setObjectPool.erase(this);
	assert(m_nRefCount <= 0 && "�̷��� ���� ����� �̻���!");
}

void cObject::AddRef()
{
	m_nRefCount++;
}

void cObject::Release()
{
	m_nRefCount--;
	if (m_nRefCount <= 0)
	{
		delete this;
	}
}

cObject* cObject::AutoRelease()
{
	g_pAutoReleasePool->AddObject(this);
	return this;
}
