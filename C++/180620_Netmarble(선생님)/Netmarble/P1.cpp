#include "stdafx.h"
#include "P1.h"


P1::P1()
{
}


P1::~P1()
{
}

void P1::Excute(int nNodeNum, int aEdge[][2], int nEdgeNum)
{
	vector<ST_NODE> vecNode(nNodeNum);

	for (size_t i = 0; i < nNodeNum; i++)
	{
		vecNode[i].nNodeNo = i + 1;
		vecNode[i].nNumFriend = 0;
		vecNode[i].isVisited = false;
		vecNode[i].isCounting = false;
	}

	for (size_t i = 0; i < nEdgeNum; i++)
	{
		int n1 = aEdge[i][0] - 1;
		int n2 = aEdge[i][1] - 1;
		vecNode[n1].vecAdjNode.push_back(&vecNode[n2]);
		vecNode[n2].vecAdjNode.push_back(&vecNode[n1]);
	}

	vecNode[0].isVisited = true;
	DFS(&vecNode[0]);
	
	for (size_t i = 0; i < nNodeNum; i++)
	{
		printf("%d 의 친구 수 : %d\n", vecNode[i].nNodeNo, vecNode[i].nNumFriend);
	}
}

void P1::DFS(ST_NODE * pNode)
{
	pNode->isCounting = true;
	pNode->nNumFriend = CountFriend(pNode, 0);
	pNode->isCounting = false;

	//printf("%d\n", pNode->nNodeNo);
	for (size_t i = 0; i < pNode->vecAdjNode.size(); i++)
	{
		if (pNode->vecAdjNode[i]->isVisited) continue;
		pNode->vecAdjNode[i]->isVisited = true;
		DFS(pNode->vecAdjNode[i]);
	}
}

int P1::CountFriend(ST_NODE * pNode, int nLevel)
{
	if (nLevel == 2) return 1;

	int nNumFriend = (nLevel == 0) ? 0 : 1;

	for (size_t i = 0; i < pNode->vecAdjNode.size(); i++)
	{
		if (pNode->vecAdjNode[i]->isCounting) continue;
		pNode->vecAdjNode[i]->isCounting = true;
		nNumFriend += CountFriend(pNode->vecAdjNode[i], nLevel + 1);
		pNode->vecAdjNode[i]->isCounting = false;
	}
	return nNumFriend;
}
