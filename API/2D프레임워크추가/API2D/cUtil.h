#pragma once
static class cUtil
{
public:
	//���׸���
	static void DrawEllipse(HDC hdc, float fRadius, cVector2 vCenter);
	//���� �׸���
	static void DrawCircle(HDC hdc, float fRadius, cVector2 vCenter);
	//�簢��
	static void DrawRect(HDC hdc, RECT& rc);
	//���浹
	static bool isCollision(float x1, float y1, float x2, float y2, float r);
};

