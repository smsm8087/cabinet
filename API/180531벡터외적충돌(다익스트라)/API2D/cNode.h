#pragma once
class cNode
{
protected:
	COLORREF	m_dwColor;
	
protected:
	//겟셋매크로 (타입 , 변수명 , 함수이름)
	GETSET(cVector2, m_vPos, Pos);
	GETSET(int, m_nNodeNum, NodeNum);

public:
	cNode();
	//~cNode();*/
	cNode(const cVector2& pt, int n);
	virtual ~cNode();
	
	void Update();
	void Render(HDC hdc);
	void SaveToFile(FILE* fp);
	bool IsPicked(const POINT& pt);
};

