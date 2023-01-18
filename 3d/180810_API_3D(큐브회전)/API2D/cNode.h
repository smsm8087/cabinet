#pragma once

class cNode
{
protected:

public:
	cNode();
	virtual ~cNode();
	
	RECT			m_rcNode;
	cNode*			m_aChild[4];
	vector<RECT*>	m_vecObstacle;
	int				m_nNodeSize;

	cNode* GetNodeAt(RECT& rc);
	void BuildNode(int nNodeSize, vector<RECT>& vecObstacle, vector<cNode*>& vecLeafNode);
	void Update();
	void Render(HDC hdc, RECT& rc);
};

