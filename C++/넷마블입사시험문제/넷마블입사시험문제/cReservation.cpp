#include "stdafx.h"
#include "cReservation.h"
//n���� �濡 ���Ǵ�� �����û��  �� ����
//����� ���ٸ� ����� ��ܿ� ��.
//���� �������ִ� ���� ���� ��Ҹ� �ϸ� ����� ��� 1���� ���� ���� ��������.
//�����޾Ҵ� ���� ����� �ٽ� �����û�� �Ѵٸ� ����� ����� ���� �������� ��.
//����� ����� ���� ������Ҹ� �Ѵٸ� ����� ��ܿ��� ���� �׸��� ����� ���� �ڿ� �ִ�
//������ ������ 1ĭ�� �����.
//����� ��ܿ��� ������ ���� �ٽ� �����û�� �Ѵٸ� ����� ����� ���� �������� ��.
//
//---- - �ʿ��Ѱ�
//���� ���̵�� ���� ��û ���ΰ� ������� ����ִ� �迭
//����� ��Ÿ���� �Ű������� �־����� ������ ���� ��û ��� ��û�� ������� ��� ó���� ��
//���������� ���� �������� ������ ID�� ����ִ� �迭�� ������������ �����Ͽ� Return �ϵ���
//�Լ��� �ϼ��� �ּ���.
//
//��, �̹� �����Ͽ� ���� ���� ���̳� ����� ��ܿ� �ִ� ���� �ٽ� �����û�ϴ� ����
//
//�� ���� ����ڸ�� ��𿡵� ���� ���� �� ������ ����ϴ� ���� �Է����� �־����� �ʽ��ϴ�.

cReservation::cReservation()
{
	//2�� ���� ��� 4�� �������
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
