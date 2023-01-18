#pragma once
class cNode
{
protected:
	COLORREF	m_dwColor;

protected:
	GETSET(int, m_nRow, Row);
	GETSET(int, m_nCol, Col);
	GETSET(cNode*, m_pPrev, Prev);

public:
	void UpdateRowCol(cNode* pOutNode, eDir e);
	bool IsCollision(cNode* pNode);
	void RandomRowCol();
	void SetColor(COLORREF c);
/*
protected:
	cNode*	m_pPrev;
public:
	cNode* GetPrev()
	{
		return m_pPrev;
	}
	void SetPrev(cNode* pPrev)
	{
		m_pPrev = pPrev;
	}
*/
public:
	cNode(int nRow = 0, int nCol = 0, cNode* pPrev = NULL);
	virtual ~cNode();
	
	void Update();
	void Render(HDC hdc);
	void SaveToFile(FILE* fp);
};

