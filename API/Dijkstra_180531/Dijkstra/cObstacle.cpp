#include "stdafx.h"
#include "cObstacle.h"


bool cObstacle::IsCollision(cVector2 pos1, cVector2 pos2) {
	// 왼쪽
	cVector2 rectPos1 = cVector2(m_rect.left, m_rect.bottom);
	cVector2 rectPos2 = cVector2(m_rect.left, m_rect.top);

	// 박스 교차 체크
	if(BoxColCheck(pos1, pos2, rectPos1, rectPos2)){
		// 선분 교차 체크
		if (EdgeColCheck(pos1, pos2, rectPos1, rectPos2))
			return true;
	}

	// 위쪽
	rectPos1 = cVector2(m_rect.left, m_rect.top);
	rectPos2 = cVector2(m_rect.right, m_rect.top);

	// 박스 교차 체크
	if(BoxColCheck(pos1, pos2, rectPos1, rectPos2)){
		// 선분 교차 체크
		if (EdgeColCheck(pos1, pos2, rectPos1, rectPos2))
			return true;
	}

	// 오른쪽
	rectPos1 = cVector2(m_rect.right, m_rect.bottom);
	rectPos2 = cVector2(m_rect.right, m_rect.top);

	// 박스 교차 체크
	if(BoxColCheck(pos1, pos2, rectPos1, rectPos2)){
		// 선분 교차 체크
		if (EdgeColCheck(pos1, pos2, rectPos1, rectPos2))
			return true;
	}
	
	// 아래쪽
	rectPos1 = cVector2(m_rect.left, m_rect.bottom);
	rectPos2 = cVector2(m_rect.right, m_rect.bottom);

	// 박스 교차 체크
	if(BoxColCheck(pos1, pos2, rectPos1, rectPos2)){
		// 선분 교차 체크
		if (EdgeColCheck(pos1, pos2, rectPos1, rectPos2))
			return true;
	}

	return false;
}

bool cObstacle::BoxColCheck(cVector2 r1_pos1, cVector2 r1_pos2, cVector2 r2_pos1, cVector2 r2_pos2) {
	RECT r1, r2, r3;

	r1.left = r1_pos1.x <= r1_pos2.x ? r1_pos1.x : r1_pos2.x;
	r1.right = r1_pos1.x > r1_pos2.x ? r1_pos1.x : r1_pos2.x;
	r1.top = r1_pos1.y <= r1_pos2.y ? r1_pos1.y : r1_pos2.y;
	r1.bottom = r1_pos1.y > r1_pos2.y ? r1_pos1.y : r1_pos2.y;

	r2.left = r2_pos1.x <= r2_pos2.x ? r2_pos1.x : r2_pos2.x;
	r2.right = r2_pos1.x > r2_pos2.x ? r2_pos1.x : r2_pos2.x;
	r2.top = r2_pos1.y <= r2_pos2.y ? r2_pos1.y : r2_pos2.y;
	r2.bottom = r2_pos1.y > r2_pos2.y ? r2_pos1.y : r2_pos2.y;

	return IntersectRect(&r3, &r1, &m_rect);
}

bool cObstacle::EdgeColCheck(cVector2 r1_pos1, cVector2 r1_pos2, cVector2 r2_pos1, cVector2 r2_pos2) {
	bool result1, result2;
	float CrossResult1, CrossResult2;

	cVector2 main = r1_pos2 - r1_pos1;
	cVector2 extra1 = r2_pos1 - r1_pos1;
	cVector2 extra2 = r2_pos2 - r1_pos1;

	CrossResult1 = CrossProduct(main, extra1);
	CrossResult2 = CrossProduct(main, extra2);

	if (CrossResult1 == 0 || CrossResult2 == 0)
		return true;

	result1 = (CrossResult1 < 0) != (CrossResult2 < 0);

	if (!result1)
		return false;

	main = r2_pos2 - r2_pos1;
	extra1 = r1_pos1 - r2_pos1;
	extra2 = r1_pos2 - r2_pos1;

	CrossResult1 = CrossProduct(main, extra1);
	CrossResult2 = CrossProduct(main, extra2);

	if (CrossResult1 == 0 || CrossResult2 == 0)
		return true;

	result2 = (CrossResult1 < 0) != (CrossResult2 < 0);

	return result2;
}

float cObstacle::CrossProduct(cVector2 v1, cVector2 v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

cObstacle::cObstacle()
	: m_bIsCol(false)
{ }


cObstacle::~cObstacle() { }

void cObstacle::Init(RECT rect) {
	m_rect = rect;
	m_bIsCol = false;
}

void cObstacle::Update(cVector2 pos1, cVector2 pos2) {
	m_bIsCol = IsCollision(pos1, pos2);
}

void cObstacle::Render(HDC hdc) {
	HBRUSH Brush, OldBrush;
	
	if(m_bIsCol){
		Brush = CreateSolidBrush(RGB(255, 0, 0));
		OldBrush = (HBRUSH)SelectObject(hdc, Brush);

		Rectangle(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

		SelectObject(hdc, OldBrush);
	}
	else{
		Brush = CreateSolidBrush(RGB(255, 255, 255));
		OldBrush = (HBRUSH)SelectObject(hdc, Brush);

		Rectangle(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

		SelectObject(hdc, OldBrush);
	}

	DeleteObject(Brush);
	DeleteObject(OldBrush);
}

void cObstacle::SetLeftTop(cVector2 pos) {
	m_rect.left = pos.x;
	m_rect.top = pos.y;
}

void cObstacle::SetRightBottom(cVector2 pos) {
	if (m_rect.left > pos.x) {
		m_rect.right = m_rect.left;
		m_rect.left = pos.x;
	}
	else {
		m_rect.right = pos.x;
	}

	if (m_rect.top > pos.y) {
		m_rect.bottom = m_rect.top;
		m_rect.top = pos.y;
	}
	else {
		m_rect.bottom = pos.y;
	}
}

bool cObstacle::PathColCheck(cVector2 pos1, cVector2 pos2)
{
	return IsCollision(pos1, pos2);
}

RECT cObstacle::GetRect()
{
	return m_rect;
}
