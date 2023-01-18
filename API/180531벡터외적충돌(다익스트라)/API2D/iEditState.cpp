#include "stdafx.h"
#include "iEditState.h"
#include "cMainGame.h"
#include "cNode.h"
//에디트스타일 시작
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
//에디트스타일 끝




//에디트스타일 <노드> 시작

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

		cVector2 v(pt);//포인트와 벡터가 저장형식이다르므로 넣어준다.xy좌표
		m_pMainGame->AddNode(cVector2(pt));
		return true;
	}
	break;
	}

	return false;
}
//에디트스타일 <노드> 끝



//에디트스타일 <선> 시작
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
		//다시널로만들어줘야 또쓸수 있다.
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
	const vector<cNode*>& vecNode = m_pMainGame->GetNode();//벡터의 겟

	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);

	for (auto p : vecNode)//원이 마우스커서안에 있냐 있으면 그노드 반환
	{
		if (p->IsPicked(pt))
		{
			return p;
		}
	}
	return NULL;//없으면 널
}
//에디트스타일 <선> 끝



//에디트스타일 <장애물> 시작
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
		//장애물추가함수
		m_pMainGame->AddObstacle(rc);
		return true;
	}
	break;
	}

	return false;
}
//에디트스타일 <장애물> 끝





//에디트스타일 <선충돌테스트> 시작
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
		const vector<RECT>& vecObstacle = m_pMainGame->GetObstacle();//겟벡터
		
		Graphics g(hdc);
		Pen p(&SolidBrush(Color::Black));
		//장애물 벡터<RECT>를 렉트 rc의 이터로 돌려서 펜을 빨간색으로 만든다
		//rc= 장애물의 이터레이터
		for (RECT rc : vecObstacle)
		{
			if (cUtil::IsCollision(m_ptLineFrom, m_ptLineTo, rc))//선이랑 사각형이랑 충돌했는지 수학벡터외적
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
//에디트스타일 <선충돌테스트> 끝