#include "StdAfx.h"
#include "cKeyManager.h"

cKeyManager* cKeyManager::m_pInstance = NULL;

cKeyManager::cKeyManager()
{
}

cKeyManager::~cKeyManager()
{
}


void cKeyManager::Release()
{
}

bool cKeyManager::IsOnceDown(int nVkey)
{

	//nVkey ���� ����
	if (GetAsyncKeyState(nVkey) & 0x8000)
	{
		if (m_bDownCheck[nVkey] == false)
		{
			m_bDownCheck[nVkey] = true;
			return true;
		}
	}


	//�ȴ��� ����
	else
	{
		if (m_bDownCheck[nVkey])
			m_bDownCheck[nVkey] = false;
	}


	return false;
}

bool cKeyManager::IsOnceUp(int nVkey)
{
	//nVkey ���� ����
	if (GetAsyncKeyState(nVkey) & 0x8000)
	{
		if (m_bUpCheck[nVkey] == false)
		{
			m_bUpCheck[nVkey] = true;
		}
	}


	//�ȴ��� ����
	else
	{
		if (m_bUpCheck[nVkey]) {
			m_bUpCheck[nVkey] = false;
			return true;
		}
	}

	return false;
}

bool cKeyManager::IsStayDown(int nVkey)
{
	if (GetAsyncKeyState(nVkey) & 0x8000)
		return true;

	return false;
}