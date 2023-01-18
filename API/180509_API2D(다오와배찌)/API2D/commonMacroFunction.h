#pragma once

//===================================================

//## ��ũ�� �Լ�(�ʿ��� �κ��� ���� ���� �߰�)

//===================================================

//point

inline POINT pointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//���׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1,NULL);
	LineTo(hdc, x2, y2);
}

//Rect �����(��ǥ�� ����)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}

//Rect �����(�߽����� ��������)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width/2, y + height/2 };
	return rc;
}

//�簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x+width, x+height);
}

//�� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

