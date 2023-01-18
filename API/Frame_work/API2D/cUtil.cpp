#include "stdafx.h"
#include "cUtil.h"

void cUtil::DrawCircle(HDC hdc, float fRadius, cVector2 vCenter)
{
	Ellipse(hdc,
		vCenter.x - fRadius,
		vCenter.y - fRadius,
		vCenter.x + fRadius,
		vCenter.y + fRadius);
}

void cUtil::DrawRect(HDC hdc, RECT & rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

bool cUtil::IsCollision(POINT & pt1, POINT & pt2, POINT & pt3, POINT & pt4)
{
	float sign1 = (pt2.x - pt1.x)*(pt3.y - pt1.y) - (pt3.x - pt1.x)*(pt2.y - pt1.y);
	float sign2 = (pt2.x - pt1.x)*(pt4.y - pt1.y) - (pt4.x - pt1.x)*(pt2.y - pt1.y);
	float sign3 = (pt4.x - pt3.x)*(pt1.y - pt3.y) - (pt1.x - pt3.x)*(pt4.y - pt3.y);
	float sign4 = (pt4.x - pt3.x)*(pt2.y - pt3.y) - (pt2.x - pt3.x)*(pt4.y - pt3.y);

	return sign1 * sign2 < 0 && sign3 * sign4 < 0;
}

bool cUtil::IsCollision(POINT & ptLineFrom, POINT & ptLineTo, RECT & rc)
{
	RECT rcLine;
	rcLine.left = min(ptLineFrom.x, ptLineTo.x);
	rcLine.top = min(ptLineFrom.y, ptLineTo.y);
	rcLine.right = max(ptLineFrom.x, ptLineTo.x);
	rcLine.bottom = max(ptLineFrom.y, ptLineTo.y);
	
	if (rcLine.right < rc.left) return false;
	if (rc.right < rcLine.left) return false;
	if (rcLine.bottom < rc.top) return false;
	if (rc.bottom < rcLine.top) return false;
	
	vector<POINT> vecPos;
	vecPos.push_back(cVector2(rc.left, rc.top).ToPoint());
	vecPos.push_back(cVector2(rc.left, rc.bottom).ToPoint());
	vecPos.push_back(cVector2(rc.left, rc.bottom).ToPoint());
	vecPos.push_back(cVector2(rc.right, rc.bottom).ToPoint());
	vecPos.push_back(cVector2(rc.right, rc.bottom).ToPoint());
	vecPos.push_back(cVector2(rc.right, rc.top).ToPoint());
	vecPos.push_back(cVector2(rc.right, rc.top).ToPoint());
	vecPos.push_back(cVector2(rc.left, rc.top).ToPoint());

	for (size_t i = 0; i < vecPos.size(); i += 2)
	{
		if (cUtil::IsCollision(ptLineFrom, ptLineTo, vecPos[i], vecPos[i + 1]))
			return true;
	}
	
	return false;
}

void cUtil::DrawShadowText(HDC hdc, int x, int y, const char* str, DWORD textColor)
{
	//Text 배경을 투명으로...
	SetBkMode(hdc, TRANSPARENT);

	//기존의  Text 색을 기억한다.
	DWORD prevTextColor = GetTextColor(hdc);

	SetTextColor(hdc, 0x00000000);
	TextOut(hdc, x + 1, y + 1, str, strlen(str));

	SetTextColor(hdc, textColor);
	TextOut(hdc, x, y, str, strlen(str));

	//기존색으로 돌려 놓는다
	SetTextColor(hdc, prevTextColor);

	//Text 배경을 불투명
	SetBkMode(hdc, OPAQUE);

}
