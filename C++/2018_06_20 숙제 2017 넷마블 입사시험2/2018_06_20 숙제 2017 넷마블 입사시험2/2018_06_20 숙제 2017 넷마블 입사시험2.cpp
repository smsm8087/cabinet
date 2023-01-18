// 2018_06_20 숙제 2017 넷마블 입사시험2.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>	//sort 을 사용하기위한 인클루드
using namespace std;

struct DATA
{
	int ID;
	int Reservation;
};

struct DATA2
{
	int Num1;
	int Num2;
};

struct DATA3
{
	unsigned long long X;
	unsigned long long Y;
};

vector<int> Problem1(vector<DATA>& vecData, int RoomCount)
{
	vector<int> vecRoom;			//방
	vector<DATA> vecReservation;	//예약 목록

	vecRoom.resize(RoomCount, INT_MAX);

	for (int i = 0; i < vecData.size(); ++i)	//손님을 검사한다.
	{
		bool isCheck = false;
		for (int j = 0; j < vecReservation.size(); ++j)	//예약 목록을 검사한다.
		{
			if (vecReservation[j].ID == vecData[i].ID) //이미 예약목록에 있는 손님이라면
			{
				vecReservation[j].Reservation = vecData[i].Reservation;	//예약 내용 갱신
				isCheck = true;
			}
		}
		if (!isCheck)
		{
			vecReservation.push_back(vecData[i]);
		}

	}

	for (int i = 0; i < vecReservation.size(); ++i)
	{
		if (vecReservation[i].Reservation == 1)
		{
			vecRoom.push_back(vecReservation[i].ID);
		}
	}

	sort(vecRoom.begin(), vecRoom.end());
	return vecRoom;

}
int Problem2(vector<DATA2>& vecData)
{
	vector<DATA2> vecTemp = vecData;

	int Count = 0;
	vector<DATA2>::iterator iter_1 = vecTemp.begin();
	

	for ( ; iter_1 != vecTemp.end(); ++iter_1)
	{
		vector<DATA2>::iterator iter_2 = vecTemp.begin();
		for (; iter_2 != vecTemp.end(); ++iter_2 )
		{
			if (iter_1->Num1 == iter_2->Num2 &&
				iter_1->Num2 == iter_2->Num1)
			{
				++Count;
				vecTemp.erase(iter_2);
				break;
			}
		}
	}

	return Count;

}
int Problem3(vector<DATA3> vecTemp)
{
	vector<DATA3> vecData;

	for (int i = 0; i < vecTemp.size() ; ++i)
	{
		bool isCheck = false;

		if (vecData.size() == 0)
		{
			vecData.push_back(vecTemp[i]);
		}
			
		for (int j = 0 ; j < vecData.size() ; ++j)
		{
			if (vecData[j].X == vecTemp[i].X &&
				vecData[j].Y == vecTemp[i].Y)
			{
				isCheck = true;
				break;
			}
		}

		if (!isCheck)
		{
			vecData.push_back(vecTemp[i]);
		}
	}
	
	return vecData.size();
}
int Problem4(int n , int x , int y)
{

	vector<vector<int>> vecN;
	int G = 0;
	int A = 0;
	int B = 1;
	int Count = 1;
	bool isUp = true;
	for (int i = 0 ;i < n ; ++i)
	{
		vector<int> vecTemp(n);
		vecN.push_back(vecTemp);
	}

	for (int i = 0; i < (n * 2) - 1 ; ++i)
	{
		if (i == 0)
		{
			vecN[0][0] = Count;
			++Count;
			G = 2;
		}
		else
		{
			if (isUp)
			{
				if (G % 2 == 0)	//짝수
				{
					A = 0;
					B = G - 1;
				}
				else if (G % 2 == 1) //홀수
				{
					A = G - 1;
					B = 0;
				}
				for (int a = 0; a < G; ++a)
				{
					vecN[A][B] = Count;
					++Count;
					if (G % 2 == 0)	//짝수
					{
						++A;
						--B;
					}
					else if (G % 2 == 1) //홀수
					{
						--A;
						++B;
					}
				}
				++G;
				if (G > n)
				{
					G -= 2;
					isUp = false;
				}
					
			}
			else if (!isUp)
			{
				if (G % 2 == 0)	//짝수
				{
					A = (i + 1) - n;
					B = n - 1;
				}
				else if (G % 2 == 1) //홀수
				{
					A = n - 1;
					B = (i + 1) - n;
				}
				for (int a = 0; a < G; ++a)
				{
					vecN[A][B] = Count;
					++Count;
					if (G % 2 == 0)	//짝수
					{
						++A;
						--B;
					}
					else if (G % 2 == 1) //홀수
					{
						--A;
						++B;
					}
				}
				--G;
			}
		}
	}
	return vecN[x - 1][y - 1];
}
void JigZegMatrix();
int main()
{
	//방 예약 문제
	//	vector<DATA> vecData;
	//	DATA tData;
	//	tData.ID = 1;
	//	tData.Reservation = 0;
	//	vecData.push_back(tData);

	//	tData.ID = 2;
	//	tData.Reservation = 1;
	//	vecData.push_back(tData);

	//	tData.ID = 3;
	//	tData.Reservation = 1;
	//	vecData.push_back(tData);

	//	tData.ID = 2;
	//	tData.Reservation = 0;
	//	vecData.push_back(tData);

	//	tData.ID = 1;
	//	tData.Reservation = 1;
	//	vecData.push_back(tData);

	//	vector<int> vecTemp = Problem1(vecData, 3);
	//	for (int i = 0; i < vecTemp.size(); ++i)
	//	{
	//		if (vecTemp[i] == INT_MAX)
	//			cout << "빈방" << endl;
	//		else
	//			cout << vecTemp[i] << "번 손님 은 " << i + 1 << "번 방" << endl;
	//	}

	//이벤트 문제
	//vector<DATA2> vecData2;
	//DATA2 tData2;
	//tData2.Num1 = 1;
	//tData2.Num2 = 3;
	//vecData2.push_back(tData2);

	//tData2.Num1 = 3;
	//tData2.Num2 = 1;
	//vecData2.push_back(tData2);

	//tData2.Num1 = 3;
	//tData2.Num2 = 5;
	//vecData2.push_back(tData2);

	//tData2.Num1 = 2;
	//tData2.Num2 = 5;
	//vecData2.push_back(tData2);

	//tData2.Num1 = 5;
	//tData2.Num2 = 3;
	//vecData2.push_back(tData2);

	//int Count = Problem2(vecData2);
	//cout << Count << "그룹이 서로 선호" << endl;

	//콘서트관람 문제	
	/*vector<DATA3> vecTemp;
	DATA3 tData3;
	tData3.X = 10;
	tData3.Y = 10;
	vecTemp.push_back(tData3);

	tData3.X = 20;
	tData3.Y = 20;
	vecTemp.push_back(tData3);

	tData3.X = 30;
	tData3.Y = 30;
	vecTemp.push_back(tData3);

	tData3.X = 40;
	tData3.Y = 40;
	vecTemp.push_back(tData3);

	tData3.X = 10;
	tData3.Y = 10;
	vecTemp.push_back(tData3);

	tData3.X = 20;
	tData3.Y = 20;
	vecTemp.push_back(tData3);

	cout << Problem3(vecTemp) << endl;*/

	//cout << Problem4(5, 3, 2) << endl;
	
	//지그재그행렬
	JigZegMatrix();
	return 0;
}
void JigZegMatrix()
{
	const long long countmat = 5;
	long long mat[countmat][countmat];
	long long countNum = 2;
	long long pickrow = 3;
	long long pickcol = 3;

	mat[0][0] = 1;
	mat[countmat - 1][countmat - 1] = countmat * countmat;

	while (countNum <= countmat)
	{
		//중간지점에 도달할때 까지
		long long plusCount = mat[0][0] + ((countNum*countNum) - countNum) / 2;

		//짝수
		if (countNum % 2 == 0)
		{
			mat[0][countNum - 1] = plusCount;
			for (size_t i = 1; i < countNum; i++)
			{
				mat[i][(countNum - 1) - i] = ++plusCount;
			}
		}
		//홀수
		else if (countNum % 2 == 1)
		{
			mat[countNum - 1][0] = plusCount;
			for (size_t i = 1; i < countNum; i++)
			{
				mat[(countNum - 1) - i][i] = ++plusCount;
			}
		}
		++countNum;
	}
	countNum = 2;
	int countNum2 = countmat - 1;
	while (countNum <= countmat)
	{
		//중간지점에 도달할때 까지
		long long minusCount = mat[countmat - 1][countmat - 1] + (-(countNum*countNum) + (countNum)) / 2;

		//짝수
		if (countNum % 2 == 0)
		{
			mat[countmat - 1][countNum2 - 1] = minusCount;
			/*for (size_t i = 1; i <= countmat - countNum; i++)
			{
			mat[(countNum - 1) + i][(countmat - 1) - i] = ++minusCount;
			}*/

			for (size_t i = 1; i < countNum; i++)
			{
				mat[(countmat - 1) - i][(countNum2 - 1) + i] = --minusCount;
			}
		}
		//홀수
		else if (countNum % 2 == 1)
		{
			mat[countNum2 - 1][countmat - 1] = minusCount;
			/*for (size_t i = 1; i <= countmat - countNum; i++)
			{
			mat[(countmat - 1) - i][(countNum - 1) + i] = ++minusCount;
			}*/
			for (size_t i = 1; i < countNum; i++)
			{
				mat[(countNum2 - 1) + i][(countmat - 1) - i] = --minusCount;
			}
		}
		--countNum2;
		++countNum;
	}

	cout << "선택한 녀석의 값은" << mat[pickrow - 1][pickcol - 1] << endl;
}
