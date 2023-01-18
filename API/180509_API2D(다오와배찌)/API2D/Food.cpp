#include "stdafx.h"
#include "Food.h"


Food::Food()
	:mfDiameter(10.0f),
	mVisible(true)
{
}


Food::~Food()
{
}

void Food::Init(float x, float y, HWND hwnd)
{
	mfPosx = x;
	mfPosy = y;
	mhWnd = hwnd;
}

void Food::Update()
{
}

void Food::Render(HDC hdc)
{
	if (mVisible)
	{
		HBRUSH hBrush, hOldBrush;

		hBrush = CreateSolidBrush(RGB(255, 0, 0));

		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		RECT rc = RectMake(mfPosx, mfPosy, mfDiameter, mfDiameter);
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);

	}
}
