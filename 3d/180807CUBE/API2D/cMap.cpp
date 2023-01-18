#include "stdafx.h"
#include "cMap.h"

cMap::cMap()
	: m_pFocusObject(NULL)
	, m_vMapPos(0, 0)
{
}

cMap::~cMap()
{
	SAFE_RELEASE(m_pFocusObject);

	for (auto p : m_vecMapObject)
	{
		SAFE_RELEASE(p);
	}
}

void cMap::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (m_pFocusObject)
	{
		m_pFocusObject->Update();
		m_vMapPos = m_pFocusObject->GetWorldPos();
		m_vMapPos.x -= rc.right / 2;
		m_vMapPos.y -= rc.bottom / 2;
	}

	if (m_vMapPos.x < 0)
		m_vMapPos.x = 0;
	if (m_vMapPos.y < 0)
		m_vMapPos.y = 0;
	if (m_vMapPos.x > m_stSize.nWidth - rc.right)
		m_vMapPos.x = m_stSize.nWidth - rc.right;
	if (m_vMapPos.y > m_stSize.nHeight - rc.bottom)
		m_vMapPos.y = m_stSize.nHeight - rc.bottom;
		
	for (auto p : m_vecMapObject)
	{
		p->Update();
	}
}

void cMap::Render(HDC hdc)
{
	if (m_pFocusObject)
		m_pFocusObject->Render(hdc, &m_vMapPos);

	for (auto p : m_vecMapObject)
	{
		p->Render(hdc, &m_vMapPos);
	}
}

void cMap::AddMapObject(cGameObject * pGameObject)
{
	SAFE_ADDREF(pGameObject);
	if(pGameObject)
		m_vecMapObject.push_back(pGameObject);
}
