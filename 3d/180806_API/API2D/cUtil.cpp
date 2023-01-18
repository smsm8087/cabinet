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

void cUtil::DrawCircle(HDC hdc, float fRadius, POINT ptCenter)
{
	Ellipse(hdc,
		ptCenter.x - fRadius,
		ptCenter.y - fRadius,
		ptCenter.x + fRadius,
		ptCenter.y + fRadius);
}

void cUtil::DrawCircle(HDC hdc, float fRadius, POINT ptCenter, COLORREF c)
{
	HBRUSH b = CreateSolidBrush(c);
	HBRUSH ob = (HBRUSH)SelectObject(hdc, b);
	cUtil::DrawCircle(hdc, fRadius, ptCenter);
	SelectObject(hdc, ob);
	DeleteObject(b);
}

void cUtil::DrawRect(HDC hdc, RECT & rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

void cUtil::DrawX(HDC hdc, RECT & rc)
{
	HPEN p = CreatePen(PS_SOLID, 2, RGB(0, 0 ,0));
	HPEN op = (HPEN)SelectObject(hdc, p);
	MoveToEx(hdc, rc.left, rc.top, NULL);
	LineTo(hdc, rc.right, rc.bottom);
	MoveToEx(hdc, rc.right, rc.top, NULL);
	LineTo(hdc, rc.left, rc.bottom);
	SelectObject(hdc, op);
	DeleteObject(p);
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

POINT cUtil::AddPoint(POINT & pt1, POINT & pt2)
{
	POINT pt;
	pt.x = pt1.x + pt2.x;
	pt.y = pt1.y + pt2.y;
	return pt;
}

POINT cUtil::AddPoint(POINT & pt, int n)
{
	POINT ptRet;
	ptRet.x = pt.x + n;
	ptRet.y = pt.y + n;
	return ptRet;
}

POINT cUtil::SubPoint(POINT & pt1, POINT & pt2)
{
	POINT pt;
	pt.x = pt1.x - pt2.x;
	pt.y = pt1.y - pt2.y;
	return pt;
}

POINT cUtil::PointZero()
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	return pt;
}

POINT cUtil::MakePoint(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

float cUtil::LengthSq(POINT & pt)
{
	return pt.x * pt.x + pt.y * pt.y;
}

float cUtil::LengthSq(POINT & pt1, POINT & pt2)
{
	POINT pt = cUtil::SubPoint(pt1, pt2);
	return cUtil::LengthSq(pt);
}

RECT cUtil::MakeRect(int x, int y, int w, int h)
{
	RECT rc;
	SetRect(&rc,
		x,
		y,
		x + w,
		y + h);
	return rc;
}

RECT cUtil::MakeRect(POINT & pt, ST_SIZE & size)
{
	RECT rc;
	SetRect(&rc,
		pt.x,
		pt.y,
		pt.x + size.nWidth,
		pt.y + size.nHeight);
	return rc;
}

POINT cUtil::Lerp(float t, POINT & pt1, POINT & pt2)
{
	POINT pt;
	pt.x = (1.0f - t) * pt1.x + t * pt2.x;
	pt.y = (1.0f - t) * pt1.y + t * pt2.y;
	return pt;
}
