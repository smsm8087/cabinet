#include "stdafx.h"
#include "P3.h"


P3::P3()
{
}


P3::~P3()
{
}

void P3::Excute(int x, int y, int nNumEnemy, int aEnemyCoord[][2])
{
	float fRadius = 2.0f;
	float fCos60 = cosf(3.141592 / 3);
	for (size_t i = 0; i < nNumEnemy; i++)
	{
		int nEX = aEnemyCoord[i][0];
		int nEY = aEnemyCoord[i][1];
		float a = sqrt(x * x + y * y);
		float b = sqrt(nEX * nEX + nEY * nEY);
		float fCos = (x * nEX + y * nEY) / (a * b);
		if (fCos > fCos60 && b < fRadius)
		{
			printf("%d 번 적 맞음\n", i + 1);
		}
	}
}
