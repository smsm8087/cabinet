#include "stdafx.h"
#include "cAddLine.h"
#include"cCheckcost.h"


cAddLine::cAddLine()
{
	
	check = new cCheckcost;
}


cAddLine::~cAddLine()
{
	SAFE_DELETE(check);
}

void cAddLine::moveRender(HDC hdc)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x1, y1);
	//±ÛÀÚ

	float distance = check->opercost((x1 - x), (y1 - y));
	float centerx = abs(x1 - x) / 2;
	float centery = abs(y1-y)/2;
	char szBuf[15];
	wsprintf(szBuf,"%d",(int)distance);
	if (x1 > x)
	{
		if (y1 > y)
		{
			TextOut(hdc, x + centerx, y + centery, szBuf, strlen(szBuf));
		}
		if (y1 < y)
		{
			TextOut(hdc, x + centerx, y - centery, szBuf, strlen(szBuf));
		}
	}
	if (x1 < x)
	{
		if (y1 > y)
		{
			TextOut(hdc, x - centerx, y + centery, szBuf, strlen(szBuf));
		}
		if (y1 < y)
		{
			TextOut(hdc, x - centerx, y - centery, szBuf, strlen(szBuf));
		}
	}
	
	
}

