#include "stdafx.h"
#include "cMainGame.h"
#include "cScv.h"
#include"cCommandCenter.h"
#include"cMineral.h"
cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	,m_commandcenter(new cCommandCenter)
	,fp(nullptr)
	,isDrag(false)
	,isRbt(false)
	,RbtnCount(0)
	,count(0)
	,Start(0)
	,Dest(0)
	,isScvgoing(false)
	,v_start(0,0)
	,v_dest(0,0)
	, m_fSpeed(200.0f)
{
	Col = 0;
	Row = 0;
	wall.Tilesize = 0;
	wall.WallCount = 0;
	wall.pt.x = 0;
	wall.pt.y = 0;
	wall.rowindex = 0;
	wall.colindex = 0;
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	SAFE_DELETE(m_commandcenter);
}

void cMainGame::Init()
{
	
	
	//Drag
	for (size_t i = 0; i < 4; i++)
	{
		ptDrag[i].x = 0;
		ptDrag[i].y = 0;
	}
	/////FILE input output
	fopen_s(&fp, "data.txt", "r");
	if (fp == nullptr)return;
	fscanf_s(fp, "%d", &wall.Tilesize);
	fscanf_s(fp, "%d", &Row);
	fscanf_s(fp, "%d", &Col);
	fscanf_s(fp, "%d", &wall.WallCount);

	Tile_size = wall.Tilesize;
	m_nScore = 0;

	for (size_t i = 0; i <wall.WallCount; i++)
	{
		fscanf_s(fp, "%d", &wall.rowindex);
		fscanf_s(fp, "%d", &wall.colindex);
		
		wall.pt.x = wall.rowindex * wall.Tilesize;
		wall.pt.y = wall.colindex * wall.Tilesize;

		wall.walltype =eNodeType::E_WALL;
		m_vecWall.push_back(wall);
	}
	for (size_t i = 0; i < Row; i++)
	{
		for (size_t j = 0; j < Col; j++)
		{
			Wall tile;
			tile.WallCount = Row * Col;
			tile.rowindex = i;
			tile.colindex = j;
			tile.Tilesize = Tile_size;
			
			tile.pt.x = i * Tile_size;
			tile.pt.y = j * Tile_size;

			tile.Tileindex = i * Row + j;
			tile.walltype = eNodeType::E_EMPTY;
			for (auto p : m_vecWall)
			{
				if (p.rowindex == tile.rowindex && p.colindex == tile.colindex)
				{
					tile.walltype = eNodeType::E_WALL;
				}
			}
			m_vecAll_wall.push_back(tile);
		}
	}
	//astar
	map<int, eNodeType> mapNodeType;
	mapNodeType[0] = eNodeType::E_START;
	mapNodeType[1] = eNodeType::E_EMPTY;
	mapNodeType[2] = eNodeType::E_WALL;
	mapNodeType[3] = eNodeType::E_DEST;

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
	for (auto p : m_vecAll_wall)
	{
		cNode* pNode = new cNode;
		pNode->Init(p.Tileindex, mapNodeType[p.walltype]);
		m_vecNode.push_back(pNode);
	}
	
	////////////Starcraft
	//
	///////////////////////
	
	
	//COMMAND CENTER
	
	POINT pt;
	pt.x = 8;
	pt.y = 3;
	
	m_commandcenter->rc.left = pt.x * 32 ;
	m_commandcenter->rc.right = pt.x * 32 + m_commandcenter->m_nRadius;
	m_commandcenter->rc.top = pt.y * 32 ;
	m_commandcenter->rc.bottom = pt.y * 32 + m_commandcenter->m_nRadius;
	
	m_commandcenter->setm_pt(pt);
	m_vecCmdcenter.push_back(m_commandcenter);

	//SCV *4
	cScv*  scv[4];
	cVector2 v_pt[4];
	for (size_t i = 0; i < 4; i++)
	{
		scv[i] = new cScv;
		v_pt[i].x = 7.f + i;
		v_pt[i].y = 5.f;
		scv[i]->rc.left = v_pt[i].x * 32 ;
		scv[i]->rc.right = v_pt[i].x * 32 + scv[i]->m_nRadius;
		scv[i]->rc.top = v_pt[i].y * 32 ;
		scv[i]->rc.bottom = v_pt[i].y * 32 + scv[i]->m_nRadius;
		scv[i]->m_nmineral = 0;
		scv[i]->setm_pt(v_pt[i]);
		m_vecScv.push_back(scv[i]);
	}

	//Mineral *8
	cMineral  *near_mineral[4];
	cMineral  *far_mineral[4];
	POINT ptmineral[4];
	for (size_t i = 0; i < 4; i++)
	{
		//근처 미네랄
		near_mineral[i] = new cMineral;
		ptmineral[i].x = 14;
		ptmineral[i].y = 1 + i * 2;
		near_mineral[i]->rc.left = ptmineral[i].x * 32 ;
		near_mineral[i]->rc.right = ptmineral[i].x * 32 + near_mineral[i]->m_nRadius;
		near_mineral[i]->rc.top = ptmineral[i].y * 32;
		near_mineral[i]->rc.bottom = ptmineral[i].y * 32 + near_mineral[i]->m_nRadius;
		near_mineral[i]->m_num = i + 1;
		near_mineral[i]->isImpossible = false;
		
		near_mineral[i]->setm_pt(ptmineral[i]);
		m_vec_nearMineral.push_back(near_mineral[i]);

		//멀리있는미네랄
		far_mineral[i] = new cMineral;
		ptmineral[i].x = 1;
		ptmineral[i].y = 7 + i * 2;
		far_mineral[i]->rc.left = ptmineral[i].x * 32;
		far_mineral[i]->rc.right = ptmineral[i].x * 32 + far_mineral[i]->m_nRadius;
		far_mineral[i]->rc.top = ptmineral[i].y * 32;
		far_mineral[i]->rc.bottom = ptmineral[i].y * 32 + far_mineral[i]->m_nRadius;
		far_mineral[i]->m_num = i + 1;
		far_mineral[i]->isImpossible = false;
		far_mineral[i]->setm_pt(ptmineral[i]);
		m_vec_farMineral.push_back(far_mineral[i]);
	}
	
	
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	for (auto p : m_vecScv)
	{
		m_nScore += p->m_nmineral;
	}

	//왼쪽드래그
	RECT rcDrag;
	rcDrag.left = ptDrag[0].x;
	rcDrag.top = ptDrag[0].y;
	rcDrag.right = ptDrag[3].x;
	rcDrag.bottom = ptDrag[3].y;
	RECT rcTemp;
	if (isDrag)
	{
		isRbt = false;
		for (auto p : m_vecCmdcenter)
		{
			if (IntersectRect(&rcTemp, &rcDrag, &p->rc))
			{
				p->isSelected = true;
			}
			else
				p->isSelected = false;
		}
		//scv
		for (auto p : m_vecScv)
		{
			if (IntersectRect(&rcTemp, &rcDrag, &p->rc))
			{
				p->isSelected = true;
			}
			else
				p->isSelected = false;
		}
		//mineral
		for (auto p : m_vec_nearMineral)
		{
			if (IntersectRect(&rcTemp, &rcDrag, &p->rc))
			{
				p->isSelected = true;
			}
			else
				p->isSelected = false;
		}
		for (auto p : m_vec_farMineral)
		{
			if (IntersectRect(&rcTemp, &rcDrag, &p->rc))
			{
				p->isSelected = true;
			}
			else
				p->isSelected = false;
		}
	}
	
	//왼쪽클릭
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		isRbt = false;
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		//커맨드센터
		for (auto p : m_vecCmdcenter)
		{
			if (PtInRect(&p->rc, pt))
			{
				p->isSelected = true;
			}
			else
				p->isSelected = false;
		}
		//scv
		for (auto p : m_vecScv)
		{
			
			if (PtInRect(&p->rc, pt))
			{
				if (Start != -1)
					m_vecNode[Start]->m_eNodeType = E_EMPTY;
				p->isSelected = true;
				Start = p->getm_pt().x*Row + p->getm_pt().y;
				m_vecNode[Start]->m_eNodeType = E_START;
				v_start = p->getm_pt()*Tile_size+Tile_size/2;
				
			}
			else
			{
				p->isSelected = false;
			}
			
		}
		//mineral
		for (auto p : m_vec_nearMineral)
		{
			if (PtInRect(&p->rc, pt))
			{
				p->isSelected = true;
			}
			else
			{
				p->isSelected = false;
			}
		}
		for (auto p : m_vec_farMineral)
		{
			if (PtInRect(&p->rc, pt))
			{
				p->isSelected = true;
			}
			else
			{
				p->isSelected = false;
			}
		}
		

	}
	//오른쪽 클릭
	if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)
	{
		GetCursorPos(&ptRbtn);
		ScreenToClient(g_hWnd, &ptRbtn);
		isRbt = true;
		//mineral
		for (auto p : m_vec_nearMineral)
		{
			if (PtInRect(&p->rc, ptRbtn))
			{
				if (Dest != -1)
					m_vecNode[Dest]->m_eNodeType = E_EMPTY;
				p->isSelected = true;
				Dest = p->getm_pt().x*Row + p->getm_pt().y;
				m_vecNode[Dest]->m_eNodeType = E_DEST;
				FindPath();
				v_dest.x = m_vecNode[Dest]->m_nRow*Tile_size + Tile_size / 2;
				v_dest.y = m_vecNode[Dest]->m_nCol*Tile_size + Tile_size / 2;
				isScvgoing = true;

			}
			else
			{
				p->isSelected = false;
			}
		}
		for (auto p : m_vec_farMineral)
		{
			if (PtInRect(&p->rc, ptRbtn))
			{
				if(Dest != -1)
					m_vecNode[Dest]->m_eNodeType = E_EMPTY;
			
				p->isSelected = true;
				Dest = p->getm_pt().x*Row + p->getm_pt().y;
				m_vecNode[Dest]->m_eNodeType = E_DEST;
				FindPath();
				v_dest.x = m_vecNode[Dest]->m_nRow*Tile_size + Tile_size / 2;
				v_dest.y = m_vecNode[Dest]->m_nCol*Tile_size + Tile_size / 2;
				isScvgoing = true;
			}
			else
			{
				p->isSelected = false;
			}
		}
	}
	
	//캐릭터 이동
	if (isScvgoing)
	{
		cVector2 v_Parent;
		//auto a = m_pathnode.top();
		if (m_pathnode.empty())return;
		if (m_pathnode.top() == nullptr)
			m_pathnode.pop();
		if (m_pathnode.top()->m_nRow*Tile_size + Tile_size / 2 == v_start.x)
			m_pathnode.pop();
		v_Parent.x = m_pathnode.top()->m_nRow*Tile_size + Tile_size / 2;
		v_Parent.y = m_pathnode.top()->m_nCol*Tile_size + Tile_size / 2;
		
		ScvMove(v_start, v_Parent);
		//v_start.x <= v_Parent.x + 1 && v_start.x >= v_Parent.x - 1
		//	&& v_start.y <= v_Parent.y + 1 && v_start.y >= v_Parent.y - 1
		RECT rc, rc1, rc2;
		SetRect(&rc1, v_start.x - Tile_size / 2, v_start.y - Tile_size /2,
			v_start.x + Tile_size / 2, v_start.y + Tile_size / 2);

		SetRect(&rc2, v_Parent.x - Tile_size / 4, v_Parent.y - Tile_size / 4,
			v_Parent.x + Tile_size / 4, v_Parent.y + Tile_size / 4);
		if (IntersectRect(&rc,&rc1,&rc2))
		{
			m_pathnode.pop();
		}
	}
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
	}
	
	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_WINDOW));
	///////////////////////////////////////////////////////////////////
	///////////////////////  Render 부분 넣어줌  ///////////////////////
	///////////////////////////////////////////////////////////////////

	//타일맵그리기
	for (auto p : m_vecAll_wall)
	{
		if (p.walltype == eNodeType::E_WALL)
		{
			HBRUSH hbrush, oldbrush;
			hbrush = CreateSolidBrush(RGB(125, 125, 125));
			oldbrush = (HBRUSH)SelectObject(m_hMemDC, hbrush);
			Rectangle(m_hMemDC, p.pt.x, p.pt.y,
				p.pt.x + p.Tilesize, p.pt.y + p.Tilesize);
			SelectObject(m_hMemDC, oldbrush);
			DeleteObject(hbrush);
		}
		else
		{
			Rectangle(m_hMemDC, p.pt.x, p.pt.y,
				p.pt.x + p.Tilesize, p.pt.y + p.Tilesize);
		}
	}
	//커맨드센터
	for (auto p : m_vecCmdcenter)
	{
		p->Render(m_hMemDC);
	}
	//scv*4
	for (auto p : m_vecScv)
	{
		p->Render(m_hMemDC);
	}
	//Mineral*8
	for (auto p : m_vec_nearMineral)
	{
		p->Render(m_hMemDC);
	}
	for (auto p : m_vec_farMineral)
	{
		p->Render(m_hMemDC);
	}
	//Score
	TextOut(m_hMemDC,rc.right- 500, rc.top+200, "SCORE : ", strlen("SCORE : "));
	char szBuf[100];
	wsprintf(szBuf,"%d",m_nScore);
	TextOut(m_hMemDC, rc.right - 400, rc.top + 200, szBuf, strlen(szBuf));
	//Drag
	if (ptDrag[0].x != 0 && ptDrag[0].y != 0)
	{
		if (isDrag)
		{
			HPEN pen, oldpen;
			pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
			oldpen = (HPEN)SelectObject(m_hMemDC, pen);
			SelectObject(m_hMemDC, pen);
			MoveToEx(m_hMemDC, ptDrag[0].x, ptDrag[0].y, NULL);
			LineTo(m_hMemDC, ptDrag[1].x, ptDrag[1].y);
			LineTo(m_hMemDC, ptDrag[3].x, ptDrag[3].y);
			LineTo(m_hMemDC, ptDrag[2].x, ptDrag[2].y);
			LineTo(m_hMemDC, ptDrag[0].x, ptDrag[0].y);
			SelectObject(m_hMemDC, oldpen);
			DeleteObject(pen);
		}
	}
	//오른쪽 클릭
	int RbtRadius1=10;
	int RbtRadius2 = 5;
	if (isRbt)
	{
		HPEN pen, oldpen;
		pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		oldpen = (HPEN)SelectObject(m_hMemDC, pen);
		SelectObject(m_hMemDC, pen);
		Ellipse(m_hMemDC, ptRbtn.x  - RbtRadius1,
			ptRbtn.y - RbtRadius1,
			ptRbtn.x  + RbtRadius1,
			ptRbtn.y  + RbtRadius1);
		Ellipse(m_hMemDC, ptRbtn.x  - RbtRadius2,
			ptRbtn.y - RbtRadius2,
			ptRbtn.x+ RbtRadius2,
			ptRbtn.y+ RbtRadius2);
		SelectObject(m_hMemDC, oldpen);
		DeleteObject(pen);
	}
	///////////////////////////////////////////////////////////////////
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
		GetCursorPos(&ptDrag[0]);
		ScreenToClient(g_hWnd, &ptDrag[0]);
		isDrag = true;
	}break;
	case WM_MOUSEMOVE:
	{
		GetCursorPos(&ptDrag[3]);
		ScreenToClient(g_hWnd, &ptDrag[3]);
		ptDrag[1].x = ptDrag[3].x;
		ptDrag[1].y = ptDrag[0].y;
		ptDrag[2].x = ptDrag[0].x;
		ptDrag[2].y = ptDrag[3].y;
	}break;
	case WM_LBUTTONUP:
	{
		isDrag = false;
	}break;
	case WM_RBUTTONDOWN:
	{
		
	}break;
	case WM_RBUTTONUP:
	{
	
	}break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
		}
		break;
		case VK_RIGHT:
		{
		}
		break;
		case VK_UP:
		{
		}
		break;
		case VK_DOWN:
		{
		}
		break;
		case 'B':
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			pt.x /= Tile_size;
			pt.y /= Tile_size;
			cCommandCenter* m_commandtemp = new cCommandCenter;
			m_commandtemp->setm_pt(pt);
			m_vecCmdcenter.push_back(m_commandtemp);
		}break;
		}
	}
	break;
	}
}

void cMainGame::FindPath()
{
	cNode* pStart = nullptr;
	cNode* pDest = nullptr;
	pStart = FindNode(eNodeType::E_START);
	pDest = FindNode(eNodeType::E_DEST);

	if (pStart == nullptr || pDest == nullptr)return;

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
	m_pathnode.push(pDest);
	while (pNode)
	{
		pNode->m_eNodeType = eNodeType::E_PATH;
		pNode = pNode->m_pParent;
		m_pathnode.push(pNode);
	}
}

cNode * cMainGame::FindNode(eNodeType eNodeType)
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
		if (pExtNode->m_nRow == 0) return NULL;
		int nIndex = pExtNode->m_nIndex - TILE_N;
		if (m_vecNode[nIndex]->m_eNodeType == eNodeType::E_WALL) return NULL;
		nAdjRow -= 1;
	}
	else if (nDir & E_DOWN)
	{
		if (pExtNode->m_nRow == TILE_N - 1) return NULL;
		int nIndex = pExtNode->m_nIndex + TILE_N;
		if (m_vecNode[nIndex]->m_eNodeType == eNodeType::E_WALL) return NULL;
		nAdjRow += 1;
	}

	if (nDir & E_LEFT)
	{
		if (pExtNode->m_nCol == 0) return NULL;
		int nIndex = pExtNode->m_nIndex - 1;
		if (m_vecNode[nIndex]->m_eNodeType == eNodeType::E_WALL) return NULL;
		nAdjCol -= 1;
	}
	else if (nDir & E_RIGHT)
	{
		if (pExtNode->m_nCol == TILE_N - 1) return NULL;
		int nIndex = pExtNode->m_nIndex + 1;
		if (m_vecNode[nIndex]->m_eNodeType == eNodeType::E_WALL) return NULL;
		nAdjCol += 1;
	}

	int nIndex = nAdjRow * TILE_N + nAdjCol;
	if (m_vecNode[nIndex]->m_eNodeType == eNodeType::E_WALL) return NULL;
	if (m_vecNode[nIndex]->m_eNodeState == cNode::E_CLOSE) return NULL;
	return m_vecNode[nIndex];
}

void cMainGame::ScvMove(cVector2 start, cVector2 dest)
{
	cVector2 vDir;
	vDir = dest - start;
	vDir = vDir.Normalize();

	v_start.x += vDir.x * m_fSpeed * g_pTimeManager->GetElapsedTime();
	v_start.y += vDir.y * m_fSpeed * g_pTimeManager->GetElapsedTime();
	cVector2 v_Temp;
	v_Temp.x = (v_start.x - Tile_size / 2) / Tile_size;
	v_Temp.y = v_start.y / Tile_size;
	for (auto p : m_vecScv)
	{
		if (p->isSelected)
		{
			p->setm_pt(v_Temp);
			SetRect(&p->rc, v_Temp.x*Tile_size, v_Temp.y*Tile_size,
				v_Temp.x*Tile_size + Tile_size, v_Temp.y*Tile_size + Tile_size);
		}
	}
}

