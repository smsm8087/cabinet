#include "stdafx.h"
#include "cMainGame.h"
//#include "cAirplane.h"
#include"cImage.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)										//�ڵ��ʱ�ȭ�� �÷��̾�Ŭ���� �����Ҵ�
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	//,m_nRow(15)
	//,m_nCol(15)
	,tilesize(40)
	,fp(NULL)
	
{
	//m_bg = new cImage("map1.bmp");
	ptStart.x = -1; ptStart.y = -1;
	ptDest.x = -1; ptDest.y = -1;
	
	

	
}

cMainGame::~cMainGame()										//�Ҹ��� : ��ũ���Լ��� ��� ����������Ʈ�� �����Ҵ�� ��ü�� �����.
{
	SAFE_DELETE(m_pPlayer);
	
	ClearEnemy();

	//cTimeManager::GetInstance()->Destroy();
	g_pTimeManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()										//�ʱ�ȭ���ΰ���
{
	TILE * tile = new TILE;
	fopen_s(&fp, "data.txt", "r");
	if (fp == nullptr)return;

	fscanf_s(fp, "%d", &m_nRow);
	fscanf_s(fp, "%d", &m_nCol);
	while (!feof(fp))
	{
		fscanf_s(fp, "%d", &ptWall.x);
		fscanf_s(fp, "%d", &ptWall.y);
		m_vecptWall.push_back(ptWall);
	}
	m_vecptWall;//1���������� �ʱ�ȭ





	srand((unsigned int)time(NULL));						//�̰ž��ϸ� �����Լ� ����������������
	InitStage(1);
}

void cMainGame::Update()									//������Ʈ
{
	g_pTimeManager->Update();								//�̱���� Ÿ�ӸŴ����� ������Ʈ�Ѵ�.

	///////////////////////////astar
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	RECT rc;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		for (int i = 0; i < TILE_SIZE; ++i)
			for (int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if (PtInRect(&rc, mouse))
				{
					m_vecTile[i * TILE_SIZE + j]->Option += 1;
					if (m_vecTile[i * TILE_SIZE + j]->Option == OPTION_ELLIPSE)
						m_vecTile[i * TILE_SIZE + j]->cost.list = 3;
					if (m_vecTile[i * TILE_SIZE + j]->Option == OPTION_ELLIPSE + 1)
					{
						m_vecTile[i * TILE_SIZE + j]->Option = OPTION_RECT;
						m_vecTile[i * TILE_SIZE + j]->cost.list = 0;
					}
				}
			}
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)
	{
		_initialize();
		mouseDest = mouse;
		POINT dest = { 0 };
		for (int i = 0; i < TILE_SIZE; ++i)
			for (int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if (PtInRect(&rc, mouse))
				{
					m_vecTile[i * TILE_SIZE + j]->Option = OPTION_DESTINATION;
					dest.x = j;
					dest.y = i;
				}
			}
		for (int i = 0; i < TILE_SIZE; ++i)
			for (int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if (PtInRect(&rc, unit))
				{
					m_vecTile[i * TILE_SIZE + j]->Option = OPTION_RESOURCE;
					POINT start = { j, i };
					isMove = PathTrace(start, dest); // �� ã�� ����, ���� ������ ���� ������ �Ѱ��ش�.
				}
			}

	}
	for (int i = 0; i < TILE_SIZE; ++i)
		for (int j = 0; j < TILE_SIZE; ++j)
		{
			rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
			rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
			rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
			rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
			if (PtInRect(&rc, unit))
			{
				if (m_vecTile[i * TILE_SIZE + j]->cost.Direct != _NONE)
					m_Direct = m_vecTile[i * TILE_SIZE + j]->cost.Direct;
			}
		}
	if (isMove)
	{

		switch (m_Direct)
		{
		case TOP:
			unit.y -= Speed;
			break;
		case BOTTOM:
			unit.y += Speed;
			break;
		case LEFT:
			unit.x -= Speed;
			break;
		case RIGHT:
			unit.x += Speed;
			break;
		case RT:
			unit.x += Speed;
			unit.y -= Speed;
			break;
		case RB:
			unit.x += Speed;
			unit.y += Speed;
			break;
		case LT:
			unit.x -= Speed;
			unit.y -= Speed;
			break;
		case LB:
			unit.x -= Speed;
			unit.y += Speed;
			break;
		case _DEST:
			if (mouseDest.x > unit.x)
				unit.x += (LONG)Speed;
			if (mouseDest.x < unit.x)
				unit.x -= (LONG)Speed;
			if (mouseDest.y > unit.y)
				unit.y += (LONG)Speed;
			if (mouseDest.y < unit.y)
				unit.y -= (LONG)Speed;
			break;
		}
	}
	////////////////////////////////////
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

	/////////////astar
	static HFONT hFont, OldFont;
	static PAINTSTRUCT ps;
	static HBRUSH MyBrush, OldBrush;
	static HPEN MyPen, OldPen;

	hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
	OldFont = (HFONT)SelectObject(m_hMemDC, hFont);
	static TCHAR str[3][TILE_SQUARE] = { { "Resource" },{ "Destination" },{ "False" } };

	for (vector<TILE*>::iterator iter = m_vecTile.begin();
		iter != m_vecTile.end(); ++iter)
	{


		switch ((*iter)->Option)
		{
		case OPTION_RESOURCE:
			MyBrush = CreateSolidBrush(RGB(255, 255, 0));
			OldBrush = (HBRUSH)SelectObject(m_hMemDC, MyBrush);
			Ellipse(m_hMemDC, (*iter)->rc.left + 1, (*iter)->rc.top + 1, (*iter)->rc.right - 1, (*iter)->rc.bottom - 1);
			TextOut(m_hMemDC, (*iter)->rc.left + ((*iter)->rc.right - (*iter)->rc.left) / 2,
				(*iter)->rc.top + ((*iter)->rc.bottom - (*iter)->rc.top) / 2, "Start", strlen("Start"));
			DeleteObject(SelectObject(m_hMemDC, OldBrush));
			break;
		case OPTION_DESTINATION:
			MyBrush = CreateSolidBrush(RGB(0, 255, 255));
			OldBrush = (HBRUSH)SelectObject(m_hMemDC, MyBrush);
			Ellipse(m_hMemDC, (*iter)->rc.left + 1, (*iter)->rc.top + 1, (*iter)->rc.right - 1, (*iter)->rc.bottom - 1);
			TextOut(m_hMemDC, (*iter)->rc.left + ((*iter)->rc.right - (*iter)->rc.left) / 2,
				(*iter)->rc.top + ((*iter)->rc.bottom - (*iter)->rc.top) / 2, "Dest", strlen("Dest"));
			DeleteObject(SelectObject(m_hMemDC, OldBrush));
			break;
			//������ �ʷϻ� ������ ������ ��ΰ� �����
		case OPTION_RECT:
			if ((*iter)->cost.list == 1)
				MyPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			if ((*iter)->cost.list == 2)
				MyPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			MyBrush = CreateSolidBrush(RGB(255, 255, 255));
			OldPen = (HPEN)SelectObject(m_hMemDC, MyPen);
			OldBrush = (HBRUSH)SelectObject(m_hMemDC, MyBrush);
			Rectangle(m_hMemDC, (*iter)->rc.left + 1, (*iter)->rc.top + 1, (*iter)->rc.right - 1, (*iter)->rc.bottom - 1);
			DeleteObject(SelectObject(m_hMemDC, OldBrush));
			DeleteObject(SelectObject(m_hMemDC, OldPen));
			TCHAR cost[4][TILE_SQUARE];
			if ((*iter)->cost.F != 0)
			{
				wsprintf(cost[0], "%d", (*iter)->cost.F);
				wsprintf(cost[1], "%d", (*iter)->cost.G);
				wsprintf(cost[2], "%d", (*iter)->cost.H);
				wsprintf(cost[3], "%d", (*iter)->index);
				TextOut(m_hMemDC, (*iter)->rc.left + 5, (*iter)->rc.top + 10, cost[0], lstrlen(cost[0]));
				TextOut(m_hMemDC, (*iter)->rc.left + 5, (*iter)->rc.bottom - 15, cost[1], lstrlen(cost[1]));
				TextOut(m_hMemDC, (*iter)->rc.right - 20, (*iter)->rc.bottom - 15, cost[2], lstrlen(cost[2]));
				TextOut(m_hMemDC, (*iter)->rc.right - 20, (*iter)->rc.top + 10, cost[3], lstrlen(cost[3]));
				MoveToEx(m_hMemDC, (*iter)->rc.left + 25, (*iter)->rc.top + 25, 0);
				Ellipse(m_hMemDC, (*iter)->rc.left + 20, (*iter)->rc.top + 20, (*iter)->rc.right - 20, (*iter)->rc.bottom - 20);
				switch ((*iter)->cost.p_Direct)
				{
				case TOP:
					LineTo(m_hMemDC, (*iter)->rc.right - 25, (*iter)->rc.top);
					break;
				case BOTTOM:
					LineTo(m_hMemDC, (*iter)->rc.right - 25, (*iter)->rc.bottom);
					break;
				case LEFT:
					LineTo(m_hMemDC, (*iter)->rc.left, (*iter)->rc.bottom - 25);
					break;
				case RIGHT:
					LineTo(m_hMemDC, (*iter)->rc.right, (*iter)->rc.bottom - 25);
					break;
				case RT:
					LineTo(m_hMemDC, (*iter)->rc.right, (*iter)->rc.top);
					break;
				case RB:
					LineTo(m_hMemDC, (*iter)->rc.right, (*iter)->rc.bottom);
					break;
				case LT:
					LineTo(m_hMemDC, (*iter)->rc.left, (*iter)->rc.top);
					break;
				case LB:
					LineTo(m_hMemDC, (*iter)->rc.left, (*iter)->rc.bottom);
					break;
				}
				MoveToEx(m_hMemDC, (*iter)->rc.left + 25, (*iter)->rc.top + 25, 0);
				switch ((*iter)->cost.Direct)
				{
				case TOP:
					LineTo(m_hMemDC, (*iter)->rc.right - 25, (*iter)->rc.top);
					break;
				case BOTTOM:
					LineTo(m_hMemDC, (*iter)->rc.right - 25, (*iter)->rc.bottom);
					break;
				case LEFT:
					LineTo(m_hMemDC, (*iter)->rc.left, (*iter)->rc.bottom - 25);
					break;
				case RIGHT:
					LineTo(m_hMemDC, (*iter)->rc.right, (*iter)->rc.bottom - 25);
					break;
				case RT:
					LineTo(m_hMemDC, (*iter)->rc.right, (*iter)->rc.top);
					break;
				case RB:
					LineTo(m_hMemDC, (*iter)->rc.right, (*iter)->rc.bottom);
					break;
				case LT:
					LineTo(m_hMemDC, (*iter)->rc.left, (*iter)->rc.top);
					break;
				case LB:
					LineTo(m_hMemDC, (*iter)->rc.left, (*iter)->rc.bottom);
					break;
				}
			}
			if ((*iter)->cost.list == 2)
				TextOut(m_hMemDC, (*iter)->rc.left + 10, (*iter)->rc.bottom - 30, "  ����", lstrlen("  ����"));
			break;
		case OPTION_ELLIPSE:
			MyBrush = CreateSolidBrush(RGB(0, 0, 0));
			OldBrush = (HBRUSH)SelectObject(m_hMemDC, MyBrush);
			Rectangle(m_hMemDC, (*iter)->rc.left, (*iter)->rc.top, (*iter)->rc.right, (*iter)->rc.bottom);
			/*if ((*iter)->cost.list == 3)
				TextOut(m_hMemDC, (*iter)->rc.left + 10, (*iter)->rc.bottom - 30, "   ��", lstrlen("   ��"));*/
			SelectObject(m_hMemDC, OldBrush);
			DeleteObject(MyBrush);
			break;
		}
		if ((*iter)->cost.Direct != _NONE)
		{
			MyBrush = CreateSolidBrush(RGB(255, 255, 0));
			OldBrush = (HBRUSH)SelectObject(m_hMemDC, MyBrush);
			Rectangle(m_hMemDC, (*iter)->rc.left + 15, (*iter)->rc.top + 15, (*iter)->rc.right - 15, (*iter)->rc.bottom - 15);
			DeleteObject(SelectObject(m_hMemDC, OldBrush));
		}

	}
	Ellipse(m_hMemDC, unit.x - 15, unit.y - 15, unit.x + 15, unit.y + 15);
	SelectObject(m_hMemDC, OldFont);
	DeleteObject(hFont);
	GetClientRect(g_hWnd, &rc);
	TextOut(m_hMemDC, rc.right - 200, rc.top + 200, "������ : �� ", strlen("������ : �� "));
	TextOut(m_hMemDC, rc.right - 200, rc.top + 250, "������ : ������� ", strlen("������ : ������� "));
	TextOut(m_hMemDC, rc.right - 200, rc.top + 300, "�ʷϻ� : ������� ", strlen("�ʷϻ� : ������� "));
	TextOut(m_hMemDC, rc.right - 200, rc.top + 350, "����������簢�� : ��� ", strlen("����������簢�� : ��� "));
	TextOut(m_hMemDC, rc.right - 200, rc.top + 70, "������� : �������� ", strlen("������� : �������� "));
	TextOut(m_hMemDC, rc.right - 200, rc.top + 130, "û�ϻ��� : �������� ", strlen("û�ϻ��� : �������� "));


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
	switch (message)											//Ű�����̺�Ʈó�������� �������Լ��� �����´�. 
	{
	case WM_LBUTTONDOWN:
	{
		
		
	}break;
	case WM_RBUTTONDOWN:
	{
		
	}break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			
		}
		break;
		}
	}
	break;
	}
}

void cMainGame::InitStage(int nStage)							//���������ʱ�ȭ
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);


}

void cMainGame::ClearEnemy()									//�������� �����.
{
	for (auto p : m_vecEnemy)
	{
		SAFE_DELETE(p);
	}
	m_vecEnemy.clear();
}

HRESULT cMainGame::Initialize()
{
	

	m_vecTile.resize(TILE_SIZE * TILE_SIZE);
	
	
	for (int i = 0; i < TILE_SIZE; ++i)
	{
		for (int j = 0; j < TILE_SIZE; ++j)
		{
			TILE* pTile = new TILE;
			pTile->Option = OPTION_RECT;
			pTile->rc.top = TILE_SQUARE * i;
			pTile->rc.left = TILE_SQUARE * j;
			pTile->rc.bottom = TILE_SQUARE * (i + 1);
			pTile->rc.right = TILE_SQUARE * (j + 1);
			pTile->cost.Direct = _NONE;
			pTile->cost.G = 0;
			pTile->cost.H = 0;
			pTile->cost.p_G = 100000;
			pTile->cost.F = pTile->cost.G + pTile->cost.H;
			pTile->cost.list = 0;
			pTile->index = i * TILE_SIZE + j;
			m_vecTile[i * TILE_SIZE + j] = pTile;
		}
	}
	unit.x = 10;
	unit.y = 10;
	mouseDest.x = unit.x;
	mouseDest.y = unit.y;
	m_Direct = _NONE;
	Speed = 10;
	isMove = false;

	for (size_t k = 0; k <m_vecptWall.size(); k++)
	{
		POINT pos;
		pos.x = 0;
		pos.y = 0;
		pos.x = m_vecptWall[k].x + 25;
		pos.y = m_vecptWall[k].y + 25;
		RECT rc;
		for (int i = 0; i < TILE_SIZE; ++i)
		{
			for (int j = 0; j < TILE_SIZE; ++j)
			{
				if (i * TILE_SIZE + j > 225)
					break;
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if (PtInRect(&rc, pos))
				{
					m_vecTile[i * TILE_SIZE + j]->Option += 1;
					if (m_vecTile[i * TILE_SIZE + j]->Option == OPTION_ELLIPSE)
						m_vecTile[i * TILE_SIZE + j]->cost.list = 3;
				}

			}
			int x = 0;
		}
	}

	return S_OK;
}

void cMainGame::Render()
{
	
}


bool cMainGame::PathTrace(POINT start, POINT dest)
{
	_resultH(dest);
	// ���� ������ ���� ������ ���ٸ� ����.
	if (start.x == dest.x && start.y == dest.y) return true;
	if (m_vecTile[start.y * TILE_SIZE + start.x]->cost.list == 3) return false;
	for (int search = 0; search < 1000; ++search)	// �ִ� 1000���� �˻��Ѵ�. 1000���̳� ����� �� ������ ��� ��θ� �������� �ʴ´�.
	{
		// 1. ���� ������ ���� ���(2)���� ����.
		TILE* parent = m_vecTile[start.y * TILE_SIZE + start.x];
		parent->cost.list = 2;

		// 2. �ֺ� �簢������ ���� ���(1)�� �߰��Ѵ�.(���� ����)
		// 3. (�ٽ�)���� ��ϵ��� ���ο� ���� ���� ���ش�.

		// TOP
		if (start.y > 0)
		{
			TILE* temp = m_vecTile[(start.y - 1) * TILE_SIZE + start.x];
			if (temp->cost.list == 0 || temp->cost.list == 1)
			{
				if (temp->cost.p_G >= parent->cost.G)
				{
					temp->cost.list = 1;
					temp->cost.G = parent->cost.G + 10;
					temp->cost.F = temp->cost.G + temp->cost.H;
					temp->cost.p_G = parent->cost.G;
					temp->cost.p_Direct = BOTTOM;
				}
			}
		}

		// LEFT
		if (start.x > 0)
		{
			TILE* temp = m_vecTile[start.y * TILE_SIZE + start.x - 1];
			if (temp->cost.list == 0 || temp->cost.list == 1)
			{
				if (temp->cost.p_G >= parent->cost.G)
				{
					temp->cost.list = 1;
					temp->cost.G = parent->cost.G + 10;
					temp->cost.F = temp->cost.G + temp->cost.H;
					temp->cost.p_G = parent->cost.G;
					temp->cost.p_Direct = RIGHT;
				}
			}
		}

		// RIGHT
		if (start.x < TILE_SIZE - 1)
		{
			TILE* temp = m_vecTile[start.y * TILE_SIZE + start.x + 1];
			if (temp->cost.list == 0 || temp->cost.list == 1)
			{
				if (temp->cost.p_G >= parent->cost.G)
				{
					temp->cost.list = 1;
					temp->cost.G = parent->cost.G + 10;
					temp->cost.F = temp->cost.G + temp->cost.H;
					temp->cost.p_G = parent->cost.G;
					temp->cost.p_Direct = LEFT;
				}
			}
		}

		// BOTTOM
		if (start.y < TILE_SIZE - 1)
		{
			TILE* temp = m_vecTile[(start.y + 1) * TILE_SIZE + start.x];
			if (temp->cost.list == 0 || temp->cost.list == 1)
			{
				if (temp->cost.p_G >= parent->cost.G)
				{
					temp->cost.list = 1;
					temp->cost.G = parent->cost.G + 10;
					temp->cost.F = temp->cost.G + temp->cost.H;
					temp->cost.p_G = parent->cost.G;
					temp->cost.p_Direct = TOP;
				}
			}
		}
		// RB
		if (start.y < TILE_SIZE - 1 && start.x < TILE_SIZE - 1)
		{
			// �밢���� ��� ���� ���� ���� �ִ� ��� �����Ѵ�.
			if (m_vecTile[(start.y + 1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x + 1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y + 1) * TILE_SIZE + start.x + 1];
				if (temp->cost.list == 0 || temp->cost.list == 1)
				{
					if (temp->cost.p_G >= parent->cost.G)
					{
						temp->cost.list = 1;
						temp->cost.G = parent->cost.G + 14;
						temp->cost.F = temp->cost.G + temp->cost.H;
						temp->cost.p_G = parent->cost.G;
						temp->cost.p_Direct = LT;
					}
				}
			}
		}

		// LT
		if (start.y > 0 && start.x > 0)
		{
			if (m_vecTile[(start.y - 1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x - 1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y - 1) * TILE_SIZE + start.x - 1];
				if (temp->cost.list == 0 || temp->cost.list == 1)
				{
					if (temp->cost.p_G >= parent->cost.G)
					{
						temp->cost.list = 1;
						temp->cost.G = parent->cost.G + 14;
						temp->cost.F = temp->cost.G + temp->cost.H;
						temp->cost.p_G = parent->cost.G;
						temp->cost.p_Direct = RB;
					}
				}
			}
		}

		// LB
		if (start.y < TILE_SIZE - 1 && start.x > 0)
		{
			if (m_vecTile[(start.y + 1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x - 1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y + 1) * TILE_SIZE + start.x - 1];
				if (temp->cost.list == 0 || temp->cost.list == 1)
				{
					if (temp->cost.p_G >= parent->cost.G)
					{
						temp->cost.list = 1;
						temp->cost.G = parent->cost.G + 14;
						temp->cost.F = temp->cost.G + temp->cost.H;
						temp->cost.p_G = parent->cost.G;
						temp->cost.p_Direct = RT;
					}
				}
			}
		}

		// RT
		if (start.y > 0 && start.x < TILE_SIZE - 1)
		{
			if (m_vecTile[(start.y - 1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x + 1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y - 1) * TILE_SIZE + start.x + 1];
				if (temp->cost.list == 0 || temp->cost.list == 1)
				{
					if (temp->cost.p_G >= parent->cost.G)
					{
						temp->cost.list = 1;
						temp->cost.G = parent->cost.G + 14;
						temp->cost.F = temp->cost.G + temp->cost.H;
						temp->cost.p_G = parent->cost.G;
						temp->cost.p_Direct = LB;
					}
				}
			}
		}

		// 4. ���� ��� �� F���� ���� ���� ���. (ã�� �ݺ�)
		int minF = 10000, minH = 10000;
		for (int i = 0; i < TILE_SIZE; ++i)
			for (int j = 0; j < TILE_SIZE; ++j)
			{
				TILE* temp = m_vecTile[i * TILE_SIZE + j];
				if (temp->cost.list == 1)		// ���� ��� ��
					if (minF >= temp->cost.F)		// F���� ���� ���� ���
					{
						minF = temp->cost.F;
						minH = temp->cost.H;
						start.x = j;
						start.y = i;
					}
			}
		if (minH == 0) break;
	}

	// 5. ��� ã�Ⱑ �Ϸ�Ǹ� ���� �������� �θ� Ŭ������ �ݺ��Ͽ� ã�� ���� �������� ���� ������ش�. (������ �����Ͽ� ����ȭ�� ���� ����.)
	TILE* destination_path = 0;
	for (int i = 0; i < TILE_SIZE; ++i)
		for (int j = 0; j < TILE_SIZE; ++j)
			if (m_vecTile[i * TILE_SIZE + j]->cost.H == 0)
				destination_path = m_vecTile[i * TILE_SIZE + j];
	TILE* temp = 0;
	while (true)
	{
		int _x = 0, _y = 0;
		switch (destination_path->cost.p_Direct)
		{
		case TOP:
			_x = destination_path->rc.left / TILE_SQUARE;
			_y = destination_path->rc.top / TILE_SQUARE - 1;
			break;
		case BOTTOM:
			_x = destination_path->rc.left / TILE_SQUARE;
			_y = destination_path->rc.top / TILE_SQUARE + 1;
			break;
		case LEFT:
			_x = destination_path->rc.left / TILE_SQUARE - 1;
			_y = destination_path->rc.top / TILE_SQUARE;
			break;
		case RIGHT:
			_x = destination_path->rc.left / TILE_SQUARE + 1;
			_y = destination_path->rc.top / TILE_SQUARE;
			break;
		case RT:
			_x = destination_path->rc.left / TILE_SQUARE + 1;
			_y = destination_path->rc.top / TILE_SQUARE - 1;
			break;
		case RB:
			_x = destination_path->rc.left / TILE_SQUARE + 1;
			_y = destination_path->rc.top / TILE_SQUARE + 1;
			break;
		case LT:
			_x = destination_path->rc.left / TILE_SQUARE - 1;
			_y = destination_path->rc.top / TILE_SQUARE - 1;
			break;
		case LB:
			_x = destination_path->rc.left / TILE_SQUARE - 1;
			_y = destination_path->rc.top / TILE_SQUARE + 1;
			break;
		}
		if (destination_path->cost.list == 3) return false;
		if (temp == 0)
			destination_path->cost.Direct = _DEST;
		else
			switch (temp->cost.p_Direct)
			{
			case TOP:
				destination_path->cost.Direct = BOTTOM;
				break;
			case BOTTOM:
				destination_path->cost.Direct = TOP;
				break;
			case LEFT:
				destination_path->cost.Direct = RIGHT;
				break;
			case RIGHT:
				destination_path->cost.Direct = LEFT;
				break;
			case RT:
				destination_path->cost.Direct = LB;
				break;
			case RB:
				destination_path->cost.Direct = LT;
				break;
			case LT:
				destination_path->cost.Direct = RB;
				break;
			case LB:
				destination_path->cost.Direct = RT;
				break;
			}
		if (destination_path->cost.G == 0) break;
		temp = destination_path;
		destination_path = m_vecTile[_y * TILE_SIZE + _x];
	}
	for (int i = 0; i < TILE_SIZE; ++i)
		for (int j = 0; j < TILE_SIZE; ++j)
			if (m_vecTile[i * TILE_SIZE + j]->cost.list == 1)
				return true;
	return false;// ��ã�� ��� �ʱ�ȭ�ϰ� ��θ� ������ �ʴ´�.(����)
}

void cMainGame::_resultH(POINT dest)
{
	int absX = 0, absY = 0;
	// �������� ���� ���� �������� Ŀ���� ��ü���� H���� �����Ѵ�.
	for (int i = 0; i < TILE_SIZE; ++i)
		for (int j = 0; j < TILE_SIZE; ++j)
		{
			absX = (dest.x - j) * 10;
			absY = (dest.y - i) * 10;
			if (absX<0) absX *= -1;
			if (absY<0) absY *= -1;
			m_vecTile[i * TILE_SIZE + j]->cost.H = absX + absY;
		}
}

void cMainGame::_initialize()
{
	for (int i = 0; i < TILE_SIZE; ++i)
		for (int j = 0; j < TILE_SIZE; ++j)
		{
			m_vecTile[i * TILE_SIZE + j]->cost.G = 0;
			m_vecTile[i * TILE_SIZE + j]->cost.H = 0;
			m_vecTile[i * TILE_SIZE + j]->cost.F = 0;
			m_vecTile[i * TILE_SIZE + j]->cost.p_G = 100000;
			m_vecTile[i * TILE_SIZE + j]->cost.Direct = _NONE;
			m_vecTile[i * TILE_SIZE + j]->cost.p_Direct = _NONE;
			if (m_vecTile[i * TILE_SIZE + j]->cost.list != 3)
			{
				m_vecTile[i * TILE_SIZE + j]->cost.list = 0;
				m_vecTile[i * TILE_SIZE + j]->Option = OPTION_RECT;
			}
			if (m_vecTile[i * TILE_SIZE + j]->cost.list == 3)
			{
				m_vecTile[i * TILE_SIZE + j]->Option = OPTION_ELLIPSE;
			}
		}
}

