#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "cSpriteSheetAnimation.h"
#include"cMainPlay.h"
#include"cLobby.h"
cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
{	 
}

cMainGame::~cMainGame()
{
	//SOUND 해제
	for (auto p : m_vecSound)
	{
		FMOD_Sound_Release(p);
	}
	m_vecSound.clear();
	//사운드 시스템 종료
	FMOD_System_Close(m_pSystem);

	//사운드 시스템 해제
	FMOD_System_Release(m_pSystem);
	g_pTimeManager->Destroy();
	//이미지 해제
	SAFE_DELETE(m_pMainPlay);
	SAFE_DELETE(m_pMouse);
	SAFE_DELETE(m_pStart);
	SAFE_DELETE(m_pBackImage);
	SAFE_DELETE(m_pLobby);

	
	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);

	//assert(g_setObjectPool.empty() && "지워지지 않은 객체가 있음.");
}

void cMainGame::Init()
{
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	//기본메인설정
	srand((unsigned int)time(NULL));
	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);
	//////////////////////////////////////////////////////////////////////
	//메인 상태 설정

	e_mainstatus = MAINSTATUS::E_MAINLOADING;

	////////////////////////////////////////////////////////////////////

	//메인게임 이미지 생성
	//2. 로딩바 생성

	m_pLobby = new cLobby();
	m_pLobby->Init();
	//3. 싸움화면 스프라이트 출력
	m_pMainPlay = new cMainPlay();

	GetClientRect(g_hWnd, &rcMap);
	m_pBackImage = new cImage("image/stage1.bmp");

	m_pMouse = new cImage("image/cursor.bmp");

	m_pStart = new cImage("image/start.bmp");
	m_fStarttime = 0.f;

	//sound
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);//첫번째인자 fmod, 2번쨰인자 채널의갯수(갯수만큼음원을넣을수잇음)


	//lobby
	FMOD_SOUND* pSound = NULL;
	FMOD_System_CreateSound(m_pSystem, "Sound/ca_lobby.mp3", FMOD_LOOP_NORMAL, 0, &pSound);
	m_vecSound.push_back(pSound);
	//start
	FMOD_System_CreateSound(m_pSystem, "Sound/start.mp3", FMOD_LOOP_OFF, 0, &pSound);
	m_vecSound.push_back(pSound);
	
	//사운드 재생

	FMOD_CHANNEL * pChannel = NULL;
	m_vecChannel.push_back(pChannel);
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[0], 0, &m_vecChannel[0]);

	//// 채널 생성
	m_vecChannel.resize(10);


}


void cMainGame::Update()
{
	
	g_pTimeManager->Update();

	//sound
	//FMOD_System_Update(m_pSystem);

	//////////////////////////////////////////////////////////////
	//1.MAININIT
	//폰트 깜빡이기
	switch (e_mainstatus)
	{
	case  MAINSTATUS::E_MAINLOADING:
	{
		//2.MAINLOADING

		//사운드 생성
		
		m_pLobby->Update();
		if (m_pLobby->GetisStartButton() == true)
		{
			//e_mainstatus = E_MAINFIGHT;
			CHARNAME temp1, temp2;
			temp1 = m_pLobby->Getcharname();
			temp2 = m_pLobby->Getsecondname();
			if (temp1 == RANDOM)
			{
				int randomname = rand() % RANDOM;
				temp1 = (CHARNAME)randomname;
			}
			if (temp2 == RANDOM)
			{
				int randomname = rand() % RANDOM;
				temp2 = (CHARNAME)randomname;
			}
			m_pMainPlay->Init(temp1, temp2);
			e_mainstatus = E_MAINFIGHT;
			m_pLobby->SetisStartButton(false);

			FMOD_Channel_Stop(m_vecChannel[0]);
			FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[1], 0, &m_vecChannel[0]);
		}
		FMOD_Channel_IsPlaying(m_vecChannel[0], &isplay);
		if(!isplay)
			FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[0], 0, &m_vecChannel[0]);
	}break;
	case  MAINSTATUS::E_MAINFIGHT:
	{
		m_fStarttime += g_pTimeManager->GetElapsedTime();
		if (m_fStarttime > 2.f)
		{
			m_isstart = true;
			//m_fStarttime = 0;
		}
		if (m_isstart)
		{

			m_pMainPlay->Update();
			if (m_pMainPlay->GetisWantExit() == true)
			{
				PostQuitMessage(0);
			}
			if (m_pMainPlay->GetisPlayerDie() == true)
			{
				m_isstart = false;
				m_fStarttime = 0.f;
				e_mainstatus = E_MAINLOADING;
			}
			if (m_pMainPlay->GetisSecondPlayerDie() == true)
			{
				m_isstart = false;
				m_fStarttime = 0.f;
				e_mainstatus = E_MAINLOADING;
			}
		}
	}break;
	default:
		break;
	}
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
	FillRect(m_hMemDC, &rc, GetSysColorBrush(/*COLOR_GRAYTEXT*//*COLOR_WINDOW*/COLOR_BACKGROUND));
	//////////////////////////////////////////////////////////////////////////
	

	//1.배경 출력
	switch (e_mainstatus)
	{
	case MAINSTATUS::E_MAINLOADING:
	{
		//로딩중이냐
		m_pLobby->Render(m_hMemDC);

	}break;
	case MAINSTATUS::E_MAINFIGHT:
	{

		m_pBackImage->RenderCharater(m_hMemDC, rcMap, true);
		
		RECT rcStart; rcStart.left = 100; rcStart.top = 200; rcStart.right = 600; rcStart.bottom = 400;
		m_pMainPlay->Render(m_hMemDC);

		if (!m_isstart)
			m_pStart->RenderCharater(m_hMemDC, rcStart,true);

		//Rectangle(m_hMemDC, rcTempplayer.left, rcTempplayer.top, rcTempplayer.right, rcTempplayer.bottom);

	}break;
	default:
		break;
	}
	ShowCursor(false);
	//마우스
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	RECT mouse; mouse.left = pt.x; mouse.top = pt.y; mouse.right = pt.x + 30; mouse.bottom = pt.y + 30;
	ShowCursor(false);
	m_pMouse->RenderCharater(m_hMemDC, mouse, true);
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainPlay&& m_isstart)
		m_pMainPlay->WndProc(hWnd, message, wParam, lParam);
}