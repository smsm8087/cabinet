#include "stdafx.h"
#include "cMainGame.h"
//#include "cAirplane.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cBulletManager.h"
#include "WormPlayer.h"
#include "Food.h"
#include "ConvexHull.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, mbGameOver(false)
	, m_fPassedIdleTime(0)
	, m_fIdleTime(0.05f)
	, mConvexHull(NULL)
	//, m_pPlayer(new cPlayer)
{
}

cMainGame::~cMainGame()
{
	//SAFE_DELETE(m_pPlayer);
	
	//ClearEnemy();
	//지렁이 게임 저장
	//mPlayer->Save();

	//ConvexHull 삭제
	SAFE_DELETE(mConvexHull);

	//지렁이게임 삭제 플레이어랑 먹이랑
	//Release();
	//cTimeManager::GetInstance()->Destroy();

	g_pTimeManager->Destroy();
	g_pBulletManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init(HWND hwnd)
{
	srand((unsigned int)time(NULL));
	mhWnd = hwnd;
	InitStage(1);
	RECT winrc;
	GetClientRect(hwnd, &winrc);


	//지렁이 게임 초기화
	//mPlayer = new WormPlayer;
	//mFood = new Food;
	//mPlayer->Init(winrc.right/2, winrc.bottom/2, hwnd);
	//auto a = rand() % winrc.right;
	//auto b = rand() % winrc.bottom;
	//mFood->Init(a, b,hwnd);

	//ConvexHull 초기화
	mConvexHull = new ConvexHull;
	mConvexHull->Init();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	m_fPassedIdleTime += g_pTimeManager->GetElapsedTime();

	while (m_fPassedIdleTime >= m_fIdleTime)
	{
		//지렁이 게임 충돌처리 및 행동
		//if (!mbGameOver)
		//{
		//	//플레이어 작업해줌
		//	mPlayer->Update();
		//	//m_fPassedIdleTime = 0.0f;

		//	//먹이딱히 하는건 아직없음
		//	mFood->Update();
		//	float fpx = mPlayer->GetList()->front().posx;
		//	float fpy = mPlayer->GetList()->front().posy;

		//	auto plistiter = mPlayer->GetList()->begin();
		//	while (plistiter != mPlayer->GetList()->end())
		//	{
		//		//플레이 리스트 첫번쨰인 머리는 충돌제외
		//		if ((plistiter) != mPlayer->GetList()->begin())
		//		{
		//			RECT rcc, headrc, listrc;
		//			headrc = RectMakeCenter(fpx, fpy, mPlayer->GetDiameter(), mPlayer->GetDiameter());
		//			listrc = RectMakeCenter((*plistiter).posx, (*plistiter).posy, mPlayer->GetDiameter(), mPlayer->GetDiameter());
		//			if (IntersectRect(&rcc, &listrc, &headrc))
		//			{
		//				RECT rci;
		//				GetClientRect(mhWnd, &rci);
		//				//리스트 초기화 해주고
		//				mPlayer->GetList()->clear();
		//				PosXY posi;
		//				posi.posx = rci.right / 2;
		//				posi.posy = rci.bottom / 2;
		//				mPlayer->GetList()->push_back(posi);
		//				mPlayer->Save();
		//				mbGameOver = true;
		//				//mIsKeyDown = 0;
		//				break;
		//			}
		//		}
		//		++plistiter;
		//	}
		//	float px = mPlayer->GetPosX();
		//	float py = mPlayer->GetPosY();
		//	float fx = mFood->GetPosX();
		//	float fy = mFood->GetPosY();
		//	float pdia = mPlayer->GetDiameter();
		//	float fdia = mFood->GetDiameter();

		//	float dix = px - fx;
		//	float diy = py - fy;

		//	float dis = sqrt((dix * dix) + (diy * diy));
		//	float disdia = pdia / 2 + fdia / 2;
		//	//충돌!
		//	if (dis < disdia)
		//	{
		//		RECT winrc;
		//		GetClientRect(mhWnd, &winrc);
		//		mFood->Init(rand() % winrc.right, rand() % winrc.bottom, mhWnd);
		//		auto plist = mPlayer->GetList();
		//		PosXY pos;
		//		pos.posx = fx;
		//		pos.posy = fy;
		//		plist->push_back(pos);

		//	}
		//}
		mConvexHull->Update();

		m_fPassedIdleTime -= m_fIdleTime;
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
	}
	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_WINDOW));

	//지렁이 게임 출력
	//if (!mbGameOver)
	//{
	//	mPlayer->Render(m_hMemDC);

	//	mFood->Render(m_hMemDC);
	//}
	//else
	//{
	//	char szBuf[16];
	//	wsprintf(szBuf, "GameOver");
	//	TextOut(m_hMemDC, rc.right / 2, rc.bottom/2, szBuf, strlen(szBuf));
	//}

	mConvexHull->Render(m_hMemDC);
	//m_pPlayer->Render(m_hMemDC);
	//for (auto p : m_vecEnemy)
	//{
	//	p->Render(m_hMemDC);
	//}

	//g_pBulletManager->Render(m_hMemDC);

	//char szBuf[16];
	//wsprintf(szBuf, "%X", GetAsyncKeyState(VK_SPACE));
	//TextOut(m_hMemDC, 10, 10, szBuf, strlen(szBuf));

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
		case VK_SPACE:
		{

			//cTimeManager* p = new cTimeManager;
 			//m_pPlayer->Fire();
			//InitStage(1);
		}
		break;
		case '7':
		{
			mbGameOver = false;
		}
		break;
		}
	}
	break;
	}
}

void cMainGame::Release()
{
	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mFood);
}

void cMainGame::InitStage(int nStage)
{
	//RECT rc;
	//GetClientRect(g_hWnd, &rc);

	//m_pPlayer->Init(cVector2(rc.right / 2, rc.bottom / 2));

	//ClearEnemy();

	//int nNumEnemy = 1;
	//m_vecEnemy.resize(nNumEnemy);
	//for (int i = 0; i < nNumEnemy; i++)
	//{
	//	m_vecEnemy[i] = new cEnemy;
	//	m_vecEnemy[i]->AddTarget(m_pPlayer);

	//	m_pPlayer->AddTarget(m_vecEnemy[i]);

	//	do
	//	{
	//		float x = rand() % (rc.right - (int)m_vecEnemy[i]->GetFullRadius() * 2);
	//		x += m_vecEnemy[i]->GetFullRadius();
	//		float y = rand() % (rc.bottom - (int)m_vecEnemy[i]->GetFullRadius() * 2);
	//		y += m_vecEnemy[i]->GetFullRadius();

	//		cVector2 vPos(x, y);
	//		m_vecEnemy[i]->Init(vPos);
	//	} while (CheckCollision(m_vecEnemy[i]));
	//}
}

void cMainGame::ClearEnemy()
{
	//for (auto p : m_vecEnemy)
	//{
	//	SAFE_DELETE(p);
	//}
	//m_vecEnemy.clear();
}

bool cMainGame::CheckCollision(cAirplane * pAirplane)
{
	//if (pAirplane && CheckCollision(pAirplane, m_pPlayer))
	//{
	//	return true;
	//}

	//for (auto p : m_vecEnemy)
	//{
	//	if (p == pAirplane) continue;
	//	if (p == NULL) break;
	//	if(CheckCollision(pAirplane, p))
	//		return true;
	//}
	return false;
}

bool cMainGame::CheckCollision(cAirplane * pAirplane1, cAirplane * pAirplane2)
{
	if (pAirplane1 && pAirplane2)
	{
		cVector2 v1 = pAirplane1->GetPosition();
		cVector2 v2 = pAirplane2->GetPosition();
		float r1 = pAirplane1->GetBodyRadius();
		float r2 = pAirplane2->GetBodyRadius();
		cVector2 v = v2 - v1;
		if ((r1 + r2) * (r1 + r2) > (v2 - v1).LenSq())
			return true;
	}
	return false;
}
