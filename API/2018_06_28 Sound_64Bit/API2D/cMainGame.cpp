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
	, m_pSystem(NULL)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	m_pSound->release();
	m_pSystem->close();
	m_pSystem->release();
	/*
	// 사운드 해제
	for (auto p : m_vecSound)
	{
		FMOD_Sound_Release(p);
	}

	// 사운드 시스템 종료
	FMOD_System_Close(m_pSystem);

	// 사운드 시스템 해제
	FMOD_System_Release(m_pSystem);
	*/
	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);

	SAFE_DELETE(m_pUIRoot);

	cImage::Destroy();

	assert(g_setObjectPool.empty() && "지워지지 않은 객체가 있음.");
}

void cMainGame::Init()
{
	System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, NULL);
	
	//m_pSound = new Sound();
	
	m_pSystem->createStream("sound/bgm.mp3", FMOD_DEFAULT, 0, &m_pSound);
	//m_pSystem->createSound("sound/boom.wav", FMOD_DEFAULT, 0, &m_pSound);
	Channel* pChannel = NULL;

	m_pSystem->playSound(FMOD_CHANNEL_FREE, m_pSound, false, &pChannel);

	/*
	FMOD_System_Create(&m_pSystem); // FMOD system 객체 생성
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL); // FMOD system 초기화
	// 사운드 생성
	FMOD_SOUND* pSound = NULL;
	FMOD_System_CreateSound(m_pSystem, "sound/bgm.mp3", FMOD_DEFAULT, 0, &pSound);
	m_vecSound.push_back(pSound);

	// 채널 생성
	m_vecChannel.resize(2);

	// 사운드 재생
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, pSound, 0, &m_vecChannel[0]);
	
	pSound = NULL;
	FMOD_System_CreateSound(m_pSystem, "sound/boom.wav", FMOD_DEFAULT | FMOD_LOOP_NORMAL, 0, &pSound);
	m_vecSound.push_back(pSound);
	*/
	
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

	m_pSystem->update();
	//FMOD_System_Update(m_pSystem);

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
		//FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[1], 0, &m_vecChannel[1]);
	}
	break;
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_RBUTTONDOWN:
	{
		/*
		static float fVolum = 1.0f;
		fVolum -= 0.1;
		FMOD_Channel_SetVolume(m_vecChannel[0], fVolum);
		
		//FMOD_Channel_SetPaused(m_vecChannel[0], true);
		//FMOD_Channel_SetFrequency(m_vecChannel[0], 2.0f);
		float f = 0;
		//FMOD_Channel_GetFrequency(m_vecChannel[0], &f);
		//FMOD_Channel_SetFrequency(m_vecChannel[0], f * 1.5);
		//FMOD_Channel_GetPosition()
		//FMOD_Channel_SetPosition(m_vecChannel[0], 0, FMOD_TIMEUNIT_MS);
		FMOD_BOOL b;
		//FMOD_Channel_IsPlaying(m_vecChannel[0], &b);
		FMOD_RESULT fr = FMOD_Channel_IsPlaying(m_vecChannel[1], &b);
		if (FMOD_OK == fr)
		{
			int a = 0;
		}
		else
		{
			int a = 0;
		}
		*/
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	}
}

