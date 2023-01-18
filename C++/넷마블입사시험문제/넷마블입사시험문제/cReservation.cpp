#include "stdafx.h"
#include "cReservation.h"
//n개의 방에 임의대로 예약신청한  고객 배정
//빈방이 없다면 대기자 명단에 들어감.
//방을 가지고있는 고객이 예약 취소를 하면 대기자 명단 1번의 고객이 방을 배정받음.
//배정받았던 고객이 취소후 다시 예약신청을 한다면 대기자 명단의 가장 마지막에 들어감.
//대기자 명단의 고객이 예약취소를 한다면 대기자 명단에서 삭제 그리고 취소한 고객의 뒤에 있던
//고객들의 순번이 1칸씩 당겨짐.
//대기자 명단에서 삭제된 고객이 다시 예약신청을 한다면 대기자 명단의 가장 마지막에 들어감.
//
//---- - 필요한것
//고객의 아이디와 예약 신청 여부가 순서대로 들어있는 배열
//빈방을 나타내는 매개변수가 주어질때 고객들의 예약 신청 취소 요청을 순서대로 모두 처리한 후
//최종적으로 방을 배정받은 고객들의 ID가 들어있는 배열을 오름차순으로 정렬하여 Return 하도록
//함수를 완성해 주세요.
//
//단, 이미 예약하여 방을 받은 고객이나 대기자 명단에 있는 고객이 다시 예약신청하는 경우와
//
//방 배정 대기자명단 어디에도 없는 고객이 방 배정을 취소하는 경우는 입력으로 주어지지 않습니다.

cReservation::cReservation()
{
	//2번 예약 취소 4번 예약취소
	Reservation r[6];
	r[0].iscancel = false;
	r[1].iscancel = true;
	r[2].iscancel = false;
	r[3].iscancel = true;
	r[4].iscancel = false;
	r[5].iscancel = false;

	r[0].name = 'a';
	r[1].name = 'b';
	r[2].name = 'c';
	r[3].name = 'd';
	r[4].name = 'e';
	r[5].name = 'f';
	for (size_t i = 0; i < 6; i++)
	{
		m_veccustomer.push_back(r[i]);
	}
	

}


cReservation::~cReservation()
{
}

void cReservation::Excute(int roomNum/*, vector<Reservation> customer*/)
{
	auto iter = m_veccustomer.begin();
	
	for (iter; iter != m_veccustomer.end(); )
	{
		if ((*iter).iscancel == false)
		{
			if (m_vecRoom.size() > roomNum)break;
			m_vecRoom.push_back(1);
			iter++;
		}
		else
		{
			//m_veccustomer.push_back(*iter);
			iter = m_veccustomer.erase(iter);
		}
	}
	m_vecRoom = m_vecRoom;
	m_veccustomer = m_veccustomer;
}
