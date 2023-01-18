#include "stdafx.h"
#include "cRoadLight.h"


cRoadLight::cRoadLight()
	:length(5)
{
	//m_setlight.insert(15,5,3,7,9,14,0)
	/*m_setlight.insert(15);
	m_setlight.insert(5);
	m_setlight.insert(3);
	m_setlight.insert(7);
	m_setlight.insert(9);
	m_setlight.insert(14);
	m_setlight.insert(0);*/
	m_setlight.insert(2);
	m_setlight.insert(5);

}


cRoadLight::~cRoadLight()
{
}

int cRoadLight::calculatelight()
{
	int distance = 0;
	int prev = 0;
	int result = 0;
	int min = INT_MIN;
	for (auto p : m_setlight)
	{
		distance = p - prev;
		if (distance > min)
		{
			min = distance;
			result = min;
		}
		prev = p;
		
	}
	return result/2+1;
}
