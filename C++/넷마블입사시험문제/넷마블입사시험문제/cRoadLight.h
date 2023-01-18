#pragma once
class cRoadLight
{
	set<int>	m_setlight;
	int length;
public:
	cRoadLight();
	~cRoadLight();

	int calculatelight();
};

