#pragma once
#include "cNode.h"

class cMainGame
{
private:
	enum
	{
		E_LEFT	= 1 << 0,
		E_RIGHT = 1 << 1,
		E_UP	= 1 << 2,
		E_DOWN	= 1 << 3,
	};
	
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	ULONG_PTR		m_ulGdiplusToken;

	vector<cNode*>	m_vecNode;
	set<cNode*>		m_setOpenList;
	vector<int>		m_vecDirection;
	map<int, float> m_mapDistance;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void FindPath();
	cNode* FindNode(cNode::eNodeType eNodeType);
	cNode* MinFNodeAtOpenList();
	float GetHeuristic(cNode* n1, cNode* n2);
	void Extend(cNode* pExtNode, cNode* pDest);
	cNode* GetAdjNode(cNode* pExtNode, int nDir);
};

