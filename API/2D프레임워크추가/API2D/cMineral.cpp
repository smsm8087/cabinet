#include "stdafx.h"
#include "cMineral.h"


cMineral::cMineral()
	:m_nRadius(32)
	, isImpossible(false)
{
	m_pt.x = -m_nRadius;
	m_pt.y = -m_nRadius;
	isSelected = false;
}


cMineral::~cMineral()
{
}

void cMineral::Init()
{
}

void cMineral::Update()
{
}

void cMineral::Render(HDC hdc)
{
	if (isSelected)
	{
		HPEN pen, oldpen;
		pen = CreatePen(PS_SOLID, 4, RGB(255, 255, 0));
		oldpen = (HPEN)SelectObject(hdc, pen);
		SelectObject(hdc, pen);
		Rectangle(hdc, m_pt.x * 32 - 5,
			m_pt.y * 32  - 5,
			m_pt.x * 32 + m_nRadius + 5,
			m_pt.y * 32 + m_nRadius + 5);
		SelectObject(hdc, oldpen);
		DeleteObject(pen);
	}
	HBRUSH hbrush, oldbrush;
	hbrush = CreateSolidBrush(RGB(0, 0, 255));
	oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

	Rectangle(hdc, m_pt.x * 32 ,
		m_pt.y * 32 ,
		m_pt.x * 32 + m_nRadius,
		m_pt.y * 32 + m_nRadius);
	SelectObject(hdc, oldbrush);
	DeleteObject(hbrush);
}
