#pragma once

struct ST_NODE
{
	int					nNodeNo;
	int					nNumFriend;
	bool				isVisited;
	bool				isCounting;
	vector<ST_NODE*>	vecAdjNode;
};

class P1
{
public:
	P1();
	~P1();
	
	void Excute(int nNodeNum, int aEdge[][2], int nEdgeNum);
	void DFS(ST_NODE* pNode);
	int CountFriend(ST_NODE* pNode, int nLevel);
};


