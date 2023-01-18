#include "stdafx.h"
#include "cMainGame.h"
#include "cNode.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
{
}

cMainGame::~cMainGame()
{
	for (auto p : m_vecNode)
	{
		SAFE_DELETE(p);
	}

	m_vecNode.clear();

	g_pTimeManager->Destroy();

	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);

	map<char, cNode::eNodeType> mapNodeType;
	mapNodeType['E'] = cNode::E_EMPTY;
	mapNodeType['W'] = cNode::E_WALL;
	mapNodeType['S'] = cNode::E_START;
	mapNodeType['D'] = cNode::E_DEST;

	m_vecDirection.push_back(E_LEFT);
	m_vecDirection.push_back(E_RIGHT);
	m_vecDirection.push_back(E_UP);
	m_vecDirection.push_back(E_DOWN);
	m_vecDirection.push_back(E_LEFT | E_UP);
	m_vecDirection.push_back(E_LEFT | E_DOWN);
	m_vecDirection.push_back(E_RIGHT | E_UP);
	m_vecDirection.push_back(E_RIGHT | E_DOWN);


	m_mapDistance[E_LEFT] = 1.0f;
	m_mapDistance[E_RIGHT] = 1.0f;
	m_mapDistance[E_UP] = 1.0f;
	m_mapDistance[E_DOWN] = 1.0f;
	m_mapDistance[E_LEFT | E_UP] = sqrt(2.0f);
	m_mapDistance[E_LEFT | E_DOWN] = sqrt(2.0f);
	m_mapDistance[E_RIGHT | E_UP] = sqrt(2.0f);
	m_mapDistance[E_RIGHT | E_DOWN] = sqrt(2.0f);


	FILE* fp = NULL;
	fopen_s(&fp, "astar.txt", "r");
	while (!feof(fp))
	{
		char c = fgetc(fp);
		if (c < 33) continue;
		cNode* pNode = new cNode;
		pNode->Init(m_vecNode.size(), mapNodeType[c]);
		m_vecNode.push_back(pNode);
	}
	fclose(fp);

	FindPath();
	RECT rc;
	GetClientRect(g_hWnd, &rc);
}


void cMainGame::Update()
{
	g_pTimeManager->Update();
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (m_hMemDC == NULL)
	{
		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
		SetGraphicsMode(m_hMemDC, GM_ADVANCED);
	}

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT/*COLOR_WINDOW*/));
	
	Graphics g(m_hMemDC);
	Pen p(&SolidBrush(Color::Red));

	for (auto p : m_vecNode)
	{
		p->Render(m_hMemDC);
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}

void cMainGame::OnSize()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_RBUTTONDOWN:
	{
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	}
}

void cMainGame::FindPath()
{
	cNode* pStart = FindNode(cNode::E_START);
	cNode* pDest = FindNode(cNode::E_DEST);
	
	pStart->G = 0.0f;
	pStart->H = GetHeuristic(pStart, pDest);
	pStart->F = pStart->G + pStart->H;
	pStart->m_eNodeState = cNode::E_OPEN;

	m_setOpenList.insert(pStart);

	while (true)
	{
		cNode* pExtNode = MinFNodeAtOpenList();
		if (pExtNode == NULL)
		{
			// 경로 없음
			break;
		}

		m_setOpenList.erase(pExtNode);
		pExtNode->m_eNodeState = cNode::E_CLOSE;

		Extend(pExtNode, pDest);

		if (pExtNode == pDest)
		{
			// 경로 찾음
			break;
		}
	}

	cNode* pNode = pDest;
	while (pNode)
	{
		pNode->m_eNodeType = cNode::E_PATH;
		pNode = pNode->m_pParent;
	}
}

cNode * cMainGame::FindNode(cNode::eNodeType eNodeType)
{
	for (auto p : m_vecNode)
	{
		if (p->m_eNodeType == eNodeType)
			return p;
	}
	return nullptr;
}

cNode * cMainGame::MinFNodeAtOpenList()
{
	float fMinF = FLT_MAX;
	cNode* pNode = nullptr;
	for (auto p : m_setOpenList)
	{
		if (p->F < fMinF)
		{
			pNode = p;
			fMinF = p->F;
		}
	}
	return pNode;
}

float cMainGame::GetHeuristic(cNode * n1, cNode * n2)
{
	return fabs(n1->m_nRow - n2->m_nRow) +
		fabs(n1->m_nCol - n2->m_nCol);
}

void cMainGame::Extend(cNode * pExtNode, cNode * pDest)
{
	for (int nDir : m_vecDirection)
	{
		cNode* pAdjNode = GetAdjNode(pExtNode, nDir);
		if (pAdjNode == NULL) continue;
		if (pAdjNode->m_eNodeState == cNode::E_OPEN)
		{
			if (pAdjNode->G > pExtNode->G + m_mapDistance[nDir])
			{
				pAdjNode->G = pExtNode->G + m_mapDistance[nDir];
				//pAdjNode->H = GetHeuristic(pAdjNode, pDest);
				pAdjNode->F = pAdjNode->G + pAdjNode->H;
				//pAdjNode->m_eNodeState = cNode::E_OPEN;

				pAdjNode->m_pParent = pExtNode;

				//m_setOpenList.insert(pAdjNode);
			}
		}
		else
		{
			pAdjNode->G = pExtNode->G + m_mapDistance[nDir];
			pAdjNode->H = GetHeuristic(pAdjNode, pDest);
			pAdjNode->F = pAdjNode->G + pAdjNode->H;
			pAdjNode->m_eNodeState = cNode::E_OPEN;
			
			pAdjNode->m_pParent = pExtNode;

			m_setOpenList.insert(pAdjNode);
		}
	}
}

cNode * cMainGame::GetAdjNode(cNode * pExtNode, int nDir)
{
	int nAdjRow = pExtNode->m_nRow;
	int nAdjCol = pExtNode->m_nCol;
	if (nDir & E_UP)
	{
		if(pExtNode->m_nRow == 0) return NULL;
		int nIndex = pExtNode->m_nIndex - TILE_N;
		if (m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL) return NULL;
		nAdjRow -= 1;
	}
	else if (nDir & E_DOWN)
	{
		if (pExtNode->m_nRow == TILE_N - 1) return NULL;
		int nIndex = pExtNode->m_nIndex + TILE_N;
		if (m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL) return NULL;
		nAdjRow += 1;
	}

	if (nDir & E_LEFT)
	{
		if (pExtNode->m_nCol == 0) return NULL;
		int nIndex = pExtNode->m_nIndex - 1;
		if (m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL) return NULL;
		nAdjCol -= 1;
	}
	else if (nDir & E_RIGHT)
	{
		if (pExtNode->m_nCol == TILE_N - 1) return NULL;
		int nIndex = pExtNode->m_nIndex + 1;
		if (m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL) return NULL;
		nAdjCol += 1;
	}

	int nIndex = nAdjRow * TILE_N + nAdjCol;
	if (m_vecNode[nIndex]->m_eNodeType == cNode::E_WALL) return NULL;
	if (m_vecNode[nIndex]->m_eNodeState == cNode::E_CLOSE) return NULL;
	return m_vecNode[nIndex];
}
