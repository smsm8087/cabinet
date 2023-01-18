#include "stdafx.h"
#include "cNode.h"

cNode::cNode()
{
	m_aChild[0] = NULL;
	m_aChild[1] = NULL;
	m_aChild[2] = NULL;
	m_aChild[3] = NULL;
}

cNode::~cNode()
{
}

cNode * cNode::GetNodeAt(RECT & rc)
{
	RECT rcIntersect;
	if (IntersectRect(&rcIntersect, &m_rcNode, &rc))
	{
		if (m_aChild[0])
		{
			cNode* pNode = NULL;
			for (size_t i = 0; i < 4; i++)
			{
				pNode = m_aChild[i]->GetNodeAt(rc);
				if (pNode) break;
			}
			return pNode;
		}
		else
		{
			return this;
		}
	}
	return nullptr;
}

void cNode::BuildNode(int nNodeSize, vector<RECT>& vecObstacle, vector<cNode*>& vecLeafNode)
{
	if (nNodeSize < 1024) return;
	
	static int n = 0;
	if (n > 65536)
	{
		OutputDebugString((to_string(++n) + "\n").c_str());
	}
	
	m_nNodeSize = nNodeSize;

	if (nNodeSize == 1024)
	{
		vecLeafNode.push_back(this);
	}
	else
	{
		int x = m_rcNode.left;
		int y = m_rcNode.top;
		int w = (m_rcNode.right - m_rcNode.left) / 2;
		int h = (m_rcNode.bottom - m_rcNode.top) / 2;

		m_aChild[0] = new cNode();
		m_aChild[0]->m_rcNode = cUtil::MakeRect(x, y, w, h);
		m_aChild[0]->BuildNode(nNodeSize / 2, vecObstacle, vecLeafNode);

		m_aChild[1] = new cNode();
		m_aChild[1]->m_rcNode = cUtil::MakeRect(x + w, y, w, h);
		m_aChild[1]->BuildNode(nNodeSize / 2, vecObstacle, vecLeafNode);

		m_aChild[2] = new cNode();
		m_aChild[2]->m_rcNode = cUtil::MakeRect(x, y + h, w, h);
		m_aChild[2]->BuildNode(nNodeSize / 2, vecObstacle, vecLeafNode);

		m_aChild[3] = new cNode();
		m_aChild[3]->m_rcNode = cUtil::MakeRect(x + w, y + h, w, h);
		m_aChild[3]->BuildNode(nNodeSize / 2, vecObstacle, vecLeafNode);
	}
}

void cNode::Update()
{
}

void cNode::Render(HDC hdc, RECT& rc)
{
	RECT rcIntersect;
	if (IntersectRect(&rcIntersect, &m_rcNode, &rc))
	{
		for (size_t i = 0; i < m_vecObstacle.size(); i++)
		{
			FillRect(hdc, m_vecObstacle[i], GetSysColorBrush(COLOR_WINDOW/*COLOR_WINDOW*/));
		}
	}
	else
	{
		return;
	}

	for (size_t i = 0; i < 4; i++)
	{
		if(m_aChild[i])
			m_aChild[i]->Render(hdc, rc);
	}
}

