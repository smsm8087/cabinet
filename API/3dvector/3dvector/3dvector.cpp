// 3dvector.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include"cMatrix.h"
#include<time.h>


int main()
{
	srand((unsigned int) time(NULL));
	cMatrix m(4),n(4),temp(6);
	temp = temp.Random(6, -1, 1);
	cMatrix temp2 = temp.Invserse(temp);
	cMatrix result = temp * temp2;
	temp.Print();
	cout << endl;
	temp2.Print();
	cout << endl;
	result.Print();
	
    return 0;
}

