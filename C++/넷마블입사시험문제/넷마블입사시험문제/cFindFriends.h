#pragma once
class cFindFriends
{
private:
	int m_Friend; //ģ���� ��
	int m_Friend2; //ģ���� ��

	int m_N;         //������ ��

	vector<int> m_vecFriend;
	map<int, vector<int>> m_mapFriend;
	map<int, vector<int>>::iterator m_imapFriend;
public:
	cFindFriends();
	~cFindFriends();

	void Init();
	void Update();
};