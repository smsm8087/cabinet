#include "stdafx.h"
#include "cUtil.h"

void cUtil::DrawEllipse(HDC hdc, float fRadius, cVector2 vCenter)
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
