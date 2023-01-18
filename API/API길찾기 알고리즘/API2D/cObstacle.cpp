#include "stdafx.h"
#include "cObstacle.h"


cObstacle::cObstacle()
	:x(0.0f),x1(0.0f),y(0.0f),y1(0.0f),collision(false)
{
}


cObstacle::~cObstacle()
{
}

void cObstacle::Render(HDC hdc, float _x, float _y, float _x1, float _y1)
{
	cUtil::DrawRectangleRGB(hdc, _x, _y, _x1, _y1);
	if (collision)
	{
		TextOut(hdc, (_x+_x1) / 2,
			(_y+_y1) / 2, "충돌", strlen("충돌"));
	}
}
