// 넷마블입사시험문제.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include"cMakeRowCol.h"
#include"cCircularSector.h"
#include"cRoadLight.h"
#include"cFindFriends.h"
#include"cReservation.h"


int main()
{
	cReservation reserve;
	reserve.Excute(4);
	//소셜앱 친구구하기
	/*cFindFriends find;
	find.Update();*/

	//가로세로 행렬더하기
	/*cMakeRowCol makematrix;
	makematrix.make_Nmatrix();
	makematrix.make_difference();
	makematrix.printarray();*/

	//부채꼴범위판정
	/*cCircularSector cicularSector;
	cicularSector.isinCircularSector();*/

	//가로등문제 전구갯수구하기
	/*cRoadLight roadlight;
	int result = roadlight.calculatelight();
	cout << result << endl;*/

    return 0;
}

