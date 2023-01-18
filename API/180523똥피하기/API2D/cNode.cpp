#include "stdafx.h"
#include "cNode.h"


void cNode::UpdateRowCol(cNode* pOutNode, eDir e)
{
	if (e == eDir::E_UP)
	{
		pOutNode->m_nCol = m_nCol;
		pOutNode->m_nRow = m_nRow - 1;
		if (pOutNode->m_nRow < 0)
		{
			pOutNode->m_nRow = NUM_TILE - 1;
		}
	}
	else if (e == eDir::E_DOWN)
	{
		pOutNode->m_nCol = m_nCol;
		pOutNode->m_nRow = m_nRow + 1;
		pOutNode->m_nRow %= NUM_TILE;
	}
	else if (e == eDir::E_LEFT)
	{
		pOutNode->m_nRow = m_nRow;
		pOutNode->m_nCol = m_nCol - 1;
		if (pOutNode->m_nCol < 0)
		{
			pOutNode->m_nCol = NUM_TILE - 1;
		}
	}
	else if (e == eDir::E_RIGHT)
	{
		pOutNode->m_nRow = m_nRow;
		pOutNode->m_nCol = m_nCol + 1;
		pOutNode->m_nCol %= NUM_TILE;
	}
}

bool cNode::IsCollision(cNode * pNode)
{
	return m_nRow == pNode->m_nRow && m_nCol == pNode->m_nCol;
}

void cNode::RandomRowCol()
{
	m_nRow = rand() % NUM_TILE;
	m_nCol = rand() % NUM_TILE;
}

void cNode::SetColor(COLORREF c)
{
	m_dwColor = c;
}

cNode::cNode(int nRow, int nCol, cNode* pPrev)
	: m_nRow(nRow)
	, m_nCol(nCol)
	, m_pPrev(pPrev)
	, m_dwColor(RGB(0, 255, 0))
{
}

cNode::~cNode()
{
}

void cNode::Update()
{
}

void cNode::Render(HDC hdc)
{
	HBRUSH hBrush, hOldBrush;
	hBrush = CreateSolidBrush(m_dwColor);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Rectangle(hdc,
		m_nCol * SQUARE_SIZE,
		m_nRow * SQUARE_SIZE,
		(m_nCol + 1) * SQUARE_SIZE,
		(m_nRow + 1) * SQUARE_SIZE);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
}

void cNode::SaveToFile(FILE * fp)
{
	fprintf_s(fp, "%d %d\n", m_nRow, m_nCol);
}


