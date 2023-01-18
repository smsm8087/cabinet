#pragma once
#include "cVector2.h"
#include <vector>

class cNode {
private:
	int			m_nNum;
	cVector2	m_vPos;
	float		m_fRadius;

public:
	cNode();
	~cNode();

	void Init(int num, cVector2 pos, float radius);
	void Render(HDC hdc);
	void AddEdge(cNode* node);
	int GetNodeNum();
	int GetEdgesSize();
	cVector2 GetNodePos();

	vector<cNode*>	m_vecEdges;
};

