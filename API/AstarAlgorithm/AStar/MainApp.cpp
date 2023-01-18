#include "StdAfx.h"
#include "MainApp.h"


CMainApp::CMainApp(void)
{
}


CMainApp::~CMainApp(void)
{
}

HRESULT CMainApp::Initialize()
{
	m_hdc = GetDC(g_hWnd);
	m_vecTile.resize(TILE_SIZE * TILE_SIZE);
	for(int i = 0; i < TILE_SIZE; ++i)
	{
		for(int j = 0; j < TILE_SIZE; ++j)
		{
			TILE* pTile = new TILE;
			pTile->Option    = OPTION_RECT;
			pTile->rc.top    = TILE_SQUARE * i;
			pTile->rc.left   = TILE_SQUARE * j;
			pTile->rc.bottom = TILE_SQUARE * (i+1);
			pTile->rc.right  = TILE_SQUARE * (j+1);
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
	return S_OK;
}

int CMainApp::Progress()
{
	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(g_hWnd, &mouse);
	RECT rc;
	if(GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		for(int i = 0; i < TILE_SIZE; ++i)
			for(int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if(PtInRect(&rc, mouse))
				{
					m_vecTile[i * TILE_SIZE + j]->Option += 1;
					if(m_vecTile[i * TILE_SIZE + j]->Option == OPTION_ELLIPSE)
						m_vecTile[i * TILE_SIZE + j]->cost.list = 3;
					if(m_vecTile[i * TILE_SIZE + j]->Option == OPTION_ELLIPSE + 1)
					{
						m_vecTile[i * TILE_SIZE + j]->Option = OPTION_RECT;
						m_vecTile[i * TILE_SIZE + j]->cost.list = 0;
					}
				}
			}
	}
	if(GetAsyncKeyState(VK_RBUTTON) & 0x0001)
	{
		_initialize();
		mouseDest = mouse;
		POINT dest = {0};
		for(int i = 0; i < TILE_SIZE; ++i)
			for(int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if(PtInRect(&rc, mouse))
				{
					m_vecTile[i * TILE_SIZE + j]->Option = OPTION_DESTINATION;
					dest.x = j;
					dest.y = i;
				}
			}
		for(int i = 0; i < TILE_SIZE; ++i)
			for(int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if(PtInRect(&rc, unit))
				{
					m_vecTile[i * TILE_SIZE + j]->Option = OPTION_RESOURCE;
					POINT start = {j, i};
					isMove = PathTrace(start, dest); // 길 찾기 실행, 시작 지점과 도착 지점을 넘겨준다.
				}
			}
		
	}
	for(int i = 0; i < TILE_SIZE; ++i)
			for(int j = 0; j < TILE_SIZE; ++j)
			{
				rc.top = m_vecTile[i * TILE_SIZE + j]->rc.top;
				rc.left = m_vecTile[i * TILE_SIZE + j]->rc.left;
				rc.bottom = m_vecTile[i * TILE_SIZE + j]->rc.bottom;
				rc.right = m_vecTile[i * TILE_SIZE + j]->rc.right;
				if(PtInRect(&rc, unit))
				{
					if(m_vecTile[i * TILE_SIZE + j]->cost.Direct != _NONE)
						m_Direct = m_vecTile[i * TILE_SIZE + j]->cost.Direct;
				}
			}
	if(isMove)
	{
		
		switch(m_Direct)
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
			if(mouseDest.x > unit.x)
				unit.x += (LONG)Speed;
			if(mouseDest.x < unit.x)
				unit.x -= (LONG)Speed;
			if(mouseDest.y > unit.y)
				unit.y += (LONG)Speed;
			if(mouseDest.y < unit.y)
				unit.y -= (LONG)Speed;
			break;
		}
	}
	return 0;
}

void CMainApp::Render()
{
	static HFONT hFont, OldFont;
	static PAINTSTRUCT ps;
	static HBRUSH MyBrush, OldBrush;
	static HPEN MyPen, OldPen;

	hFont = CreateFont(10,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,VARIABLE_PITCH|FF_ROMAN,TEXT("궁서"));
	OldFont = (HFONT)SelectObject(m_hdc, hFont);
	static TCHAR str[3][TILE_SQUARE] = { { L"Resource" }, { L"Destination" }, { L"False" } };

	for(vector<TILE*>::iterator iter = m_vecTile.begin();
		iter != m_vecTile.end(); ++iter)
	{
		switch((*iter)->Option)
		{
		case OPTION_RESOURCE:
			MyBrush = CreateSolidBrush(RGB(0,255,0));
			OldBrush = (HBRUSH)SelectObject(m_hdc, MyBrush);
			Ellipse(m_hdc, (*iter)->rc.left + 1, (*iter)->rc.top + 1, (*iter)->rc.right - 1, (*iter)->rc.bottom - 1);
			DeleteObject(SelectObject(m_hdc, OldBrush));
			break;
		case OPTION_DESTINATION:
			MyBrush = CreateSolidBrush(RGB(255,0,0));
			OldBrush = (HBRUSH)SelectObject(m_hdc, MyBrush);
			Ellipse(m_hdc, (*iter)->rc.left + 1, (*iter)->rc.top + 1, (*iter)->rc.right - 1, (*iter)->rc.bottom - 1);
			DeleteObject(SelectObject(m_hdc, OldBrush));
			break;
		case OPTION_RECT:
			if((*iter)->cost.list == 1)
				MyPen = CreatePen(PS_SOLID, 2, RGB(0,255,255));
			if((*iter)->cost.list == 2)
				MyPen = CreatePen(PS_SOLID, 3, RGB(0,205,0));
			MyBrush = CreateSolidBrush(RGB(255,255,255));
			OldPen = (HPEN)SelectObject(m_hdc, MyPen);
			OldBrush = (HBRUSH)SelectObject(m_hdc, MyBrush);
			Rectangle(m_hdc, (*iter)->rc.left + 1, (*iter)->rc.top + 1, (*iter)->rc.right - 1, (*iter)->rc.bottom - 1);
			DeleteObject(SelectObject(m_hdc, OldBrush));
			DeleteObject(SelectObject(m_hdc, OldPen));
			TCHAR cost[4][TILE_SQUARE];
			if((*iter)->cost.F != 0)
			{
				wsprintf(cost[0], L"%d", (*iter)->cost.F);
				wsprintf(cost[1], L"%d", (*iter)->cost.G);
				wsprintf(cost[2], L"%d", (*iter)->cost.H);
				wsprintf(cost[3], L"%d", (*iter)->index);
				TextOut(m_hdc,(*iter)->rc.left + 5, (*iter)->rc.top + 10, cost[0], lstrlen(cost[0]));
				TextOut(m_hdc,(*iter)->rc.left + 5, (*iter)->rc.bottom - 15, cost[1], lstrlen(cost[1]));
				TextOut(m_hdc,(*iter)->rc.right - 20, (*iter)->rc.bottom - 15, cost[2], lstrlen(cost[2]));
				TextOut(m_hdc,(*iter)->rc.right - 20, (*iter)->rc.top + 10, cost[3], lstrlen(cost[3]));
				MoveToEx(m_hdc,(*iter)->rc.left + 25, (*iter)->rc.top + 25, 0);
				Ellipse(m_hdc, (*iter)->rc.left + 20, (*iter)->rc.top + 20, (*iter)->rc.right - 20, (*iter)->rc.bottom - 20);
				switch((*iter)->cost.p_Direct)
				{
				case TOP:
					LineTo(m_hdc, (*iter)->rc.right - 25, (*iter)->rc.top);
					break;
				case BOTTOM:
					LineTo(m_hdc, (*iter)->rc.right - 25, (*iter)->rc.bottom);
					break;
				case LEFT:
					LineTo(m_hdc, (*iter)->rc.left, (*iter)->rc.bottom - 25);
					break;
				case RIGHT:
					LineTo(m_hdc, (*iter)->rc.right, (*iter)->rc.bottom - 25);
					break;
				case RT:
					LineTo(m_hdc, (*iter)->rc.right, (*iter)->rc.top);
					break;
				case RB:
					LineTo(m_hdc, (*iter)->rc.right, (*iter)->rc.bottom);
					break;
				case LT:
					LineTo(m_hdc, (*iter)->rc.left, (*iter)->rc.top);
					break;
				case LB:
					LineTo(m_hdc, (*iter)->rc.left, (*iter)->rc.bottom);
					break;
				}
				MoveToEx(m_hdc,(*iter)->rc.left + 25, (*iter)->rc.top + 25, 0);
				switch((*iter)->cost.Direct)
				{
				case TOP:
					LineTo(m_hdc, (*iter)->rc.right - 25, (*iter)->rc.top);
					break;
				case BOTTOM:
					LineTo(m_hdc, (*iter)->rc.right - 25, (*iter)->rc.bottom);
					break;
				case LEFT:
					LineTo(m_hdc, (*iter)->rc.left, (*iter)->rc.bottom - 25);
					break;
				case RIGHT:
					LineTo(m_hdc, (*iter)->rc.right, (*iter)->rc.bottom - 25);
					break;
				case RT:
					LineTo(m_hdc, (*iter)->rc.right, (*iter)->rc.top);
					break;
				case RB:
					LineTo(m_hdc, (*iter)->rc.right, (*iter)->rc.bottom);
					break;
				case LT:
					LineTo(m_hdc, (*iter)->rc.left, (*iter)->rc.top);
					break;
				case LB:
					LineTo(m_hdc, (*iter)->rc.left, (*iter)->rc.bottom);
					break;
				}
			}
			if((*iter)->cost.list == 2)
				TextOut(m_hdc, (*iter)->rc.left + 10, (*iter)->rc.bottom - 30, str[2], lstrlen(str[2]));
			break;
		case OPTION_ELLIPSE:
			Ellipse(m_hdc, (*iter)->rc.left, (*iter)->rc.top, (*iter)->rc.right, (*iter)->rc.bottom);
			if((*iter)->cost.list == 3)
				TextOut(m_hdc, (*iter)->rc.left + 10, (*iter)->rc.bottom - 30, str[2], lstrlen(str[2]));
			break;
		}
		if((*iter)->cost.Direct != _NONE)
		{
			MyBrush = CreateSolidBrush(RGB(255,0,0));
			OldBrush = (HBRUSH)SelectObject(m_hdc, MyBrush);
			Rectangle(m_hdc, (*iter)->rc.left + 20, (*iter)->rc.top + 20, (*iter)->rc.right - 20, (*iter)->rc.bottom - 20);
			DeleteObject(SelectObject(m_hdc, OldBrush));
		}
	}
	Ellipse(m_hdc, unit.x -15, unit.y - 15, unit.x + 15, unit.y + 15);
	SelectObject(m_hdc,OldFont);
	DeleteObject(hFont);
	EndPaint(g_hWnd, &ps);
}

void CMainApp::Release()
{}

bool CMainApp::PathTrace(POINT start, POINT dest)
{
	_resultH(dest);
	// 시작 지점과 도착 지점이 같다면 종료.
	if(start.x == dest.x && start.y == dest.y) return true;
	if(m_vecTile[start.y * TILE_SIZE + start.x]->cost.list == 3) return false;
	for(int search = 0; search < 1000; ++search)	// 최대 1000번을 검색한다. 1000번이내 결과가 안 나오는 경우 경로를 돌려주지 않는다.
	{
		// 1. 시작 지점은 닫힌 목록(2)으로 변경.
		TILE* parent = m_vecTile[start.y * TILE_SIZE + start.x];
		parent->cost.list = 2;
	
		// 2. 주변 사각형들을 열린 목록(1)에 추가한다.(벽은 무시)
		// 3. (다시)열린 목록들은 새로운 값을 지정 해준다.
	
		// TOP
		if(start.y > 0)
		{
			TILE* temp = m_vecTile[(start.y-1) * TILE_SIZE + start.x];
			if(temp->cost.list == 0 || temp->cost.list == 1)
			{
				if(temp->cost.p_G >= parent->cost.G)
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
		if(start.x > 0)
		{
			TILE* temp = m_vecTile[start.y * TILE_SIZE + start.x-1];
			if(temp->cost.list == 0 || temp->cost.list == 1)
			{
				if(temp->cost.p_G >= parent->cost.G)
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
		if(start.x < TILE_SIZE - 1)
		{
			TILE* temp = m_vecTile[start.y * TILE_SIZE + start.x+1];
			if(temp->cost.list == 0 || temp->cost.list == 1)
			{
				if(temp->cost.p_G >= parent->cost.G)
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
		if(start.y < TILE_SIZE - 1)
		{
			TILE* temp = m_vecTile[(start.y+1) * TILE_SIZE + start.x];
			if(temp->cost.list == 0 || temp->cost.list == 1)
			{
				if(temp->cost.p_G >= parent->cost.G)
				{
					temp->cost.list = 1;
					temp->cost.G = parent->cost.G +10;
					temp->cost.F = temp->cost.G + temp->cost.H;
					temp->cost.p_G = parent->cost.G;
					temp->cost.p_Direct = TOP;
				}
			}
		}
		// RB
		if(start.y < TILE_SIZE - 1 && start.x < TILE_SIZE - 1)
		{
			// 대각선의 경우 가로 세로 벽이 있는 경우 무시한다.
			if(m_vecTile[(start.y+1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x+1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y+1) * TILE_SIZE + start.x+1];
				if(temp->cost.list == 0 || temp->cost.list == 1)
				{
					if(temp->cost.p_G >= parent->cost.G)
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
		if(start.y > 0 && start.x > 0)
		{
			if(m_vecTile[(start.y-1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x-1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y-1) * TILE_SIZE + start.x-1];
				if(temp->cost.list == 0 || temp->cost.list == 1)
				{
					if(temp->cost.p_G >= parent->cost.G)
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
		if(start.y < TILE_SIZE - 1 && start.x > 0)
		{
			if(m_vecTile[(start.y+1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x-1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y+1) * TILE_SIZE + start.x-1];
				if(temp->cost.list == 0 || temp->cost.list == 1)
				{
					if(temp->cost.p_G >= parent->cost.G)
					{
						temp->cost.list = 1;
						temp->cost.G = parent->cost.G +14;
						temp->cost.F = temp->cost.G + temp->cost.H;
						temp->cost.p_G = parent->cost.G;
						temp->cost.p_Direct = RT;
					}
				}
			}
		}

		// RT
		if(start.y > 0 && start.x < TILE_SIZE - 1)
		{
			if(m_vecTile[(start.y-1) * TILE_SIZE + start.x]->cost.list == 3 || m_vecTile[(start.y) * TILE_SIZE + start.x+1]->cost.list == 3);
			else
			{
				TILE* temp = m_vecTile[(start.y-1) * TILE_SIZE + start.x+1];
				if(temp->cost.list == 0 || temp->cost.list == 1)
				{
					if(temp->cost.p_G >= parent->cost.G)
					{
						temp->cost.list = 1;
						temp->cost.G = parent->cost.G +14;
						temp->cost.F = temp->cost.G + temp->cost.H;
						temp->cost.p_G = parent->cost.G;
						temp->cost.p_Direct = LB;
					}
				}
			}
		}
		
		// 4. 열린 목록 중 F값이 제일 작은 경우. (찾기 반복)
		int minF=10000, minH=10000;
		for(int i = 0; i < TILE_SIZE; ++i)
			for(int j = 0; j < TILE_SIZE; ++j)
			{
				TILE* temp = m_vecTile[i * TILE_SIZE + j];
				if(temp->cost.list == 1)		// 열린 목록 중
					if(minF >= temp->cost.F)		// F값이 제일 작은 경우
						{
							minF = temp->cost.F;
							minH = temp->cost.H;
							start.x = j;
							start.y = i;
						}
			}
		if(minH == 0) break;
	}

	// 5. 경로 찾기가 완료되면 도착 지점부터 부모 클래스를 반복하여 찾아 시작 지점까지 길을 만들어준다. (역으로 추적하여 최적화된 길을 제시.)
	TILE* destination_path;
	for(int i = 0; i < TILE_SIZE; ++i)
		for(int j = 0; j < TILE_SIZE; ++j)
			if(m_vecTile[i * TILE_SIZE + j]->cost.H == 0)
				destination_path = m_vecTile[i * TILE_SIZE + j];
	TILE* temp=0;
	while(true)
	{
		int _x = 0, _y = 0;
		switch(destination_path->cost.p_Direct)
		{
		case TOP:
			_x = destination_path->rc.left/TILE_SQUARE;
			_y = destination_path->rc.top/TILE_SQUARE-1;				
			break;
		case BOTTOM:
			_x = destination_path->rc.left/TILE_SQUARE;
			_y = destination_path->rc.top/TILE_SQUARE+1;				
			break;
		case LEFT:
			_x = destination_path->rc.left/TILE_SQUARE-1;
			_y = destination_path->rc.top/TILE_SQUARE;				
			break;
		case RIGHT:
			_x = destination_path->rc.left/TILE_SQUARE+1;
			_y = destination_path->rc.top/TILE_SQUARE;	
			break;
		case RT:
			_x = destination_path->rc.left/TILE_SQUARE+1;
			_y = destination_path->rc.top/TILE_SQUARE-1;	
			break;
		case RB:
			_x = destination_path->rc.left/TILE_SQUARE+1;
			_y = destination_path->rc.top/TILE_SQUARE+1;	
			break;
		case LT:
			_x = destination_path->rc.left/TILE_SQUARE-1;
			_y = destination_path->rc.top/TILE_SQUARE-1;	
			break;
		case LB:
			_x = destination_path->rc.left/TILE_SQUARE-1;
			_y = destination_path->rc.top/TILE_SQUARE+1;	
			break;
		}
		if(destination_path->cost.list == 3) return false;
		if(temp == 0)
			destination_path->cost.Direct = _DEST;
		else
			switch(temp->cost.p_Direct)
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
		if(destination_path->cost.G == 0) break;
		temp = destination_path;
		destination_path = m_vecTile[_y * TILE_SIZE +_x];
	}
	for(int i = 0; i < TILE_SIZE; ++i)
		for(int j = 0; j < TILE_SIZE; ++j)
			if(m_vecTile[i * TILE_SIZE + j]->cost.list == 1)
				return true;
	return false;// 못찾는 경우 초기화하고 경로를 보내지 않는다.(보류)
}

void CMainApp::_resultH(POINT dest)
{
	int absX=0, absY=0;
	// 목적지로 부터 시작 지점까지 커지는 전체적인 H값을 구성한다.
	for(int i = 0; i < TILE_SIZE; ++i)
		for(int j = 0; j < TILE_SIZE; ++j)
		{
			absX = (dest.x-j)*10;
			absY = (dest.y-i)*10;
			if(absX<0) absX*=-1;
			if(absY<0) absY*=-1;
			m_vecTile[i * TILE_SIZE + j]->cost.H = absX+absY;
		}
}
void CMainApp::_initialize()
{
	for(int i = 0; i < TILE_SIZE; ++i)
			for(int j = 0; j < TILE_SIZE; ++j)
			{
				m_vecTile[i * TILE_SIZE + j]->cost.G = 0;
				m_vecTile[i * TILE_SIZE + j]->cost.H = 0;
				m_vecTile[i * TILE_SIZE + j]->cost.F = 0;
				m_vecTile[i * TILE_SIZE + j]->cost.p_G = 100000;
				m_vecTile[i * TILE_SIZE + j]->cost.Direct = _NONE;
				m_vecTile[i * TILE_SIZE + j]->cost.p_Direct = _NONE;
				if(m_vecTile[i * TILE_SIZE + j]->cost.list != 3)
				{
					m_vecTile[i * TILE_SIZE + j]->cost.list = 0;
					m_vecTile[i * TILE_SIZE + j]->Option = OPTION_RECT;
				}
				if(m_vecTile[i * TILE_SIZE + j]->cost.list == 3)
				{
					m_vecTile[i * TILE_SIZE + j]->Option = OPTION_ELLIPSE;
				}
			}
}