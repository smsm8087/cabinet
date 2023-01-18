#include "stdafx.h"
#include "cMainGame.h"
#include "cUIObject.h"
#include "cUIWindow.h"
#include "cUISlotContainer.h"
#include "cUIItemImage.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_pUIRoot(NULL)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	

	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);

	SAFE_DELETE(m_pUIRoot);

	cImage::Destroy();

	assert(g_setObjectPool.empty() && "지워지지 않은 객체가 있음.");
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pUIRoot = new cUIObject();
	m_pUIRoot->SetShow(true); 
	m_pUIRoot->SetSize(ST_SIZE(rc.right, rc.bottom));
	

	// 인벤 1
	cUIWindow* pWindow = new cUIWindow();
	pWindow->Init(ST_SIZE(369, 328));
	pWindow->SetTitleBarBack(cImage::Create("UI/bar.bmp"));
	pWindow->SetImage(cImage::Create("UI/inven.bmp"));
	pWindow->SetShow(true);
	pWindow->SetDepth(1);
	m_pUIRoot->AddChild(pWindow);

	cUISlotContainer* pSlotContainer = new cUISlotContainer;
	pSlotContainer->Init(ST_SIZE(349, 278));
	pSlotContainer->SetPosition(cUtil::MakePoint(10, 40));
	pSlotContainer->SetSlot(20, "UI/slot.bmp");
	pWindow->AddChild(pSlotContainer);

	// 인벤 2
	pWindow = new cUIWindow();
	pWindow->Init(ST_SIZE(369, 328));
	pWindow->SetPosition(cUtil::MakePoint(400, 50));
	pWindow->SetTitleBarBack(cImage::Create("UI/bar.bmp"));
	pWindow->SetImage(cImage::Create("UI/inven.bmp"));
	pWindow->SetShow(true);
	pWindow->SetDepth(1);
	m_pUIRoot->AddChild(pWindow);

	pSlotContainer = new cUISlotContainer;
	pSlotContainer->Init(ST_SIZE(349, 278));
	pSlotContainer->SetPosition(cUtil::MakePoint(10, 40));
	pSlotContainer->SetSlot(20, "UI/slot.bmp");
	pWindow->AddChild(pSlotContainer);

	cUIItemImage* pItemImage = new cUIItemImage;
	pItemImage->SetImage(cImage::Create("UI/1.bmp"));
	pItemImage->SetSize(ST_SIZE(40, 40));
	pSlotContainer->AddItem(2, pItemImage);

	pItemImage = new cUIItemImage;
	pItemImage->SetImage(cImage::Create("UI/2.bmp"));
	pItemImage->SetSize(ST_SIZE(40, 40));
	pSlotContainer->AddItem(4, pItemImage);

	pItemImage = new cUIItemImage;
	pItemImage->SetImage(cImage::Create("UI/3.bmp"));
	pItemImage->SetSize(ST_SIZE(40, 40));
	pSlotContainer->AddItem(10, pItemImage);

	//m_pUIRoot->SetDebugMode(true);
	/*
	m_pUIRoot = new cUIObject();
	cUIObject* pTemp = NULL;
	pTemp = new cUIObject();
	pTemp->m_nDepth = 3;
	m_pUIRoot->AddChild(pTemp);

	pTemp = new cUIObject();
	pTemp->m_nDepth = 6;
	m_pUIRoot->AddChild(pTemp);

	pTemp = new cUIObject();
	pTemp->m_nDepth = 1;
	m_pUIRoot->AddChild(pTemp);

	pTemp = new cUIObject();
	pTemp->m_nDepth = 4;
	m_pUIRoot->AddChild(pTemp);
	cUIObject* pParent = pTemp;

	
	
	pTemp = new cUIObject();
	pTemp->m_nDepth = 4;
	pParent->AddChild(pTemp);

	pTemp = new cUIObject();
	pTemp->m_nDepth = 10;
	pParent->AddChild(pTemp);

	pTemp = new cUIObject();
	pTemp->m_nDepth = 1;
	pParent->AddChild(pTemp);

	pTemp = new cUIObject();
	pTemp->m_nDepth = 5;
	pParent->AddChild(pTemp);

	int a = 0;
	*/

	/*
	Window
	{
		Depth:1
		ToggleKey:"S"
		Title:"Store"
		SlotContainer
		{
			Position:20, 30
			Size:300, 200
			NumSlot:20
			SlotImage:"UI/slot.bmp"
		}
		Button
		{
			Position:200, 300
			Size:30, 20
			NormalImage:"UI/Nor.bmp"
			MouseOverImage:"UI/Mov.bmp"
			SelectedImage:"UI/Sel.bmp"
		}
	}
	*/
}


void cMainGame::Update()
{
	g_pTimeManager->Update();

	if (m_pUIRoot) m_pUIRoot->Update(NULL);

	g_pAutoReleasePool->Drain();
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
	

	if (m_pUIRoot) m_pUIRoot->Render(m_hMemDC);
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
	if (m_pUIRoot) 
		m_pUIRoot->WndProc(hWnd, message, wParam, lParam);
	
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
	}
	break;
	case WM_MOUSEMOVE:
	{
	}
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

