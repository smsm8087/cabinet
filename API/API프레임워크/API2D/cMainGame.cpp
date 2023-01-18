#include "stdafx.h"
#include "cMainGame.h"
#include"cCharater.h"
//#include "cAirplane.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)										//�ڵ��ʱ�ȭ�� �÷��̾�Ŭ���� �����Ҵ�
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

cMainGame::~cMainGame()										//�Ҹ��� : ��ũ���Լ��� ��� ����������Ʈ�� �����Ҵ�� ��ü�� �����.
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

void cMainGame::Init()										//�ʱ�ȭ���ΰ���
{
	srand((unsigned int)time(NULL));						//�̰ž��ϸ� �����Լ� ����������������
	//InitStage(1);											//1���������� �ʱ�ȭ
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_rc.left = rc.left;
	m_rc.right = rc.right;
	m_rc.top = rc.bottom / 3 * 2;
	m_rc.bottom = rc.bottom;
	//�ٴ� ����� ��

	//�÷��̾� ����
	radius = 50;

	pt.x = rc.left + 150;

	pt.y = rc.bottom / 3 * 2;
	m_playerrc.left = pt.x;
	m_playerrc.top = pt.y - radius;
	m_playerrc.right = pt.x + radius;
	m_playerrc.bottom = pt.y;
	

	//���� ����
	
	m_enemyrc.left = 730;
	m_enemyrc.top = 180;
	m_enemyrc.right = 780;
	m_enemyrc.bottom = 230;
	GetClientRect(g_hWnd, &rc);
	
	//�ӵ� ����
	speed = 0;
	a = 0;
	jump = 0;
	isjumping = false;
}

void cMainGame::Update()									//������Ʈ
{
	
	
	g_pTimeManager->Update();								//�̱���� Ÿ�ӸŴ����� ������Ʈ�Ѵ�.
	RECT rc;
	RECT rcTemp;
	GetClientRect(g_hWnd, &rc);
	
	
//�����̰��ִ»����ΰ� Ű����������
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
	//x������̱�
	m_playerrc.left = m_playerrc.left + speed;
	m_playerrc.right = m_playerrc.right + speed;
	
	//����
	if (isjumping)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{

			jump = -20;

		}
		isjumping = false;
	}
	
	
//�ȿ����϶� 
	
	

	jump += gravity;
	
	m_playerrc.bottom = m_playerrc.bottom + jump;
	m_playerrc.top = m_playerrc.top + jump;
	//y�� �浹
	//�� �浹
	if (m_playerrc.bottom>=m_rc.top)
	{
		m_playerrc.top = m_playerrc.bottom-radius;
		m_playerrc.bottom = m_rc.top;
		jump = 0;
		isjumping = true;
		
	}
	//õ���浹
	
	//x�� �浹
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
	

	//���ǰ��� �浹ó��
	//e_rc.left �� pt.x +radius ���浹 �������Ĺ������Ҷ�
	//�浹 ������
	if (IntersectRect(&rcTemp, &m_enemyrc, &m_playerrc))
	{
		
		if (rcTemp.right - rcTemp.left >= rcTemp.bottom - rcTemp.top)
		{
			//���ΰ� ���� �ؿ��� �浹
			if (m_playerrc.top +25>=m_enemyrc.bottom-25)
			{
				m_playerrc.top = m_playerrc.top + (rcTemp.bottom - rcTemp.top);
				m_playerrc.bottom = m_playerrc.top + radius;
				
			}
			//���ΰ� ���� ������ �浹
			if (m_playerrc.bottom-25 <= m_enemyrc.top+25)
			{
				m_playerrc.bottom = m_playerrc.bottom - (rcTemp.bottom - rcTemp.top);
				m_playerrc.top = m_playerrc.bottom - radius;
				jump = 0;
				isjumping = true;
			}
		}
		


		//���ΰ� ���� ������ �浹
		if (rcTemp.bottom - rcTemp.top >= rcTemp.right - rcTemp.left)
		{
			//�����浹�϶�
			if (m_playerrc.right-25 <= m_enemyrc.left+ 25)
			{
				m_playerrc.right = m_playerrc.right - (rcTemp.right - rcTemp.left);
				m_playerrc.left = m_playerrc.right - radius;
			}
			//�������浹�϶�
			if (m_playerrc.left+ 25 > m_enemyrc.right- 25)
			{
				m_playerrc.left = m_playerrc.left + (rcTemp.right - rcTemp.left);
				m_playerrc.right = m_playerrc.left + radius;
			}
		}
	}
	
	
	
	//������ �����ε����� ���鼭 �ö󰥶�
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
	Rectangle(m_hMemDC, m_enemyrc.left, m_enemyrc.top, m_enemyrc.right, m_enemyrc.bottom);//��濡����������
	//������
	ch1->Rendermap(m_hMemDC, 0, 0);
	
	Rectangle(m_hMemDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	/*Rectangle(m_hMemDC, m_playerrc.left, m_playerrc.top, m_playerrc.right, m_playerrc.bottom);*/
	ch2->Rendermap2(m_hMemDC, m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	
	//ĳ�������
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
	switch (message)											//Ű�����̺�Ʈó�������� �������Լ��� �����´�. 
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
		{			//����
			
		}
		break;
		case VK_RIGHT:
		{
						//������
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

