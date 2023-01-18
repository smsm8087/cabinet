#pragma once
static class cUtil
{
public:
	//원그리기
	static void DrawEllipse(HDC hdc, float fRadius, cVector2 vCenter);
	//정원 그리기
	static void DrawCircle(HDC hdc, float fRadius, cVector2 vCenter);
	//사각형
	static void DrawRect(HDC hdc, RECT& rc);
	//원충돌
	static bool isCollision(float x1, float y1, float x2, float y2, float r);
};

