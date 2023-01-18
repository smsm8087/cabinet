#include "stdafx.h"
#include "P4.h"


P4::P4()
{
}


P4::~P4()
{
}

void P4::Excute(int nLen, int aData[], int nNumData)
{
	set<int> setLight;
	for (size_t i = 0; i < nNumData; i++)
	{
		setLight.insert(aData[i]);
	}
	int nPrevLightPos = 0;
	int nMaxDist = 0;
	for (int n : setLight)
	{
		int nDist = n - nPrevLightPos;
		if (nMaxDist < nDist)
		{
			nMaxDist = nDist;
		}
		nPrevLightPos = n;
	}
	int nDist = nLen - nPrevLightPos;
	if (nMaxDist < nDist)
	{
		nMaxDist = nDist;
	}
	printf("%d\n", (nMaxDist + 1) / 2);
}
