#include "stdafx.h"
#include "cObstacle.h"


cObstacle::cObstacle()
{
}


cObstacle::~cObstacle()
{
}

void cObstacle::Render(HDC hdc, cVector2* pMapPos)
{
	cVector2 vScreen;
	vScreen = m_vWorldPos;
	if (pMapPos)
	{
		vScreen = m_vWorldPos - *pMapPos;
	}
	RECT rc = cUtil::MakeRect(vScreen.x, vScreen.y, m_stSize.nWidth, m_stSize.nHeight);
	cUtil::DrawRect(hdc, rc);
}
