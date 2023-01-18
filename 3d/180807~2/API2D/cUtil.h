#pragma once
static class cUtil
{
public:
	static void DrawCircle(HDC hdc, float fRadius, cVector2 vCenter);
	static void DrawCircle(HDC hdc, float fRadius, POINT ptCenter);
	static void DrawCircle(HDC hdc, float fRadius, POINT ptCenter, COLORREF c);
	static void DrawRect(HDC hdc, RECT& rc);
	static void DrawX(HDC hdc, RECT& rc);
	static bool IsCollision(POINT& pt1, POINT& pt2, POINT& pt3, POINT& pt4);
	static bool IsCollision(POINT & ptLineFrom, POINT & ptLineTo, RECT& rc);
	static POINT AddPoint(POINT& pt1, POINT& pt2);
	static POINT AddPoint(POINT& pt, int n);
	static POINT SubPoint(POINT& pt1, POINT& pt2);
	static POINT PointZero();
	static POINT MakePoint(int x, int y);
	static float LengthSq(POINT& pt);
	static float LengthSq(POINT& pt1, POINT& pt2);
	static RECT MakeRect(int x, int y, int w, int h);
	static RECT MakeRect(POINT& pt, ST_SIZE& size);
	static POINT Lerp(float t, POINT& pt1, POINT& pt2);
};

