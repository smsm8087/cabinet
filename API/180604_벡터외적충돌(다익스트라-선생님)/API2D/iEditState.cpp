#include "stdafx.h"
#include "iEditState.h"
#include "cMainGame.h"
#include "cNode.h"

iEditState::iEditState()
	: m_pMainGame(NULL)
{
}
iEditState::~iEditState()
{
}
void iEditState::Init(cMainGame * pMainGame)
{
	m_pMainGame = pMainGame;
}

cNodeEditState::cNodeEditState()
{
}

cNodeEditState::~cNodeEditState()
{
}

void cNodeEditState::Update()
{
}

void cNodeEditState::Render(HDC hdc)
{
}

bool cNodeEditState::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainGame == NULL) return false;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		//cVector2 v(pt);
		m_pMainGame->AddNode(cVector2(pt));
		return true;
	}
	break;
	}

	return false;
}

cEdgeEditState::cEdgeEditState()
	: m_pEdgeFrom(NULL)
	, m_pEdgeTo(NULL)
{
}

cEdgeEditState::~cEdgeEditState()
{
}

void cEdgeEditState::Update()
{
}

void cEdgeEditState::Render(HDC hdc)
{
	if (m_pEdgeFrom)
	{
		POINT pt1 = m_pEdgeFrom->GetPos().ToPoint();
		POINT pt2;
		GetCursorPos(&pt2);
		ScreenToClient(g_hWnd, &pt2);
		MoveToEx(hdc, pt1.x, pt1.y, NULL);
		LineTo(hdc, pt2.x, pt2.y);
	}
}

bool cEdgeEditState::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainGame == NULL) 
		return false;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_pEdgeFrom = PickNode(lParam);
		return true;
	}
	break;
	case WM_LBUTTONUP:
	{
		if (m_pEdgeFrom == NULL) break;

		m_pEdgeTo = PickNode(lParam);

		if (m_pEdgeTo != NULL)
		{
			m_pMainGame->AddEdge(m_pEdgeFrom, m_pEdgeTo);
		}

		m_pEdgeFrom = NULL;
		m_pEdgeTo = NULL;
		return true;
	}
	break;
	}

	return false;
}

cNode * cEdgeEditState::PickNode(LPARAM lParam)
{
	if (!m_pMainGame) return NULL;
	const vector<cNode*>& vecNode = m_pMainGame->GetNode();

	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);

	for (auto p : vecNode)
	{
		if (p->IsPicked(pt))
		{
			return p;
		}
	}
	return NULL;
}

cObstacleEditState::cObstacleEditState()
{
}

cObstacleEditState::~cObstacleEditState()
{
}

void cObstacleEditState::Update()
{
}

void cObstacleEditState::Render(HDC hdc)
{
	if (m_isLButtonDown)
	{
		RECT rc;
		rc.left = m_ptLT.x;
		rc.top = m_ptLT.y;
		rc.right = m_ptRB.x;
		rc.bottom = m_ptRB.y;
		cUtil::DrawRect(hdc, rc);
	}
}

bool cObstacleEditState::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainGame == NULL) 
		return false;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
		m_ptLT.x = LOWORD(lParam);
		m_ptLT.y = HIWORD(lParam);
		return true;
	}
	break;
	case WM_MOUSEMOVE:
	{
		m_ptRB.x = LOWORD(lParam);
		m_ptRB.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
		RECT rc;
		rc.left = m_ptLT.x;
		rc.top = m_ptLT.y;
		rc.right = m_ptRB.x;
		rc.bottom = m_ptRB.y;
		m_pMainGame->AddObstacle(rc);
		return true;
	}
	break;
	}

	return false;
}

cLineCollisionTest::cLineCollisionTest()
	: m_isLButtonDown(false)
{
}

cLineCollisionTest::~cLineCollisionTest()
{
}

void cLineCollisionTest::Update()
{
}

void cLineCollisionTest::Render(HDC hdc)
{
	if (m_isLButtonDown)
	{
		const vector<RECT>& vecObstacle = m_pMainGame->GetObstacle();
		
		Graphics g(hdc);
		Pen p(&SolidBrush(Color::Black));

		for (RECT rc : vecObstacle)
		{
			if (cUtil::IsCollision(m_ptLineFrom, m_ptLineTo, rc))
			{
				p.SetColor(Color::Red);
				break;
			}
		}
		
		Point pt1, pt2;
		pt1.X = m_ptLineFrom.x;
		pt1.Y = m_ptLineFrom.y;
		pt2.X = m_ptLineTo.x;
		pt2.Y = m_ptLineTo.y;
		g.DrawLine(&p, pt1, pt2);
	}
}

bool cLineCollisionTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainGame == NULL)
		return false;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
		m_ptLineFrom.x = LOWORD(lParam);
		m_ptLineFrom.y = HIWORD(lParam);
		return true;
	}
	break;
	case WM_MOUSEMOVE:
	{
		m_ptLineTo.x = LOWORD(lParam);
		m_ptLineTo.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
		return true;
	}
	break;
	}

	return false;
}
