#include "stdafx.h"
#include "cCircularSector.h"

cCircularSector::cCircularSector()
{
	playerx = 0.f;
	playery = 0.f;
	clickx = -1.f;
	clicky = 2.f;
	FILE* fp = NULL;
	fopen_s(&fp, "3.txt", "r");
	if (fp == NULL)return;
	for (size_t i = 0; i < 4; i++)
	{
		fscanf_s(fp, "(%f,%f)\n", &monsterx[i], &monstery[i]);
	}
	fclose(fp);
	
}


cCircularSector::~cCircularSector()
{
}

void cCircularSector::isinCircularSector()
{
	int monsterTempx[4] = { 0 };
	int monsterTempy[4] = { 0 };
	for (size_t i = 0; i < 4; i++)
	{
		monsterTempx[i] = monsterx[i];
		monsterTempy[i] = monstery[i];
		if (monsterTempx[i] < 0)
			monsterTempx[i] = abs(monsterTempx[i]);
		if (monsterTempy[i] < 0)
			monsterTempy[i] = abs(monsterTempy[i]);
		if (clickx < 0)
			clickx = abs(clickx);
		if (clicky < 0)
			clicky = abs(clicky);
		float temp = sqrt(monsterTempx[i] * monsterTempx[i] + monsterTempy[i] * monsterTempy[i]);
		if (sqrt(monsterTempx[i] * monsterTempx[i] + monsterTempy[i] * monsterTempy[i]) > 2)
		{
			isin[i] = false;
		}

		else
		{
			float seta = 0.0f;
			float b = sqrt(clickx*clickx + clicky * clicky);
			float c = sqrt(monsterTempx[i] * monsterTempx[i] + monsterTempy[i] * monsterTempy[i]);
			float a = sqrt((clickx - monsterTempx[i])*(clickx - monsterTempx[i]) + (clicky - monsterTempy[i])*(clicky - monsterTempy[i]));
			seta =(b*b + c * c - a * a) / (2 * b*c);
			/*int divide = (int)seta;
			if (seta > 1)
			{
			seta =(seta - divide);
			}*/
			/*if (seta <= sqrt(3) / 2)
			{
				isin[i]= true;
			}*/
			if (seta > 0.5)
			{
				isin[i] = true;
			}
			else
				isin[i]= false;

		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (isin[i])
		{
			printf("(%f,%f)의 몬스터좌표는 플레이어타격범위안에 들어있다.(참)\n", monsterx[i], monstery[i]);
		}
		else
			printf("(%f,%f)의 몬스터좌표는 플레이어타격범위안에 들어있지않다.(거짓)\n", monsterx[i], monstery[i]);
	}
	
}
