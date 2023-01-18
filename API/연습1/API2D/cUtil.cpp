#include "stdafx.h"
#include "cUtil.h"

void cUtil::DrawEllipse(HDC hdc, float fRadius, cVector2 vCenter)	//센터의 점을받아와서 원을 그린다.
{
	Ellipse(hdc,
		vCenter.x - fRadius,
		vCenter.y - fRadius,
		vCenter.x + fRadius,
		vCenter.y + fRadius);
}
