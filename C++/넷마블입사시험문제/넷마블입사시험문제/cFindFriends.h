#pragma once
class cFindFriends
{
private:
	int m_Friend; //친구총 수
	int m_Friend2; //친구총 수

	int m_N;         //정점의 수

	vector<int> m_vecFriend;
	map<int, vector<int>> m_mapFriend;
	map<int, vector<int>>::iterator m_imapFriend;
public:
	cFindFriends();
	~cFindFriends();

	void Init();
	void Update();
};