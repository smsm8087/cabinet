#include "stdafx.h"
#include "cNode.h"

cNode::cNode()
{
}

cNode::~cNode()
{
}

void cNode::Init(int nIndex, eNodeType eType)
{
	m_nIndex = nIndex;
	m_nRow = nIndex / TILE_N;
	m_nCol = nIndex % TILE_N;
	m_eNodeType = eType;
	F = 0.0f;
	G = 0.0f;
	H = 0.0f;
	m_pParent = NULL;
	m_eNodeState = E_NONE;
}

void cNode::Update()
{
}

void cNode::Render(HDC hdc)
{
	Graphics g(hdc);
	Pen p(&SolidBrush(Color::Black));
	Rect rc(m_nCol * 50, m_nRow * 50, 50, 50);

	
	if (m_eNodeType == E_EMPTY)
		g.FillRectangle(&SolidBrush(Color::White), rc);
	else if (m_eNodeType == E_WALL)
		g.FillRectangle(&SolidBrush(Color::Gray), rc);

	if (m_eNodeState == E_OPEN)
		g.FillRectangle(&SolidBrush(Color::Green), rc);
	else if (m_eNodeState == E_CLOSE)
		g.FillRectangle(&SolidBrush(Color::Red), rc);

	if (m_eNodeType == E_PATH)
		g.FillRectangle(&SolidBrush(Color::Yellow), rc);

	g.DrawRectangle(&p, rc);

	if (true)
	{

		//g.DrawRectangle(&p, rc);
	}
}

