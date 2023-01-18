#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
{
	for (int i = 0; i < 7; i++)
	{
		m_vFrontColumUp[i]		= cVector3(-3 + i, 0, 3);
		m_vFrontColumDown[i]	= cVector3(-3 + i, 0, -3);
		m_vFrontRowLeft[i]		= cVector3(-3, 0, 3 - i);
		m_vFrontRowRight[i]		= cVector3(3, 0, 3 - i);

		m_vBackColumUp[i] = cVector3(-3 + i, -10, 3);
		m_vBackColumDown[i] = cVector3(-3 + i, -10, -3);
		m_vBackRowLeft[i] = cVector3(-3, -10, 3 - i);
		m_vBackRowRight[i] = cVector3(3, -10, 3 - i);

		
	}

	for (int i = 0; i <11; i++)
	{
		m_vBetweenRowLeft[i] = cVector3(-3, 0-i, 3 );
		m_vBetweenRowRight[i] = cVector3(3, 0-i, 3 );

		m_vBetweenDownRowLeft[i] = cVector3(-3, 0 - i, -3);
		m_vBetweenDownRowRight[i] = cVector3(3, 0 - i, -3);
	}
}

cGrid::~cGrid()
{

}

void cGrid::Render(HDC hdc)
{
	HPEN hpen, oldpen;
	hpen = CreatePen(PS_SOLID, 2,RGB(0, 255, 255));
	oldpen = (HPEN)SelectObject(hdc, hpen);
	SelectObject(hdc, hpen);

	cVector3 vFup[7];
	cVector3 vFDown[7];
	cVector3 vFLeft[7];
	cVector3 vFRight[7];

	cVector3 vBup[7];
	cVector3 vBDown[7];
	cVector3 vBLeft[7];
	cVector3 vBRight[7];

	cVector3 vBTLeft[11];
	cVector3 vBTRight[11];
	cVector3 vBDLeft[11];
	cVector3 vBDRight[11];
	cMatrix m = g_matView * g_matProj * g_matViewport;
	for (size_t i = 0; i < 7; i++)
	{
		vFup[i] = m_vFrontColumUp[i].TransformCoord(m);
		vFDown[i] = m_vFrontColumDown[i].TransformCoord(m);
		vFLeft[i] = m_vFrontRowLeft[i].TransformCoord(m);
		vFRight[i] = m_vFrontRowRight[i].TransformCoord(m);

		vBup[i] = m_vBackColumUp[i].TransformCoord(m);
		vBDown[i] = m_vBackColumDown[i].TransformCoord(m);
		vBLeft[i] = m_vBackRowLeft[i].TransformCoord(m);
		vBRight[i] = m_vBackRowRight[i].TransformCoord(m);

		MoveToEx(hdc, vFup[i].x, vFup[i].y, NULL);
		LineTo(hdc, vBup[i].x, vBup[i].y);

		MoveToEx(hdc, vFLeft[i].x, vFLeft[i].y, NULL);
		LineTo(hdc, vBLeft[i].x, vBLeft[i].y);

		MoveToEx(hdc, vFDown[i].x, vFDown[i].y, NULL);
		LineTo(hdc, vBDown[i].x, vBDown[i].y);

		MoveToEx(hdc, vFRight[i].x, vFRight[i].y, NULL);
		LineTo(hdc, vBRight[i].x, vBRight[i].y);

		//안쪽사각형
		MoveToEx(hdc, vBup[i].x, vBup[i].y, NULL);
		LineTo(hdc, vBDown[i].x, vBDown[i].y);

		MoveToEx(hdc, vBLeft[i].x, vBLeft[i].y, NULL);
		LineTo(hdc, vBRight[i].x, vBRight[i].y);

	}
	for (int i = 0; i < 11; i++)
	{
		vBTLeft[i] = m_vBetweenRowLeft[i].TransformCoord(m);
		vBTRight[i] = m_vBetweenRowRight[i].TransformCoord(m);
		vBDLeft[i] = m_vBetweenDownRowLeft[i].TransformCoord(m);
		vBDRight[i] = m_vBetweenDownRowRight[i].TransformCoord(m);
		
		MoveToEx(hdc, vBTLeft[i].x, vBTLeft[i].y, NULL);
		LineTo(hdc, vBTRight[i].x, vBTRight[i].y);

		MoveToEx(hdc, vBDLeft[i].x, vBDLeft[i].y, NULL);
		LineTo(hdc, vBDRight[i].x, vBDRight[i].y);

		MoveToEx(hdc, vBTLeft[i].x, vBTLeft[i].y, NULL);
		LineTo(hdc, vBDLeft[i].x, vBDLeft[i].y);

		MoveToEx(hdc, vBTRight[i].x, vBTRight[i].y, NULL);
		LineTo(hdc, vBDRight[i].x, vBDRight[i].y);
	}
	SelectObject(hdc, oldpen);
	DeleteObject(hpen);

}
