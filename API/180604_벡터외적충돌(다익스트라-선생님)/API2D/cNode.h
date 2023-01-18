#pragma once
class cNode
{
protected:
	COLORREF	m_dwColor;
	
protected:
	GETSET(cVector2, m_vPos, Pos);
	GETSET(int, m_nNodeNum, NodeNum);

public:
	cNode(const cVector2& pt, int n);
	virtual ~cNode();
	
	void Update();
	void Render(HDC hdc);
	void SaveToFile(FILE* fp);
	bool IsPicked(const POINT& pt);
};

