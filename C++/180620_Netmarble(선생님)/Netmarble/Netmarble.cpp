// Netmarble.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "P1.h"
#include "P2.h"
#include "P3.h"
#include "P4.h"

int main()
{
	int a[] = { 0 };
	P4 p;
	p.Excute(15, a, 1);
	/*
	int aEnemy[4][2] =
	{
		{0,1},{-1,1},{1,0},{-2,2},
	};
	P3 p;
	p.Excute(-1, 2, 4, aEnemy);
	*/
	/*
	int aMatrix[3][3] =
	{
		{ 1,2,3 },
		{ 4,5,6 },
		{ 7,8,9 },
	};
	P2 p;
	p.Excute(3, aMatrix);
	*/
	/*
	P1 p;
	int aEdge[4][2] = 
	{
		{ 1, 2 },
		{ 2, 4 },
		{ 3, 1 },
		{ 4, 5 },
	};
	p.Excute(5, aEdge, 4);
	*/

	/*
	int a[10];
	a[3] = 3;
	
	int* pa = a;
	pa[3] = 4;

	//printf("%d", a[3]);
	//printf("%x\n", pa);
	//printf("%x\n", &a[3]); // a + 4 * 3

	int b[4][3];
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			printf("%x\n", &b[i][j]);
		}
	}
	// b +4 +4 +4 +4 +4 +4 +4 +4 +4 +4 +4 +4
	//  00 01 02 10 11 12 20 21 22 30 31 32
	// |  |  |  |  |  |  |  |  | 0|  |  |  |
	//  00 01 02 
	//  10 11 12 
	//  20 21 22 
	//  30 31 32
	b[2][2]; // b + 4 * 3 * 2 + 2
	
	int** ppa;
	ppa = new int*[5];
	for (size_t i = 0; i < 5; i++)
	{
		ppa[i] = new int[2];
	}

	int* arr = new int[5];
	*/
    return 0;
}

