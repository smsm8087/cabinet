#include "stdafx.h"
#include "cUtil.h"

void cUtil::DrawEllipseCenter(HDC hdc, float fRadius, cVector2 vCenter)	//������ �����޾ƿͼ� ���� �׸���.
{
	Ellipse(hdc,
		vCenter.x - fRadius,
		vCenter.y - fRadius,
		vCenter.x + fRadius,
		vCenter.y + fRadius);
}

void cUtil::DrawRectangleCenter(HDC hdc, float fRadius, int _x, int _y, int r, int g, int b)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc,
		_x - fRadius,
		_y - fRadius,
		_x + fRadius,
		_y + fRadius);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void cUtil::DrawRectangleRGB(HDC hdc, float left, float top, float right, float bottom)
{
	

	Rectangle(hdc,
		left,top,right,bottom);
	
}
