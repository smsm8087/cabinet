#pragma once
static class cUtil
{
public:
	static void DrawEllipseCenter(HDC hdc, float fRadius, cVector2 vCenter);
	static void DrawRectangleCenter(HDC hdc, float fRadius,int _x,int _y, int r, int g, int b);
	static void DrawRectangleRGB(HDC hdc, float left, float top, float right, float bottom);
};

