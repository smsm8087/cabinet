#include "stdafx.h"
#include "cItem.h"
#include "cImage.h"


cItem::cItem()
{
}


cItem::~cItem()
{
}

void cItem::Init(int Col, int Row)
{
	m_fUppassedTime = 0.f;
	m_fDownpassedTime = 0.f;
	m_nRow = Row;
	m_nCol = Col;
	m_rcItem.right = STAGE_START_X + m_nRow * 40 + 40;
	m_rcItem.bottom = STAGE_START_Y + m_nCol * 40 + 40;
	m_rcItem.left = m_rcItem.right - 40;
	m_rcItem.top = m_rcItem.bottom - 44;


	m_rcOwnItem.right = STAGE_START_X + m_nRow * 40 + 40;
	m_rcOwnItem.bottom = STAGE_START_Y + m_nCol * 40 + 40;
	m_rcOwnItem.left = m_rcOwnItem.right - 40;
	m_rcOwnItem.top = m_rcOwnItem.bottom - 40;



	SetRect(&m_rcSpeedImage, 0, 0, 40, 50);
	SetRect(&m_rcPowerImage, 40, 0, 80, 50);
	SetRect(&m_rcAddBombImage, 80, 0, 120, 50);
	SetRect(&m_rcFullPowerImage, 120, 0, 160, 50);
	m_nRandom = rand() % 5;
	e_itemmove = E_UP;

	switch (m_nRandom)
	{
	case 0:
	{
		e_itemValue = E_SPEED;
		m_pSpeed = new cImage("image/item.bmp");
	}break;
	case 1:
	{
		e_itemValue = E_POWER;
		m_pPower = new cImage("image/item.bmp");
	}break;
	case 2:
	{
		e_itemValue = E_ADDBOMB;
		m_pAddBomb = new cImage("image/item.bmp");
	}break;
	case 3:
	{
		e_itemValue = E_FULLPOPWER;
		m_pFullPower = new cImage("image/item.bmp");
	}break;
	case 4:
	{
		e_itemValue = E_NONE;
	}break;
	default:
		break;
	}
	m_fPossibleDeleteTime = 0.f;
}

void cItem::Update()
{
	if (e_itemmove == E_UP)
	{
		m_rcItem.top--;
		m_rcItem.bottom--;
		m_fUppassedTime += g_pTimeManager->GetElapsedTime();
		if (m_fUppassedTime > 0.3f)
		{
			m_fUppassedTime -= 0.3f;
			e_itemmove = E_DOWN;
		}
	}
	else if (e_itemmove == E_DOWN)
	{
		m_rcItem.top++;
		m_rcItem.bottom++;
		m_fDownpassedTime += g_pTimeManager->GetElapsedTime();
		if (m_fDownpassedTime > 0.3f)
		{
			m_fDownpassedTime -= 0.3f;
			e_itemmove = E_UP;
		}
	}
	m_fPossibleDeleteTime += g_pTimeManager->GetElapsedTime();
	if (m_fPossibleDeleteTime >= 1.f)
	{
		m_fPossibleDeleteTime = 1.f;
		m_isPossibleDelete = true;
	}
}

void cItem::Render(HDC hdc)
{
	switch (e_itemValue)
	{
	case 0 :
	{
		if(m_pSpeed)
			m_pSpeed->TransparentRender(hdc,m_rcItem,m_rcSpeedImage);
	}break;
	case 1:
	{
		if (m_pPower)
			m_pPower->TransparentRender(hdc, m_rcItem, m_rcPowerImage);
	}break;
	case 2:
	{
		if (m_pAddBomb)
			m_pAddBomb->TransparentRender(hdc, m_rcItem, m_rcAddBombImage);
	}break;
	case 3:
	{
		if (m_pFullPower)
			m_pFullPower->TransparentRender(hdc, m_rcItem, m_rcFullPowerImage);
	}break;
	case 4:
	{
	// E_NONE;
	}break;
	default:
		break;
	}
}
