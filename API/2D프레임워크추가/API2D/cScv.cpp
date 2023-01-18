#include "stdafx.h"
#include "cScv.h"


cScv::cScv()
	:m_nRadius(32)
	, m_nmineral(0)
{
	v_pt.x = -m_nRadius;
	v_pt.y = -m_nRadius;
	isSelected = false;
}


cScv::~cScv()
{
}

void cScv::Init()
{
}

void cScv::Update()
{
}

void cScv::Render(HDC hdc)
{
	if (isSelected)
	{
		HPEN pen, oldpen;
		pen = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
		oldpen = (HPEN)SelectObject(hdc, pen);
		SelectObject(hdc, pen);

		Ellipse(hdc, v_pt.x * 32 -5,
			v_pt.y * 32-5,
			v_pt.x * 32 + m_nRadius+5,
			v_pt.y * 32 + m_nRadius+5);
		SelectObject(hdc, oldpen);
		DeleteObject(pen);
	}
	HBRUSH hbrush, oldbrush;
	hbrush = CreateSolidBrush(RGB(255, 0, 0));
	oldbrush = (HBRUSH)SelectObject(hdc, hbrush);

	Ellipse(hdc, v_pt.x * 32,
		v_pt.y * 32,
		v_pt.x * 32 + m_nRadius,
		v_pt.y * 32 + m_nRadius);
	SelectObject(hdc, oldbrush);
	DeleteObject(hbrush);
	TextOut(hdc, v_pt.x* 32+m_nRadius/2 - 10, v_pt.y* 32+m_nRadius/2-10, "[S]", lstrlen("[S]"));
}
