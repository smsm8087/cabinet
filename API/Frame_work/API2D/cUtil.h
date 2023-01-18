#pragma once
static class cUtil
{
public:
	static void DrawCircle(HDC hdc, float fRadius, cVector2 vCenter);
	static void DrawRect(HDC hdc, RECT& rc);
	static bool IsCollision(POINT& pt1, POINT& pt2, POINT& pt3, POINT& pt4);
	static bool IsCollision(POINT & ptLineFrom, POINT & ptLineTo, RECT& rc);
	static void DrawShadowText(HDC hdc, int x, int y, const char* str, DWORD textColor);
};

