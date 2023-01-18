#include "stdafx.h"
#include "cCommandCenter.h"


cCommandCenter::cCommandCenter()
	:m_nRadius(64)
	
{
	m_pt.x = -m_nRadius;
	m_pt.y = -m_nRadius;
	isSelected = false;
}


cCommandCenter::~cCommandCenter()
{
}

void cCommandCenter::Init()
{
}

void cCommandCenter::Update()
{
}

void cCommandCenter::Render(HDC hdc)
{
	if (isSelected)
	{
		HPEN pen, oldpen;
		pen = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
		oldpen = (HPEN)SelectObject(hdc, pen);
		SelectObject(hdc, pen);
		Rectangle(hdc, m_pt.x * 32 -5,
			m_pt.y * 32-5 ,
			m_pt.x * 32 + m_nRadius + 5,
			m_pt.y * 32 + m_nRadius + 5);
		SelectObject(hdc, oldpen);
		DeleteObject(pen);
	}
	HBRUSH hbrush, oldbrush;
	hbrush = CreateSolidBrush(RGB(0, 0, 0));
	oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
	Rectangle(hdc, m_pt.x*32, 
		m_pt.y * 32 ,
		m_pt.x * 32 + m_nRadius,
		m_pt.y * 32 + m_nRadius);

	SelectObject(hdc, oldbrush);
	DeleteObject(hbrush);
	TextOut(hdc, m_pt.x * 32+m_nRadius/2 -10, m_pt.y * 32+m_nRadius/2-10, "[C]", lstrlen("[C]"));
}
