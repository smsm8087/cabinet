#include "stdafx.h"
#include "cCheckcost.h"


cCheckcost::cCheckcost()
{
}


cCheckcost::~cCheckcost()
{
}

float cCheckcost::opercost(float _x, float _y)
{
	return sqrt(_x*_x + _y * _y);
}
