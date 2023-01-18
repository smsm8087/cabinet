#include "stdafx.h"
#include "cMainGame.h"
#include "cNode.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_pEdgeFrom(NULL)
	, m_pEdgeTo(NULL)
	, m_pRadioButton(NULL)
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

	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		SAFE_DELETE(m_pButton[i]);
	}

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

	Load();

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	RECT rcBtn;
	SetRect(&rcBtn, rc.right - 120, 20, rc.right - 20, 60);
	m_pButton[eButton::E_BTN_SAVE] = new cButton();
	m_pButton[eButton::E_BTN_SAVE]->Init(rcBtn, "Save");
	m_pButton[eButton::E_BTN_SAVE]->SetDelegate(this);
	m_pButton[eButton::E_BTN_SAVE]->SetTag(eButton::E_BTN_SAVE);

	SetRect(&rcBtn, rc.right - 120, 70, rc.right - 20, 110);
	m_pButton[eButton::E_BTN_RESET] = new cButton();
	m_pButton[eButton::E_BTN_RESET]->Init(rcBtn, "Reset");
	m_pButton[eButton::E_BTN_RESET]->SetDelegate(this);
	m_pButton[eButton::E_BTN_RESET]->SetTag(eButton::E_BTN_RESET);

	m_pRadioButton = new cRadioButton;
	RECT rcRadio;
	SetRect(&rcRadio, 10, 10, 120, 121);
	m_pRadioButton->Init(rcRadio);
	m_pRadioButton->AddItem("Node");
	m_pRadioButton->AddItem("Edge");
	m_pRadioButton->AddItem("Obstacle");
	m_pRadioButton->AddItem("LineCol");
	m_pRadioButton->AddItem("Dijkstra");
	m_pRadioButton->SetDelegate(this);

	m_pEditState = cNodeEditState::GetInstance();
	m_pEditState->Init(this);
	/*
	cVector2 v1(1, 0);
	cVector2 v2(0, 1);
	bool b = cVector2::CCW(v1, v2);
	b = b;
	*/
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	if(m_pEditState)
		m_pEditState->Update();

	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		if (m_pButton[i])
			m_pButton[i]->Update();
	}
	if (m_pRadioButton)
		m_pRadioButton->Update();
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
	
	for (size_t i = 0; i < m_vecObstacle.size(); i++)
	{
		cUtil::DrawRect(m_hMemDC, m_vecObstacle[i]);
	}

	Graphics g(m_hMemDC);
	Pen p(&SolidBrush(Color::Red));

	for (size_t i = 0; i < m_vecEdge.size(); i += 2)
	{
		cVector2 v1 = m_vecEdge[i]->GetPos();
		cVector2 v2 = m_vecEdge[i + 1]->GetPos();
		POINT pt1 = v1.ToPoint();
		POINT pt2 = v2.ToPoint();
		//MoveToEx(m_hMemDC, pt1.x, pt1.y, NULL);
		//LineTo(m_hMemDC, pt2.x, pt2.y);
		
		Point p1, p2;
		p1.X = pt1.x; p2.X = pt2.x;
		p1.Y = pt1.y; p2.Y = pt2.y;
		g.DrawLine(&p, p1, p2);
		string s = to_string((v2 - v1).Len());
		cVector2 v = cVector2::Center(v2, v1);
		TextOut(m_hMemDC, v.x, v.y, s.c_str(), s.length());
	}

	for (auto p : m_vecNode)
	{
		p->Render(m_hMemDC);
	}

	if (m_lstPath.empty() == false)
	{
		MoveToEx(m_hMemDC, m_lstPath.front().x, m_lstPath.front().y, NULL);
		for (auto p : m_lstPath)
		{
			LineTo(m_hMemDC, p.x, p.y);
		}
	}

	if(m_pEditState)
		m_pEditState->Render(m_hMemDC);

	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		if (m_pButton[i])
			m_pButton[i]->Render(m_hMemDC);
	}

	if (m_pRadioButton)
		m_pRadioButton->Render(m_hMemDC);
	

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
	if (m_pRadioButton->WndProc(hWnd, message, wParam, lParam))
		return;
	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		if (m_pButton[i]->WndProc(hWnd, message, wParam, lParam))
			return;
	}
	if (m_pEditState && m_pEditState->WndProc(hWnd, message, wParam, lParam))
		return;


	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_ptStart.x = LOWORD(lParam);
		m_ptStart.y = HIWORD(lParam);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		m_ptDest.x = LOWORD(lParam);
		m_ptDest.y = HIWORD(lParam);
		m_lstPath = Dijkstra(m_ptStart, m_ptDest);
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	}
}

void cMainGame::Reset()
{
	for (auto p : m_vecNode)
	{
		SAFE_DELETE(p);
	}
	m_vecNode.clear();
	m_vecEdge.clear();
	m_pEdgeFrom = NULL;
	m_pEdgeTo = NULL;
}

void cMainGame::Save()
{
	FILE* fp = NULL;
	fopen_s(&fp, "save.txt", "w");

	if (m_vecNode.empty())
	{
		fprintf_s(fp, "%d\n", 0);
		fclose(fp);
		return;
	}

	fprintf_s(fp, "%d\n", m_vecNode.size());
	for (auto p : m_vecNode)
	{
		p->SaveToFile(fp);
	}

	fprintf_s(fp, "%d\n", m_vecEdge.size() / 2);
	
	for (size_t i = 0; i < m_vecEdge.size(); i += 2)
	{
		fprintf_s(fp, "%d %d\n", m_vecEdge[i]->GetNodeNum(), m_vecEdge[i + 1]->GetNodeNum());
	}

	fprintf_s(fp, "%d\n", m_vecObstacle.size());

	for (size_t i = 0; i < m_vecObstacle.size(); i++)
	{
		fprintf_s(fp, "%d %d %d %d\n", 
			m_vecObstacle[i].left,
			m_vecObstacle[i].top, 
			m_vecObstacle[i].right, 
			m_vecObstacle[i].bottom);
	}


	fclose(fp);
}

void cMainGame::Load()
{
	FILE* fp = NULL;
	fopen_s(&fp, "save.txt", "r");

	int nNumNode = 0;
	fscanf_s(fp, "%d\n", &nNumNode);
	if (nNumNode == 0)
	{
		fclose(fp); 
		return;
	}

	for (size_t i = 0; i < nNumNode; i++)
	{
		POINT pt;
		fscanf_s(fp, "%d %d\n", &pt.x, &pt.y);
		cVector2 v(pt);
		cNode* pNode = new cNode(v, m_vecNode.size());
		m_vecNode.push_back(pNode);
	}

	int nNumEdge = 0;
	fscanf_s(fp, "%d\n", &nNumEdge);
	for (size_t i = 0; i < nNumEdge; i++)
	{
		int e1, e2;
		fscanf_s(fp, "%d %d\n", &e1, &e2);
		m_vecEdge.push_back(m_vecNode[e1]);
		m_vecEdge.push_back(m_vecNode[e2]);
	}

	int nNumObstacle = 0;
	fscanf_s(fp, "%d\n", &nNumObstacle);
	for (size_t i = 0; i < nNumObstacle; i++)
	{
		RECT rc;
		fscanf_s(fp, "%d %d %d %d\n", &rc.left, &rc.top, &rc.right, &rc.bottom);
		m_vecObstacle.push_back(rc);
	}

	fclose(fp);
}

void cMainGame::AddNode(const cVector2 v)
{
	cNode* pNode = new cNode(v, m_vecNode.size());
	m_vecNode.push_back(pNode);
}

void cMainGame::AddEdge(cNode * pNodeFrom, cNode * pNodeTo)
{
	m_vecEdge.push_back(pNodeFrom);
	m_vecEdge.push_back(pNodeTo);
}

void cMainGame::AddObstacle(const RECT rc)
{
	m_vecObstacle.push_back(rc);
}

list<POINT> cMainGame::Dijkstra(POINT p1, POINT p2)
{
	bool isDijkstra = false;
	for (RECT rc : m_vecObstacle)
	{
		if (cUtil::IsCollision(p1, p2, rc))
		{
			isDijkstra = true;
			break;
		}
	}

	if (isDijkstra == false)
	{
		list<POINT> lstPoint;
		lstPoint.push_back(p1);
		lstPoint.push_back(p2);
		return lstPoint;
	}

	vector<vector<float>> vecAdjMatrix;

	int nNumNode = (int)m_vecNode.size();
	vecAdjMatrix.resize(nNumNode);
	for (size_t i = 0; i < nNumNode; i++)
	{
		vecAdjMatrix[i].resize(nNumNode);
		for (size_t j = 0; j < nNumNode; j++)
		{
			vecAdjMatrix[i][j] = (i == j) ? 0 : FLT_MAX;
		}
	}

	for (size_t i = 0; i < m_vecEdge.size(); i += 2)
	{
		int n1 = m_vecEdge[i]->GetNodeNum();
		int n2 = m_vecEdge[i + 1]->GetNodeNum();
		cVector2 v1 = m_vecEdge[i]->GetPos();
		cVector2 v2 = m_vecEdge[i + 1]->GetPos();
		vecAdjMatrix[n1][n2] = (v2 - v1).Len();
		vecAdjMatrix[n2][n1] = vecAdjMatrix[n1][n2];
	}

	vector<bool> vecClose(nNumNode);
	vector<int> vecVia(nNumNode);
	vector<float> vecCost(nNumNode);
	for (size_t i = 0; i < nNumNode; i++)
	{
		vecClose[i] = false;
		vecVia[i] = -1;
		vecCost[i] = FLT_MAX;
	}

	int nStart = -1;
	int nDest = -1;
	float fMinDistFromStartPoint = FLT_MAX;
	float fMinDistFromDestPoint = FLT_MAX;
	cVector2 v1(p1);
	cVector2 v2(p2);
	for (auto n : m_vecNode)
	{
		float l1 = (n->GetPos() - v1).LenSq();
		float l2 = (n->GetPos() - v2).LenSq();
		if (l1 < fMinDistFromStartPoint)
		{
			fMinDistFromStartPoint = l1;
			nStart = n->GetNodeNum();
		}

		if (l2 < fMinDistFromDestPoint)
		{
			fMinDistFromDestPoint = l2;
			nDest = n->GetNodeNum();
		}
	}

	vecCost[nStart] = 0;
	for (size_t i = 0; i < nNumNode; i++)
	{
		int nMinCostNode = -1;
		float fMinCost = FLT_MAX;
		for (size_t j = 0; j < nNumNode; j++)
		{
			if (vecClose[j]) continue;
			if (vecCost[j] < fMinCost)
			{
				fMinCost = vecCost[j];
				nMinCostNode = j;
			}
		}
		assert(nMinCostNode >= 0);

		vecClose[nMinCostNode] = true;

		for (size_t j = 0; j < nNumNode; j++)
		{
			if (vecClose[j]) continue;
			if (vecCost[j] > vecCost[nMinCostNode] + vecAdjMatrix[nMinCostNode][j])
			{
				vecCost[j] = vecCost[nMinCostNode] + vecAdjMatrix[nMinCostNode][j];
				vecVia[j] = nMinCostNode;
			}
		}
	}

	vector<POINT> vecPoint;
	int n = nDest;
	while (n != nStart)
	{
		vecPoint.push_back(m_vecNode[n]->GetPos().ToPoint());
		n = vecVia[n];
	}
	vecPoint.push_back(m_vecNode[n]->GetPos().ToPoint());

	int nModDest = 0;
	for (int i = 0; i < vecPoint.size(); i++)
	{
		bool isCollision = false;
		for (RECT rc : m_vecObstacle)
		{
			if (cUtil::IsCollision(p2, vecPoint[i], rc))
			{
				isCollision = true;
				break;
			}
		}
		if (isCollision) break;
		nModDest = i;
	}

	int nModStart = 0;
	for (int i = vecPoint.size() - 1; i >= 0; i--)
	{
		bool isCollision = false;
		for (RECT rc : m_vecObstacle)
		{
			if (cUtil::IsCollision(p1, vecPoint[i], rc))
			{
				isCollision = true;
				break;
			}
		}
		if (isCollision) break;
		nModStart = i;
	}
	list<POINT> lstPath;
	for (int i = nModStart; i >= nModDest; i--)
	{
		lstPath.push_back(vecPoint[i]);
	}
	lstPath.push_front(p1);
	lstPath.push_back(p2);
	/*
	auto itStart = lstPoint.begin();
	
	for (auto p : lstPoint)
	{
		bool isCollision = false;
		for (RECT rc : m_vecObstacle)
		{
			if (cUtil::IsCollision(p1, p, rc))
			{
				isCollision = true;
				break;
			}
		}
	
		if (isCollision) break;

		itStart++;
	}

	auto itEnd = lstPoint.end();
	for (auto it = lstPoint.end(); it != lstPoint.begin(); )
	{
		--it;
		bool isCollision = false;
		for (RECT rc : m_vecObstacle)
		{
			if (cUtil::IsCollision(p2, *it, rc))
			{
				isCollision = true;
				break;
			}
		}

		if (isCollision) break;

		itEnd = it;
	}

	list<POINT> lstPath;
	
	lstPath.push_back(p1);
	for (auto it = itStart; it != itEnd; ++it)
	{
		lstPath.push_back(*it);
	}
	lstPath.push_back(*itEnd);
	lstPath.push_back(p2);
	*/
	return lstPath;
}

const vector<cNode*>& cMainGame::GetNode()
{
	return m_vecNode;
}

const vector<RECT>& cMainGame::GetObstacle()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vecObstacle;
}

void cMainGame::OnClick(cButton * pSender)
{
	if (pSender->GetTag() == eButton::E_BTN_SAVE)
	{
		Save();
	}
	else if (pSender->GetTag() == eButton::E_BTN_RESET)
	{
		Reset();
	}
}

void cMainGame::OnSelectedItemChange(cRadioButton * pSender)
{
	switch (pSender->GetSelectedItem())
	{
	case 0:
	{
		m_pEditState = cNodeEditState::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 1:
	{
		m_pEditState = cEdgeEditState::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 2:
	{
		m_pEditState = cObstacleEditState::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 3:
	{
		m_pEditState = cLineCollisionTest::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 4:
	{
		m_pEditState = NULL;
	}
	break;
	default:
		break;
	}
}

