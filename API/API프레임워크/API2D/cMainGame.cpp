#include "stdafx.h"
#include "cMainGame.h"
#include"cCharater.h"
//#include "cAirplane.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)										//핸들초기화및 플레이어클래스 동적할당
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	,idle(false)
	,m_fScale(0.0f)
	,m_fx(0.0f)
	,m_fy(0.0f)
	
{
	ch = new cCharater("mario.bmp");
	ch1 = new cCharater("map1.bmp");
	ch2 = new cCharater("map2.bmp");
}

cMainGame::~cMainGame()										//소멸자 : 매크로함수로 써논 세이프딜리트로 동적할당된 객체를 지운다.
{
	//SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(ch);
	SAFE_DELETE(ch1);
	SAFE_DELETE(ch2);
	ClearEnemy();

	//cTimeManager::GetInstance()->Destroy();
	g_pTimeManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()										//초기화메인게임
{
	srand((unsigned int)time(NULL));						//이거안하면 랜드함수 못씀같은값만나옴
	//InitStage(1);											//1스테이지로 초기화
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_rc.left = rc.left;
	m_rc.right = rc.right;
	m_rc.top = rc.bottom / 3 * 2;
	m_rc.bottom = rc.bottom;
	//바닥 만들기 끝

	//플레이어 시작
	radius = 50;

	pt.x = rc.left + 150;

	pt.y = rc.bottom / 3 * 2;
	m_playerrc.left = pt.x;
	m_playerrc.top = pt.y - radius;
	m_playerrc.right = pt.x + radius;
	m_playerrc.bottom = pt.y;
	

	//발판 시작
	
	m_enemyrc.left = 730;
	m_enemyrc.top = 180;
	m_enemyrc.right = 780;
	m_enemyrc.bottom = 230;
	GetClientRect(g_hWnd, &rc);
	
	//속도 시작
	speed = 0;
	a = 0;
	jump = 0;
	isjumping = false;
}

void cMainGame::Update()									//업데이트
{
	
	
	g_pTimeManager->Update();								//싱글톤된 타임매니저를 업데이트한다.
	RECT rc;
	RECT rcTemp;
	GetClientRect(g_hWnd, &rc);
	
	
//움직이고있는상태인가 키를눌렀을때
	if (GetAsyncKeyState(VK_LEFT))
	{
		speed -= 1;
		if (speed <= -10)
		{
			speed = -10;
		}
		ch->idir = moveleft;
		
	}

	


	else if (GetAsyncKeyState(VK_RIGHT))
	{
		speed += 1;
		if (speed >= 10)
		{
			speed = 10;
		}
		ch->idir = moveright;
	}
	else
	{
		if (speed > 0)
		{
			speed -= 1;

			ch->idir = moveidleright;
		}
		if (speed < 0)
		{
			speed += 1;
			ch->idir = moveidleleft;
		}
		


	}
	//x축움직이기
	m_playerrc.left = m_playerrc.left + speed;
	m_playerrc.right = m_playerrc.right + speed;
	
	//점프
	if (isjumping)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{

			jump = -20;

		}
		isjumping = false;
	}
	
	
//안움직일때 
	
	

	jump += gravity;
	
	m_playerrc.bottom = m_playerrc.bottom + jump;
	m_playerrc.top = m_playerrc.top + jump;
	//y축 충돌
	//땅 충돌
	if (m_playerrc.bottom>=m_rc.top)
	{
		m_playerrc.top = m_playerrc.bottom-radius;
		m_playerrc.bottom = m_rc.top;
		jump = 0;
		isjumping = true;
		
	}
	//천장충돌
	
	//x축 충돌
	if (m_playerrc.left <= rc.left)
	{
		m_playerrc.left = rc.left;
		m_playerrc.right = m_playerrc.left+ radius;
	}
	if (m_playerrc.right >= rc.right)
	{

		m_playerrc.left = m_playerrc.right-radius;
		m_playerrc.right = rc.right - radius;
	}
	

	//발판과의 충돌처리
	//e_rc.left 와 pt.x +radius 의충돌 밑으로쳐박혀야할때
	//충돌 했을때
	if (IntersectRect(&rcTemp, &m_enemyrc, &m_playerrc))
	{
		
		if (rcTemp.right - rcTemp.left >= rcTemp.bottom - rcTemp.top)
		{
			//가로가 더김 밑에서 충돌
			if (m_playerrc.top +25>=m_enemyrc.bottom-25)
			{
				m_playerrc.top = m_playerrc.top + (rcTemp.bottom - rcTemp.top);
				m_playerrc.bottom = m_playerrc.top + radius;
				
			}
			//가로가 더김 위에서 충돌
			if (m_playerrc.bottom-25 <= m_enemyrc.top+25)
			{
				m_playerrc.bottom = m_playerrc.bottom - (rcTemp.bottom - rcTemp.top);
				m_playerrc.top = m_playerrc.bottom - radius;
				jump = 0;
				isjumping = true;
			}
		}
		


		//세로가 더김 옆에서 충돌
		if (rcTemp.bottom - rcTemp.top >= rcTemp.right - rcTemp.left)
		{
			//왼쪽충돌일때
			if (m_playerrc.right-25 <= m_enemyrc.left+ 25)
			{
				m_playerrc.right = m_playerrc.right - (rcTemp.right - rcTemp.left);
				m_playerrc.left = m_playerrc.right - radius;
			}
			//오른쪽충돌일때
			if (m_playerrc.left+ 25 > m_enemyrc.right- 25)
			{
				m_playerrc.left = m_playerrc.left + (rcTemp.right - rcTemp.left);
				m_playerrc.right = m_playerrc.left + radius;
			}
		}
	}
	
	
	
	//발판의 옆에부딪혀서 비비면서 올라갈때
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
	Rectangle(m_hMemDC, m_enemyrc.left, m_enemyrc.top, m_enemyrc.right, m_enemyrc.bottom);//배경에가려버리기
	//배경출력
	ch1->Rendermap(m_hMemDC, 0, 0);
	
	Rectangle(m_hMemDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	/*Rectangle(m_hMemDC, m_playerrc.left, m_playerrc.top, m_playerrc.right, m_playerrc.bottom);*/
	ch2->Rendermap2(m_hMemDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	
	//캐릭터출력
	ch->Render(m_hMemDC,m_playerrc.left,m_playerrc.top,radius);
	
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
	switch (message)											//키보드이벤트처리를위해 윈도우함수를 가져온다. 
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			
		}
		break;
		
		case VK_LEFT:
		{			//왼쪽
			
		}
		break;
		case VK_RIGHT:
		{
						//오른쪽
		}
		break;
		}
	}
	break;
	}
	


	
}

void cMainGame::InitStage(int nStage)							//스테이지초기화
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);


}

void cMainGame::ClearEnemy()									//적군들을 지운다.
{
	/*for (auto p : m_vecEnemy)
	{
		SAFE_DELETE(p);
	}
	m_vecEnemy.clear();*/
}

//void cMainGame::CharacterInit(float _x, float _y, float _size)
//{
//	if (m_bitmap == NULL)
//	{
//		m_bitmap = (HBITMAP)LoadImage(NULL, "mario.bmp", IMAGE_BITMAP, _size * 8, _size, LR_LOADFROMFILE);
//	}
//	BITMAP tmpBm;
//	GetObject(m_bitmap, sizeof(BITMAP), &tmpBm);
//	m_fScale = _size > tmpBm.bmHeight ? tmpBm.bmHeight : _size;
//	m_fx = _x;
//	m_fy = _y;
//}

