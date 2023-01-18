#include "stdafx.h"
#include "cMainGame.h"
#include "cMapImage.h"
#include "cCharacterImage.h"
#include "cInventory.h"


cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_inventf(false)
	, LastMenu(0)
	, CurrMenu(0)
{

}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{

	m_pCharImage = new cCharacterImage("ĳ���͸���Ÿ.bmp");
	m_pMapImage = new cMapImage("����.bmp");
	m_pMapForest = new cMapImage("����.bmp");
	InvenToryBit();

	if (!m_pMapImage or !m_pCharImage)
		return;

}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	CharMove();

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
	///////////////////////  Render �κ� �־���  ///////////////////////
	///////////////////////////////////////////////////////////////////
	
	if (m_pCharImage->GetMapNum() == MAP_VILLAGE)
	{
		m_pMapImage->Render(m_hMemDC);

	}
	else if (m_pCharImage->GetMapNum() == MAP_FIELD)
	{
		m_pMapForest->Render(m_hMemDC);
	}
	if (m_inventf)
	{
		switch (CurrMenu)
		{
		case MENU_ITEM :
			m_pInventory_item->Render(m_hMemDC);
			break;
		case MENU_BOOK:
			m_pInventory_book->Render(m_hMemDC);
			break;
		default:
			break;
		}
		
	}

	m_pCharImage->Render(m_hMemDC);

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
		case WM_KEYUP:
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
			}
		}
		break;
		}
}

void cMainGame::CharMove()
{
	/*
	0x0001
	������ ���� ���� �ְ� ȣ�� �������� �������� ���� ����
	*/
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		m_inventf = true;
		count += 1;
		if (count == 2)
		{
			m_inventf = false;
			count = 0;
			CurrMenu = MENU_ITEM;
		}

	}
	if (!m_inventf)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			m_pCharImage->SetY(m_pCharImage->GetY() - 8);
			y = m_pCharImage->GetY();
			m_pCharImage->IsMove = true;
			m_pCharImage->idir = DIR_UP;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			m_pCharImage->SetY(m_pCharImage->GetY() + 8);
			y = m_pCharImage->GetY();
			m_pCharImage->IsMove = true;
			m_pCharImage->idir = DIR_DOWN;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			m_pCharImage->SetX(m_pCharImage->GetX() - 8);
			x = m_pCharImage->GetX();
			m_pCharImage->IsMove = true;
			m_pCharImage->idir = DIR_LEFT;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			m_pCharImage->SetX(m_pCharImage->GetX() + 8);
			x = m_pCharImage->GetX();
			m_pCharImage->IsMove = true;
			m_pCharImage->idir = DIR_RIGHT;
		}
		//�� �̵�
		if ((y < 0) && (x >= 260 && x <= 326))
		{
			m_pCharImage->m_MapNum = MAP_FIELD;
			m_pCharImage->SetX(182);
		}
		if ((y < 0) && (x >= 175 && x <= 230))
		{
			m_pCharImage->m_MapNum = MAP_VILLAGE;
			m_pCharImage->SetX(270);
		}
	}
	else
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			if (CurrMenu == MENU_BOOK)
			{
				CurrMenu = MENU_ITEM;
				//LastMenu = MENU_ITEM;
				//BeforeMenu = MENU_BOOK;
			}
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			if (CurrMenu == MENU_ITEM)
			{
				CurrMenu = MENU_BOOK;
				//LastMenu = MENU_BOOK;
				//BeforeMenu = MENU_ITEM;
			}
		}
	}
	
}

void cMainGame::InvenToryBit()
{
	m_pInventory_item = new cInventory("����â ����ǰ.bmp");
	m_pInventory_book = new cInventory("����â ����.bmp");
}
	
