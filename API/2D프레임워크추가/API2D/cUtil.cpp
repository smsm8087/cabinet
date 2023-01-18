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

bool cUtil::isCollision(float x1, float y1, float x2, float y2, float _r)
{
	float x = x1 - x2;
	float y = y1 - y2;

	float r = sqrt((x * x) + (y * y));
	/////////////////////////////////
	//���̰� ���������� ũ��
	//������ ���� �� ũ�� �浹�� �Ȼ���
	if (r > (_r + _r))
		return true;
	////////////////////////////////
	return false;
	return false;
}
