#include "StdAfx.h"
#include "Obj.h"


CObj::CObj(void)
{
}


CObj::~CObj(void)
{
	Release();
}

HRESULT CObj::Initialize()
{
	m_tInfo.x = 50;
	m_tInfo.y = 50;
	return S_OK;
}
int CObj::Progress()
{
	return 0;
}

void CObj::Render()
{
}

void CObj::Release()
{
}