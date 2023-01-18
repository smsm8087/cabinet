#include "stdafx.h"
#include "cFindFriends.h"

/*
5
1,2            1�̶� 2�� ģ�� 2�̶� 4�� ģ�� 5�� 4�� ģ�� 3�̶� 1�� ģ��
2,4
5,4
3,1
*/

cFindFriends::cFindFriends()
	:m_Friend(0)
	, m_Friend2(0)
	, m_N(0)
{


}


cFindFriends::~cFindFriends()
{
}

void cFindFriends::Init()
{


}

void cFindFriends::Update()
{
	FILE* fp = NULL;
	fopen_s(&fp, "1.txt", "r");
	fscanf_s(fp, "%d\n", &m_N);

	for (int i = 1; i <= m_N; i++)
	{
		m_mapFriend.insert(pair<int, vector<int>>(i, vector<int>()));
	}
	int count = 0;
	while (!feof(fp))
	{
		fscanf_s(fp, "(%d,%d)\n", &m_Friend, &m_Friend2);

		m_mapFriend[m_Friend].push_back(m_Friend2);
		m_mapFriend[m_Friend2].push_back(m_Friend);
		count++;
	}

	fclose(fp);

	for (auto m : m_mapFriend)
	{
		if (m.second.front() == m.second.back())
		{
			cout << m.first << "�� ģ����  " << m.second.front();
		}
		else
		{
			cout << m.first << "�� ģ����  " <<
				m.second.front() << " �� " <<
				m.second.back();
		}

		for (int i = 0; i < m.second.size(); i++)
		{

			if (m.first != m_mapFriend[m.second[i]].front() ||
				m.first != m_mapFriend[m.second[i]].back())
			{
				if (m.first == m_mapFriend[m.second[i]].back())
				{
					cout << " �� " << m_mapFriend[m.second[i]].front();
				}
				if (m.first == m_mapFriend[m.second[i]].front())
				{
					cout << " �� " << m_mapFriend[m.second[i]].back();
				}
			}
		}
		cout << endl;
	}
	/*
	m.first ģ���� ã�Ҵ��� 2�� 3�ε� 2��
	2�� ���µ� ģ���� 1�� 4��.
	1�� ���� 4�� ���Ƽ� 4�� �߰��Ѵ�.
	*/
}