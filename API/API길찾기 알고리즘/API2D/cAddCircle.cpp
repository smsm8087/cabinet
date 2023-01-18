#include "stdafx.h"
#include "cAddCircle.h"


cAddCircle::cAddCircle()
	:
m_nfRadius(20)
,m_num(0)
{
}


cAddCircle::~cAddCircle()
{
}

void cAddCircle::Init()
{
}

void cAddCircle::Update()
{

}

void cAddCircle::Render(HDC hdc,float _x,float _y)
{
	cUtil::DrawEllipseCenter(hdc, (int)m_nfRadius,cVector2(_x, _y));
	
	char szNum[10];
	wsprintf(szNum, "%d", m_num);
	TextOut(hdc, _x - 5, _y - 3, szNum, strlen(szNum));
	
	
}
