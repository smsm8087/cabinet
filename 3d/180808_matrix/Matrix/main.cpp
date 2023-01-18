// Matrix.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "cMatrix.h"

int main()
{
	cMatrix m = cMatrix::Random(4, -1, 1);
	float f;
	cMatrix inv = m.Invserse(f);
	(m).Print();
	cout << endl;
	(inv).Print();
	cout << endl;
	if (fabs(f) > EPSILON)
	{
		(m * inv).Print();
	}
	
    return 0;
}


