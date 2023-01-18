#include "stdafx.h"
#include "cMainPlay.h"
#include"cMap.h"
#include"cPlayer.h"
#include"cBomb.h"
#include"cItem.h"
#include"cImage.h"
cMainPlay::cMainPlay()
{
}


cMainPlay::~cMainPlay()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pPlayer2);
	SAFE_DELETE(m_pTree13);
	SAFE_DELETE(m_pPlayerWin);
	SAFE_DELETE(m_pPlayerMark);
	SAFE_DELETE(m_pSecondMark);
	SAFE_DELETE(m_pSecondPlayerWin);
	if (!m_vecItem.empty())
	{
		for (auto p : m_vecItem)
		{
			SAFE_DELETE(p);
		}
		m_vecItem.clear();
	}
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
}

void cMainPlay::Init(CHARNAME player,CHARNAME secondplayer)
{
	//sound
	FMOD_System_Create(&m_pSystem);
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);//첫번째인자 fmod, 2번쨰인자 채널의갯수(갯수만큼음원을넣을수잇음)


															//lobby
	FMOD_SOUND* pSound = NULL;
	FMOD_System_CreateSound(m_pSystem, "Sound/ca_bgm.mp3", FMOD_LOOP_NORMAL, 0, &pSound);//0
	m_vecSound.push_back(pSound);
	FMOD_System_CreateSound(m_pSystem, "Sound/bomb.mp3", FMOD_LOOP_OFF, 0, &pSound);//1
	m_vecSound.push_back(pSound);
	FMOD_System_CreateSound(m_pSystem, "Sound/boom.mp3", FMOD_LOOP_OFF, 0, &pSound);//2
	m_vecSound.push_back(pSound);
	FMOD_System_CreateSound(m_pSystem, "Sound/item.mp3", FMOD_LOOP_OFF, 0, &pSound);//3
	m_vecSound.push_back(pSound);
	FMOD_System_CreateSound(m_pSystem, "Sound/pop.mp3", FMOD_LOOP_OFF, 0, &pSound);//4
	m_vecSound.push_back(pSound);
	FMOD_System_CreateSound(m_pSystem, "Sound/win.mp3", FMOD_LOOP_OFF, 0, &pSound);//5
	m_vecSound.push_back(pSound);

	FMOD_CHANNEL * pChannel = NULL;
	m_vecChannel.push_back(pChannel);
	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[0], 0, &m_vecChannel[0]);

	//// 채널 생성
	m_vecChannel.resize(10);
	//////

	m_pMap = new cMap();
	m_pMap->Init();
	m_pPlayer = new cPlayer();
	m_pPlayer->Init(STAGE_START_X + PLAYER_X / 2 - 10, STAGE_START_Y,103, player);
	m_pPlayer2 = new cPlayer();
	m_pPlayer2->Init(STAGE_END_X - PLAYER_X / 2 + 10, STAGE_END_Y - PLAYER_Y,145, secondplayer);
	m_pTree13 = new cImage("image/tree13.bmp");
	m_pPlayerMark = new cImage("image/player_mark.bmp");
	m_pSecondMark = new cImage("image/player_mark.bmp");
	m_pPlayerWin = new cImage("image/win_1p.bmp");
	m_pSecondPlayerWin = new cImage("image/win_2p.bmp");
	m_fWinTime = 0.f;
	if (!m_vecItem.empty())
	{
		for (auto p : m_vecItem)
		{
			SAFE_DELETE(p);
		}
		m_vecItem.clear();
	}
}

void cMainPlay::Update()
{
	m_pMap->Update();
	for (auto p : m_vecItem)
	{
		p->Update();
	}
	//1p
	KeyDownPlayer();
	//2p
	KeyDownSecondPlayer();
	m_pPlayer->Update();
	FirstPlayer();
	PlayerToItemCollision();
	m_pPlayer2->Update();
	SecondPlayer();
	SecondPlayerToItemCollision();
	BombToBombPlayer();
	BombToBombSecondPlayer();
	PlayerBombToSecondPlayer();
	SecondBombPlayerToPlayer();
	PlayerToSecondPlayer();
	ItemToBombCollision();
	if (m_pPlayer->e_charmove == POP || m_pPlayer2->e_charmove == POP)
	{
		FMOD_Channel_IsPlaying(m_vecChannel[4], &ispopplay);
		if(!ispopplay)
			FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[4], 0, &m_vecChannel[4]);
	}
	for (auto p : m_pPlayer->GetvecBomb())
	{
		if (p->GetPopBomb() == true)
		{
			FMOD_Channel_IsPlaying(m_vecChannel[2], &ispopbombplay);
			if (!ispopbombplay)
				FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[2], 0, &m_vecChannel[2]);

		}
	}
	for (auto p : m_pPlayer2->GetvecBomb())
	{
		if (p->GetPopBomb() == true)
		{
			FMOD_Channel_IsPlaying(m_vecChannel[2], &issecondpopbombplay);
			if (!issecondpopbombplay)
				FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[2], 0, &m_vecChannel[2]);
		}
	}
	if (m_pPlayer->e_charmove == DIE&& m_pPlayer2->e_charmove != DIE)
	{
		//2pWin
		m_isBeforeDiePlayer = true;
		if (m_isBeforeDiePlayer)
		{
			m_fWinTime += g_pTimeManager->GetElapsedTime();
			if (m_fWinTime >= 3.f)
			{
				m_fWinTime -= 3.f;
				m_pPlayer->e_charmove = STAND;
				m_isBeforeDiePlayer = false;
				m_isPlayerDie = true;
			}
		}
		FMOD_Channel_IsPlaying(m_vecChannel[5], &issecondplay);
		if (!issecondplay)
			FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[5], 0, &m_vecChannel[5]);

		FMOD_Channel_Stop(m_vecChannel[0]);
	}
	else
	{
		m_isBeforeDiePlayer = false;
		m_isPlayerDie = false;
	}
	if (m_pPlayer2->e_charmove == DIE&& m_pPlayer->e_charmove != DIE)
	{
		//1pWin
		m_isBeforeDieSecondPlayer = true;
		if (m_isBeforeDieSecondPlayer)
		{
			m_fWinTime += g_pTimeManager->GetElapsedTime();
			if (m_fWinTime >= 3.f)
			{
				m_fWinTime -= 3.f;
				m_pPlayer2->e_charmove = STAND;
				m_isBeforeDieSecondPlayer = false;
				m_isSecondPlayerDie = true;
			}
		}
		FMOD_Channel_IsPlaying(m_vecChannel[5], &isplay);
		if (!isplay)
			FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[5], 0, &m_vecChannel[5]);
		FMOD_Channel_Stop(m_vecChannel[0]);
		FMOD_Channel_Stop(m_vecChannel[1]);
		FMOD_Channel_Stop(m_vecChannel[2]);
		FMOD_Channel_Stop(m_vecChannel[3]);
		FMOD_Channel_Stop(m_vecChannel[4]);

	}
	else
	{
		m_isBeforeDieSecondPlayer = false;
		m_isSecondPlayerDie = false;
	}
	//나가기 버튼
	RECT rcExit; SetRect(&rcExit, 647, 562, 647 + 143, 562 + 30);
	POINT ptCursor;
	GetCursorPos(&ptCursor);
	ScreenToClient(g_hWnd, &ptCursor);
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		if (PtInRect(&rcExit, ptCursor))
		{
			m_isWantExit = true;
		}
		else
		{
			m_isWantExit = false;
		}
	}

}

void cMainPlay::Render(HDC hdc)
{
		
	m_pMap->Render(hdc);
	m_pPlayer->Render(hdc);
	m_pPlayer2->Render(hdc);
	for (auto p : m_vecItem)
	{
		p->Render(hdc);
	}
	//tree13 맨밑트리는 제일 나중에
	RECT rcTree; rcTree.left = 60; rcTree.top = 600 - 40 - m_pTree13->GetstSize().nHeight; rcTree.right = 800 - 220; rcTree.bottom = 600 - 40;
	m_pTree13->RenderCharater(hdc, rcTree, true);

	//MARK
	RECT rcPmark, rcSpmark, rcSourceMark, rcSourceSecondMark;
	SetRect(&rcPmark, m_pPlayer->GetptPlayer().x-30, m_pPlayer->GetptPlayer().y-70,
		m_pPlayer->GetptPlayer().x + 30, m_pPlayer->GetptPlayer().y -40);
	SetRect(&rcSpmark, m_pPlayer2->GetptPlayer().x - 30, m_pPlayer2->GetptPlayer().y - 70,
		m_pPlayer2->GetptPlayer().x + 30, m_pPlayer2->GetptPlayer().y - 40);
	SetRect(&rcSourceMark, 0, 0, 50, 30);
	SetRect(&rcSourceSecondMark, 50, 0, 100, 30);
	m_pPlayerMark->TransparentRender(hdc, rcPmark, rcSourceMark);
	m_pSecondMark->TransparentRender(hdc, rcSpmark, rcSourceSecondMark);

	//win
	RECT rcWin;
	SetRect(&rcWin, 100, 200, 600, 400);
	if (m_isBeforeDiePlayer)
	{
		//2p
		m_pSecondPlayerWin->RenderCharater(hdc,rcWin,true);
	}
	else if (m_isBeforeDieSecondPlayer)
	{
		//1p
		m_pPlayerWin->RenderCharater(hdc,rcWin,true);
	}
}

bool cMainPlay::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 'D':
		{
			if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
			{
				m_pPlayer->e_charmove = STAND;
				m_pPlayer->Setisleftmove(false);
			}

		}break;
		case 'G':
		{
			if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
			{
				m_pPlayer->e_charmove = STAND;
				m_pPlayer->Setisrightmove(false);
			}

		}break;
		case 'R':
		{
			if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
			{
				m_pPlayer->e_charmove = STAND;
				m_pPlayer->Setisupmove(false);
			}

		}break;
		case 'F':
		{
			if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
			{
				m_pPlayer->e_charmove = STAND;
				m_pPlayer->Setisdownmove(false);
			}

		}break;
		case VK_LEFT:
		{
			if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
			{
				m_pPlayer2->e_charmove = STAND;
				m_pPlayer2->Setisleftmove(false);
			}

		}break;
		case VK_RIGHT:
		{
			if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
			{
				m_pPlayer2->e_charmove = STAND;
				m_pPlayer2->Setisrightmove(false);
			}

		}break;
		case VK_UP:
		{
			if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
			{
				m_pPlayer2->e_charmove = STAND;
				m_pPlayer2->Setisupmove(false);
			}

		}break;
		case VK_DOWN:
		{
			if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
			{
				m_pPlayer2->e_charmove = STAND;
				m_pPlayer2->Setisdownmove(false);
			}

		}break;
		case VK_ESCAPE:
		{
			PostQuitMessage(0);
		}break;
		case VK_LCONTROL:
		{
			int a = 0;
		}break;
		case VK_LSHIFT:
		{
			int a = 0;
		}break;
		case VK_RSHIFT:
		{
			int a = 0;
		}break;
		default:
			break;
		}
	}break;
	}
	return false;
}

void cMainPlay::FirstPlayer()
{
	//1p 물폭탄 처리

	/////////////////////////////////////
	POINT pt;
	pt.x = m_pPlayer->GetptPlayer().x;
	pt.y = m_pPlayer->GetptPlayer().y + 10;
	for (size_t i = 0; i < STAGE_COL; i++)
	{
		for (size_t j = 0; j < STAGE_ROW; j++)
		{
			if (PtInRect(&m_pMap->GetRectTile(i, j), pt))
			{
				m_pPlayer->SetRow(j);
				m_pPlayer->SetCol(i);
			}
		}
	}
	for (auto p : m_pPlayer->GetvecBomb())
	{
		p->Update();
		if (p->GetPopBomb() == true)
		{
			m_pMap->SetTile(p->GetCol(), p->GetRow(), 0);
		}
		else
		{
			m_pMap->SetTile(p->GetCol(), p->GetRow(), 7);//7은 아무것도없는상태로 못가게하려고 그냥넣은 숫자
		}
	}
	//////////////////////////////
	//1p
	///////////////////////맵충돌
	//상
	if (m_pMap->GetTile(m_pPlayer->GetCol() - 1, m_pPlayer->GetRow()) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer->GetCol() - 1, m_pPlayer->GetRow())))
		{
			POINT temp;
			temp = m_pPlayer->GetptPlayer();
			temp.y = m_pMap->GetRectTile(m_pPlayer->GetCol() - 1, m_pPlayer->GetRow()).bottom;
			m_pPlayer->SetptPlayer(temp);

		}
	}
	//하
	if (m_pMap->GetTile(m_pPlayer->GetCol() + 1, m_pPlayer->GetRow()) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer->GetCol() + 1, m_pPlayer->GetRow())))
		{
			POINT temp;
			temp = m_pPlayer->GetptPlayer();
			temp.y = m_pMap->GetRectTile(m_pPlayer->GetCol() + 1, m_pPlayer->GetRow()).top - 30;
			m_pPlayer->SetptPlayer(temp);

		}
	}
	//좌
	if (m_pMap->GetTile(m_pPlayer->GetCol(), m_pPlayer->GetRow() - 1) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer->GetCol(), m_pPlayer->GetRow() - 1)))
		{
			POINT temp;
			temp = m_pPlayer->GetptPlayer();
			temp.x = m_pMap->GetRectTile(m_pPlayer->GetCol(), m_pPlayer->GetRow() - 1).right + 20;
			m_pPlayer->SetptPlayer(temp);

		}
	}
	//우
	if (m_pMap->GetTile(m_pPlayer->GetCol(), m_pPlayer->GetRow() + 1) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer->GetCol(), m_pPlayer->GetRow() + 1)))
		{
			POINT temp;
			temp = m_pPlayer->GetptPlayer();
			temp.x = m_pMap->GetRectTile(m_pPlayer->GetCol(), m_pPlayer->GetRow() + 1).left - 20;
			m_pPlayer->SetptPlayer(temp);

		}
	}

	//////////////////////////////////////1p
	if (GetAsyncKeyState(VK_LSHIFT) & 0x0001)
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[1], 0, &m_vecChannel[1]);

		if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
		{

			if ((m_pPlayer->GetPlayerBombCount() <= m_pPlayer->GetBombCount()))
			{
				if (m_pMap->GetTile(m_pPlayer->GetCol(), m_pPlayer->GetRow()) != 7)//폭탄중복방지
				{
					cBomb*   m_pBomb;
					m_pBomb = new cBomb(m_pPlayer->GetbombPower());
					m_pBomb->Init(m_pPlayer->GetRow(), m_pPlayer->GetCol());
					vector<cBomb*> vecTemp = m_pPlayer->GetvecBomb();
					vecTemp.push_back(m_pBomb);
					m_pPlayer->SetvecBomb(vecTemp);
					m_pPlayer->SetPlayerBombCount(m_pPlayer->GetPlayerBombCount() + 1);
					m_pBomb->SetisLeftShiftkey(true);
					m_pBomb->SetisRightShiftkey(true);
					m_pBomb->SetisUpShiftkey(true);
					m_pBomb->SetisDownShiftkey(true);
				}
			}
		}
	}

	/////////////////////////////player1 충돌
	///////////////////////폭탄과 맵의 충돌

	for (auto Bomb : m_pPlayer->GetvecBomb())
	{
		int m_nLeft = Bomb->GetLeftPower();

		for (int i = 1; i <= Bomb->GetLeftPower(); i++)
		{
			//근접한것 부터 검사
			//왼쪽이 땅이면
			if (Bomb->GetisLeftShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetRow() - i < 0)
				{
					m_nLeft = i - 1;
					Bomb->SetLeftPower(m_nLeft);
					Bomb->SetisLeftShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 0||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 7)
				{
					if (m_nLeft >= Bomb->GetPower())
					{
						m_nLeft = Bomb->GetPower();
						Bomb->SetLeftPower(m_nLeft);
						break;
					}
					m_nLeft++;
					Bomb->SetLeftPower(m_nLeft);
				}
				//왼쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 1 ||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 2)
				{
					Bomb->SetLeftPower(m_nLeft);
					m_pMap->SetTile(Bomb->GetCol(), Bomb->GetRow() - i, 0);
					CreateItem(Bomb->GetCol(), Bomb->GetRow() - i);

					Bomb->SetisLeftShiftkey(false);
					break;
				}
				//왼쪽이 나무나 집이면
				else
				{
					if (m_nLeft == 1)
					{
						Bomb->SetLeftPower(0);
						break;
					}
					else
					{
						//폭탄과 폭탄충돌 처리
						m_nLeft = i - 1;
						Bomb->SetLeftPower(m_nLeft);
						Bomb->SetisLeftShiftkey(false);
						break;
					}
				}
			}
		}
	}

	for (auto Bomb : m_pPlayer->GetvecBomb())
	{
		int m_nRight = Bomb->GetRightPower();

		for (int i = 1; i <= Bomb->GetRightPower(); i++)
		{
			//근접한것 부터 검사
			//오른쪽이 땅이면
			if (Bomb->GetisRightShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetRow() + i > 12)
				{
					m_nRight = i - 1;
					Bomb->SetRightPower(m_nRight);
					Bomb->SetisRightShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 0 ||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 7)
				{
					if (m_nRight >= Bomb->GetPower())
					{
						m_nRight = Bomb->GetPower();
						Bomb->SetRightPower(m_nRight);
						break;
					}
					m_nRight++;
					Bomb->SetRightPower(m_nRight);
				}
				//오른쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 1 ||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 2)
				{
					Bomb->SetRightPower(m_nRight);
					m_pMap->SetTile(Bomb->GetCol(), Bomb->GetRow() + i, 0);
					CreateItem(Bomb->GetCol(), Bomb->GetRow() + i);
					Bomb->SetisRightShiftkey(false);
					break;
				}
				//오른쪽이 나무나 집이면
				else
				{
					if (m_nRight == 1)
					{
						Bomb->SetRightPower(0);
						break;
					}
					else
					{
						m_nRight = i - 1;
						Bomb->SetRightPower(m_nRight);
						Bomb->SetisRightShiftkey(false);
						break;
					}
				}
			}
		}
	}

	for (auto Bomb : m_pPlayer->GetvecBomb())
	{
		int m_nUp = Bomb->GetUpPower();

		for (int i = 1; i <= Bomb->GetUpPower(); i++)
		{
			//근접한것 부터 검사
			//위쪽이 땅이면
			if (Bomb->GetisUpShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetCol() - i < 0)
				{
					m_nUp = i - 1;
					Bomb->SetUpPower(m_nUp);
					Bomb->SetisUpShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 0||
					m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 7)
				{
					if (m_nUp >= Bomb->GetPower())
					{
						m_nUp = Bomb->GetPower();
						Bomb->SetUpPower(m_nUp);
						break;
					}
					m_nUp++;
					Bomb->SetUpPower(m_nUp);
				}
				//위쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 1 ||
					m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 2)
				{
					Bomb->SetUpPower(m_nUp);
					m_pMap->SetTile(Bomb->GetCol() - i, Bomb->GetRow(), 0);
					CreateItem(Bomb->GetCol() - i, Bomb->GetRow());
					Bomb->SetisUpShiftkey(false);
					break;
				}
				//위쪽이 나무나 집이면
				else
				{
					if (m_nUp == 1)
					{
						Bomb->SetUpPower(0);
						break;
					}
					else
					{
						m_nUp = i - 1;
						Bomb->SetUpPower(m_nUp);
						Bomb->SetisUpShiftkey(false);
						break;
					}
				}
			}
		}
	}

	for (auto Bomb : m_pPlayer->GetvecBomb())
	{
		int m_nDown = Bomb->GetDownPower();

		for (int i = 1; i <= Bomb->GetDownPower(); i++)
		{
			//근접한것 부터 검사
			//아래쪽이 땅이면
			if (Bomb->GetisDownShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetCol() + i > 10)
				{
					m_nDown = i - 1;
					Bomb->SetDownPower(m_nDown);
					Bomb->SetisDownShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 0||
					m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 7)
				{
					if (m_nDown >= Bomb->GetPower())
					{
						m_nDown = Bomb->GetPower();
						Bomb->SetDownPower(m_nDown);
						break;
					}
					m_nDown++;
					Bomb->SetDownPower(m_nDown);
				}
				//아래쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 1 ||
					m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 2)
				{
					Bomb->SetDownPower(m_nDown);
					m_pMap->SetTile(Bomb->GetCol() + i, Bomb->GetRow(), 0);
					CreateItem(Bomb->GetCol() + i, Bomb->GetRow());
					Bomb->SetisDownShiftkey(false);
					break;
				}
				//아래쪽이 나무나 집이면
				else
				{
					if (m_nDown == 1)
					{
						Bomb->SetDownPower(0);
						break;
					}
					else
					{
						m_nDown = i - 1;
						Bomb->SetDownPower(m_nDown);
						Bomb->SetisDownShiftkey(false);
						break;
					}
				}
			}
		}
	}
	
}

void cMainPlay::SecondPlayer()
{
	/////////////////////////////////////
	POINT pt;
	pt.x = m_pPlayer2->GetptPlayer().x;
	pt.y = m_pPlayer2->GetptPlayer().y + 10;
	for (size_t i = 0; i < STAGE_COL; i++)
	{
		for (size_t j = 0; j < STAGE_ROW; j++)
		{
			if (PtInRect(&m_pMap->GetRectTile(i, j), pt))
			{
				m_pPlayer2->SetRow(j);
				m_pPlayer2->SetCol(i);
			}
		}
	}
	for (auto p : m_pPlayer2->GetvecBomb())
	{
		p->Update();
		if (p->GetPopBomb() == true)
		{
			m_pMap->SetTile(p->GetCol(), p->GetRow(), 0);
		}
		else
		{
			m_pMap->SetTile(p->GetCol(), p->GetRow(), 7);//7은 아무것도없는상태로 못가게하려고 그냥넣은 숫자
		}
	}
	//////////////////////////////
	//1p
	///////////////////////맵충돌
	//상
	if (m_pMap->GetTile(m_pPlayer2->GetCol() - 1, m_pPlayer2->GetRow()) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer2->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer2->GetCol() - 1, m_pPlayer2->GetRow())))
		{
			POINT temp;
			temp = m_pPlayer2->GetptPlayer();
			temp.y = m_pMap->GetRectTile(m_pPlayer2->GetCol() - 1, m_pPlayer2->GetRow()).bottom;
			m_pPlayer2->SetptPlayer(temp);

		}
	}
	//하
	if (m_pMap->GetTile(m_pPlayer2->GetCol() + 1, m_pPlayer2->GetRow()) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer2->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer2->GetCol() + 1, m_pPlayer2->GetRow())))
		{
			POINT temp;
			temp = m_pPlayer2->GetptPlayer();
			temp.y = m_pMap->GetRectTile(m_pPlayer2->GetCol() + 1, m_pPlayer2->GetRow()).top - 30;
			m_pPlayer2->SetptPlayer(temp);

		}
	}
	//좌
	if (m_pMap->GetTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow() - 1) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer2->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow() - 1)))
		{
			POINT temp;
			temp = m_pPlayer2->GetptPlayer();
			temp.x = m_pMap->GetRectTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow() - 1).right + 20;
			m_pPlayer2->SetptPlayer(temp);

		}
	}
	//우
	if (m_pMap->GetTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow() + 1) != 0)
	{
		RECT rcTemp;
		if (IntersectRect(&rcTemp, &m_pPlayer2->GetrcTempPlayer(),
			&m_pMap->GetRectTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow() + 1)))
		{
			POINT temp;
			temp = m_pPlayer2->GetptPlayer();
			temp.x = m_pMap->GetRectTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow() + 1).left - 20;
			m_pPlayer2->SetptPlayer(temp);

		}
	}

	//////////////////////////////////////1p
	if (GetAsyncKeyState(VK_RSHIFT) & 0x0001)
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[1], 0, &m_vecChannel[1]);

		if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
		{

			if ((m_pPlayer2->GetPlayerBombCount() <= m_pPlayer2->GetBombCount()))
			{
				if (m_pMap->GetTile(m_pPlayer2->GetCol(), m_pPlayer2->GetRow()) != 7)//폭탄중복방지
				{
					cBomb*   m_pBomb;
					m_pBomb = new cBomb(m_pPlayer2->GetbombPower());
					m_pBomb->Init(m_pPlayer2->GetRow(), m_pPlayer2->GetCol());
					vector<cBomb*> vecTemp = m_pPlayer2->GetvecBomb();
					vecTemp.push_back(m_pBomb);
					m_pPlayer2->SetvecBomb(vecTemp);
					m_pPlayer2->SetPlayerBombCount(m_pPlayer2->GetPlayerBombCount() + 1);
					m_pBomb->SetisLeftShiftkey(true);
					m_pBomb->SetisRightShiftkey(true);
					m_pBomb->SetisUpShiftkey(true);
					m_pBomb->SetisDownShiftkey(true);
				}
			}
		}
	}

	/////////////////////////////player1 충돌
	///////////////////////폭탄과 맵의 충돌

	for (auto Bomb : m_pPlayer2->GetvecBomb())
	{
		int m_nLeft = Bomb->GetLeftPower();

		for (int i = 1; i <= Bomb->GetLeftPower(); i++)
		{
			//근접한것 부터 검사
			//왼쪽이 땅이면
			if (Bomb->GetisLeftShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetRow() - i < 0)
				{
					m_nLeft = i - 1;
					Bomb->SetLeftPower(m_nLeft);
					Bomb->SetisLeftShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 0||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 7)
				{
					if (m_nLeft >= Bomb->GetPower())
					{
						m_nLeft = Bomb->GetPower();
						Bomb->SetLeftPower(m_nLeft);
						break;
					}
					m_nLeft++;
					Bomb->SetLeftPower(m_nLeft);
				}
				//왼쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 1 ||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() - i) == 2)
				{
					Bomb->SetLeftPower(m_nLeft);
					m_pMap->SetTile(Bomb->GetCol(), Bomb->GetRow() - i, 0);
					CreateItem(Bomb->GetCol(), Bomb->GetRow() - i);

					Bomb->SetisLeftShiftkey(false);
					break;
				}
				//왼쪽이 나무나 집이면
				else
				{
					if (m_nLeft == 1)
					{
						Bomb->SetLeftPower(0);
						break;
					}
					else
					{
						//폭탄과 폭탄충돌 처리
						m_nLeft = i - 1;
						Bomb->SetLeftPower(m_nLeft);
						Bomb->SetisLeftShiftkey(false);
						break;
					}
				}
			}
		}
	}

	for (auto Bomb : m_pPlayer2->GetvecBomb())
	{
		int m_nRight = Bomb->GetRightPower();

		for (int i = 1; i <= Bomb->GetRightPower(); i++)
		{
			//근접한것 부터 검사
			//오른쪽이 땅이면
			if (Bomb->GetisRightShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetRow() + i > 12)
				{
					m_nRight = i - 1;
					Bomb->SetRightPower(m_nRight);
					Bomb->SetisRightShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 0||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 7)
				{
					if (m_nRight >= Bomb->GetPower())
					{
						m_nRight = Bomb->GetPower();
						Bomb->SetRightPower(m_nRight);
						break;
					}
					m_nRight++;
					Bomb->SetRightPower(m_nRight);
				}
				//오른쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 1 ||
					m_pMap->GetTile(Bomb->GetCol(), Bomb->GetRow() + i) == 2)
				{
					Bomb->SetRightPower(m_nRight);
					m_pMap->SetTile(Bomb->GetCol(), Bomb->GetRow() + i, 0);
					CreateItem(Bomb->GetCol(), Bomb->GetRow() + i);
					Bomb->SetisRightShiftkey(false);
					break;
				}
				//오른쪽이 나무나 집이면
				else
				{
					if (m_nRight == 1)
					{
						Bomb->SetRightPower(0);
						break;
					}
					else
					{
						m_nRight = i - 1;
						Bomb->SetRightPower(m_nRight);
						Bomb->SetisRightShiftkey(false);
						break;
					}
				}
			}
		}
	}

	for (auto Bomb : m_pPlayer2->GetvecBomb())
	{
		int m_nUp = Bomb->GetUpPower();

		for (int i = 1; i <= Bomb->GetUpPower(); i++)
		{
			//근접한것 부터 검사
			//위쪽이 땅이면
			if (Bomb->GetisUpShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetCol() - i < 0)
				{
					m_nUp = i - 1;
					Bomb->SetUpPower(m_nUp);
					Bomb->SetisUpShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 0||
					m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 7)
				{
					if (m_nUp >= Bomb->GetPower())
					{
						m_nUp = Bomb->GetPower();
						Bomb->SetUpPower(m_nUp);
						break;
					}
					m_nUp++;
					Bomb->SetUpPower(m_nUp);
				}
				//위쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 1 ||
					m_pMap->GetTile(Bomb->GetCol() - i, Bomb->GetRow()) == 2)
				{
					Bomb->SetUpPower(m_nUp);
					m_pMap->SetTile(Bomb->GetCol() - i, Bomb->GetRow(), 0);
					CreateItem(Bomb->GetCol() - i, Bomb->GetRow());
					Bomb->SetisUpShiftkey(false);
					break;
				}
				//위쪽이 나무나 집이면
				else
				{
					if (m_nUp == 1)
					{
						Bomb->SetUpPower(0);
						break;
					}
					else
					{
						m_nUp = i - 1;
						Bomb->SetUpPower(m_nUp);
						Bomb->SetisUpShiftkey(false);
						break;
					}
				}
			}
		}
	}

	for (auto Bomb : m_pPlayer2->GetvecBomb())
	{
		int m_nDown = Bomb->GetDownPower();

		for (int i = 1; i <= Bomb->GetDownPower(); i++)
		{
			//근접한것 부터 검사
			//아래쪽이 땅이면
			if (Bomb->GetisDownShiftkey() && Bomb->GetPopBomb())
			{
				if (Bomb->GetCol() + i > 10)
				{
					m_nDown = i - 1;
					Bomb->SetDownPower(m_nDown);
					Bomb->SetisDownShiftkey(false);
					break;
				}
				if (m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 0||
					m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 7)
				{
					if (m_nDown >= Bomb->GetPower())
					{
						m_nDown = Bomb->GetPower();
						Bomb->SetDownPower(m_nDown);
						break;
					}
					m_nDown++;
					Bomb->SetDownPower(m_nDown);
				}
				//아래쪽이 벽이면
				else if (m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 1 ||
					m_pMap->GetTile(Bomb->GetCol() + i, Bomb->GetRow()) == 2)
				{
					Bomb->SetDownPower(m_nDown);
					m_pMap->SetTile(Bomb->GetCol() + i, Bomb->GetRow(), 0);
					CreateItem(Bomb->GetCol() + i, Bomb->GetRow());
					Bomb->SetisDownShiftkey(false);
					break;
				}
				//아래쪽이 나무나 집이면
				else
				{
					if (m_nDown == 1)
					{
						Bomb->SetDownPower(0);
						break;
					}
					else
					{
						m_nDown = i - 1;
						Bomb->SetDownPower(m_nDown);
						Bomb->SetisDownShiftkey(false);
						break;
					}
				}
			}
		}
	}
	
}

void cMainPlay::BombToBombPlayer()
{
	//////폭탄과 폭탄 충돌
	if ((m_pPlayer2->e_charmove == POP && m_pPlayer2->e_charmove == DIE) ||
		(m_pPlayer->e_charmove == POP && m_pPlayer->e_charmove == DIE))
		return;

	for (auto p : m_pPlayer->GetvecBomb())
	{
		if (p->GetPopBomb() == false)return;
		//왼쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetLeftPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() - i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetLeftPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() - i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		//오른쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetRightPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() + i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetRightPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() + i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		//위쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetUpPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol()-i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetUpPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() - i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		//아래쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetDownPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() + i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetDownPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() + i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
	}
}

void cMainPlay::BombToBombSecondPlayer()
{

	//////폭탄과 폭탄 충돌
	if ((m_pPlayer2->e_charmove == POP && m_pPlayer2->e_charmove == DIE) ||
		(m_pPlayer->e_charmove == POP && m_pPlayer->e_charmove == DIE))
		return;
	for (auto p : m_pPlayer2->GetvecBomb())
	{
		if (p->GetPopBomb() == false)return;
		//왼쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetLeftPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() - i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetLeftPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() - i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		//오른쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetRightPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() + i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetRightPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() == j->GetCol() && p->GetRow() + i == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		//위쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetUpPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() - i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetUpPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() - i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		//아래쪽
		for (auto j : m_pPlayer->GetvecBomb())
		{
			for (int i = 0; i <= p->GetDownPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() + i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
		for (auto j : m_pPlayer2->GetvecBomb())
		{
			for (int i = 0; i <= p->GetDownPower(); i++)
			{
				if (i == 0)continue;
				if (p->GetCol() + i == j->GetCol() && p->GetRow() == j->GetRow())
				{
					j->SetPopBomb(true);
				}
			}
		}
	}
}

void cMainPlay::PlayerBombToSecondPlayer()
{
	for (auto p : m_pPlayer->GetvecBomb())
	{
		if (p->GetPopBomb())
		{
			//가운데
			if (m_pPlayer2->GetRow() == p->GetRow() && m_pPlayer2->GetCol() == p->GetCol())
			{
				m_pPlayer2->e_charmove = BUBBLE;
			}

			//왼
			for (int i = 0; i < p->GetLeftPower(); i++)
			{
				if (m_pPlayer2->GetRow() == p->GetRow() - (i + 1) && m_pPlayer2->GetCol() == p->GetCol())
				{
					m_pPlayer2->e_charmove = BUBBLE;
				}

			}
			//오
			for (int i = 0; i < p->GetRightPower(); i++)
			{
				if (m_pPlayer2->GetRow() == p->GetRow() + (i + 1) && m_pPlayer2->GetCol() == p->GetCol())
				{
					m_pPlayer2->e_charmove = BUBBLE;
				}
			}
			//업
			for (int i = 0; i < p->GetUpPower(); i++)
			{
				if (m_pPlayer2->GetCol() == p->GetCol() - (i + 1) && m_pPlayer2->GetRow() == p->GetRow())
				{
					m_pPlayer2->e_charmove = BUBBLE;
				}
			}
			//다운
			for (int i = 0; i < p->GetDownPower(); i++)
			{
				if (m_pPlayer2->GetCol() == p->GetCol() + (i + 1) && m_pPlayer2->GetRow() == p->GetRow())
				{
					m_pPlayer2->e_charmove = BUBBLE;
				}
			}
		}
	}
}

void cMainPlay::SecondBombPlayerToPlayer()
{
	for (auto p : m_pPlayer2->GetvecBomb())
	{
		if (p->GetPopBomb())
		{
			//가운데
			if (m_pPlayer->GetRow() == p->GetRow() && m_pPlayer->GetCol() == p->GetCol())
			{
				m_pPlayer->e_charmove = BUBBLE;
			}

			//왼
			for (int i = 0; i < p->GetLeftPower(); i++)
			{
				if (m_pPlayer->GetRow() == p->GetRow() - (i + 1) && m_pPlayer->GetCol() == p->GetCol())
				{
					m_pPlayer->e_charmove = BUBBLE;
				}

			}
			//오
			for (int i = 0; i < p->GetRightPower(); i++)
			{
				if (m_pPlayer->GetRow() == p->GetRow() + (i + 1) && m_pPlayer->GetCol() == p->GetCol())
				{
					m_pPlayer->e_charmove = BUBBLE;
				}
			}
			//업
			for (int i = 0; i < p->GetUpPower(); i++)
			{
				if (m_pPlayer->GetCol() == p->GetCol() - (i + 1) && m_pPlayer->GetRow() == p->GetRow())
				{
					m_pPlayer->e_charmove = BUBBLE;
				}
			}
			//다운
			for (int i = 0; i < p->GetDownPower(); i++)
			{
				if (m_pPlayer->GetCol() == p->GetCol() + (i + 1) && m_pPlayer->GetRow() == p->GetRow())
				{
					m_pPlayer->e_charmove = BUBBLE;
				}
			}
		}
	}
}

void cMainPlay::PlayerToSecondPlayer()
{
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &m_pPlayer->GetrcTempPlayer(), &m_pPlayer2->GetrcTempPlayer()))
	{
		if (m_pPlayer->e_charmove == BUBBLE)
		{
			m_pPlayer->e_charmove = POP;
		}
		if (m_pPlayer2->e_charmove == BUBBLE)
		{
			m_pPlayer2->e_charmove = POP;
		}
	}
}

void cMainPlay::CreateItem(int col, int row)
{
	int randomItemNum = rand() % 3;
	if (randomItemNum == 0)
	{
		cItem* pItem = new cItem();
		pItem->Init(col, row);
		m_vecItem.push_back(pItem);
	}
}

void cMainPlay::PlayerToItemCollision()
{
	if (m_pPlayer->e_charmove == BUBBLE)return;
	auto item = m_vecItem.begin();

	//1p
	for (item; item != m_vecItem.end();)
	{
		RECT rcItemTemp;
		if (IntersectRect(&rcItemTemp, &m_pPlayer->GetrcTempPlayer(), &(*item)->GetrcOwnItem()))
		{
			ItemStatus((*item)->GetitemValue());
			if ((*item)->GetitemValue() != E_NONE)
			{
				FMOD_Channel_IsPlaying(m_vecChannel[3], &isitemplay);
				if (!isitemplay)
					FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[3], 0, &m_vecChannel[3]);
				else
				{
					FMOD_Channel_Stop(m_vecChannel[3]);
				}
			}
			SAFE_DELETE(*item);
			item = m_vecItem.erase(item);
		}
		else
		{
			item++;
		}
	}
}

void cMainPlay::SecondPlayerToItemCollision()
{
	if (m_pPlayer2->e_charmove == BUBBLE)return;
	auto item = m_vecItem.begin();
	//2p
	for (item; item != m_vecItem.end();)
	{
		
		RECT rcItemTemp;
		if (IntersectRect(&rcItemTemp, &m_pPlayer2->GetrcTempPlayer(), &(*item)->GetrcOwnItem()))
		{
			SecondItemStatus((*item)->GetitemValue());

			if ((*item)->GetitemValue() != E_NONE)
			{
				FMOD_Channel_IsPlaying(m_vecChannel[3], &isseconditemplay);
				if (!isseconditemplay)
					FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, m_vecSound[3], 0, &m_vecChannel[3]);
				else
				{
					FMOD_Channel_Stop(m_vecChannel[3]);
				}
			}
			SAFE_DELETE(*item);
			item = m_vecItem.erase(item);
		}
		else
		{
			item++;
		}
	}
}

void cMainPlay::ItemStatus(int num)
{
	switch (num)
	{
		//스피드
	case 0:
	{
		//1p
		if (m_pPlayer->GetSpeed() > 3)
		{
			m_pPlayer->SetSpeed(3);
		}
		else
		{
			float speed = m_pPlayer->GetSpeed();
			speed += 0.5f;
			m_pPlayer->SetSpeed(speed);
		}
	}break;
	//물약
	case 1:
	{
		//1p
		if (m_pPlayer->GetbombPower() > 4)
		{
			m_pPlayer->SetbombPower(4);
		}
		else
		{
			int power = m_pPlayer->GetbombPower();
			power++;
			m_pPlayer->SetbombPower(power);
		}
	}break;
	//물폭탄갯수증가
	case 2:
	{
		//1p
		if (m_pPlayer->GetBombCount() > 20)
		{
			m_pPlayer->SetBombCount(20);
		}
		else
		{
			int count = m_pPlayer->GetBombCount();
			count++;

			m_pPlayer->SetBombCount(count);
		}
	}break;
	//물약파워최대
	case 3:
	{
		m_pPlayer->SetbombPower(5);
	}break;
	//아무것도없음
	case 4:
	{

	}break;
	default:
		break;
	}
}

void cMainPlay::SecondItemStatus(int num)
{
	switch (num)
	{
		//스피드
	case 0:
	{
		//2p
		if (m_pPlayer2->GetSpeed() > 3)
		{
			m_pPlayer2->SetSpeed(3);
		}
		else
		{
			float speed = m_pPlayer2->GetSpeed();
			speed += 0.5f;
			m_pPlayer2->SetSpeed(speed);
		}

	}break;
	//물약
	case 1:
	{
		//2p
		if (m_pPlayer2->GetbombPower() > 4)
		{
			m_pPlayer2->SetbombPower(4);
		}
		else
		{
			int power = m_pPlayer2->GetbombPower();
			power++;
			m_pPlayer2->SetbombPower(power);
		}
	}break;
	//물폭탄갯수증가
	case 2:
	{
		//2p
		if (m_pPlayer2->GetBombCount() > 5)
		{
			m_pPlayer2->SetBombCount(5);
		}
		else
		{
			int count = m_pPlayer2->GetBombCount();
			count++;

			m_pPlayer2->SetBombCount(count);
		}

	}break;
	//물약파워최대
	case 3:
	{
		m_pPlayer2->SetbombPower(5);
	}break;
	//아무것도없음
	case 4:
	{

	}break;
	default:
		break;
	}

}

void cMainPlay::ItemToBombCollision()
{
	for (auto p : m_pPlayer->GetvecBomb())
	{
		if (p->GetPopBomb() == false)return;
		for (auto j : m_vecItem)
		{
			if (j->GetisPossibleDelete() == false)return;
			for (int i = 0; i < p->GetLeftPower(); i++)
			{
				if (p->GetRow() - (i + 1) == j->GetRow() && p->GetCol() == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
			for (int i = 0; i < p->GetRightPower(); i++)
			{
				if (p->GetRow() + (i + 1) == j->GetRow() && p->GetCol() == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
			for (int i = 0; i < p->GetUpPower(); i++)
			{
				if (p->GetRow()  == j->GetRow() && p->GetCol() - (i + 1) == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
			for (int i = 0; i < p->GetDownPower(); i++)
			{
				if (p->GetRow() == j->GetRow() && p->GetCol() + (i + 1) == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
		}
	}
	for (auto p : m_pPlayer2->GetvecBomb())
	{
		if (p->GetPopBomb() == false)return;
		for (auto j : m_vecItem)
		{
			if (j->GetisPossibleDelete() == false)return;
			for (int i = 0; i < p->GetLeftPower(); i++)
			{
				if (p->GetRow() - (i + 1) == j->GetRow() && p->GetCol() == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
			for (int i = 0; i < p->GetRightPower(); i++)
			{
				if (p->GetRow() + (i + 1) == j->GetRow() && p->GetCol() == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
			for (int i = 0; i < p->GetUpPower(); i++)
			{
				if (p->GetRow() == j->GetRow() && p->GetCol() - (i + 1) == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
			for (int i = 0; i < p->GetDownPower(); i++)
			{
				if (p->GetRow() == j->GetRow() && p->GetCol() + (i + 1) == j->GetCol())
				{
					j->SetitemValue(E_NONE);
				}
			}
		}
	}
}

void cMainPlay::KeyDownPlayer()
{
	//////////////////////////////
	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
		{
			m_pPlayer->e_charmove = LEFT;
			POINT speed = m_pPlayer->GetptPlayer();
			speed.x -= m_pPlayer->GetSpeed();
			m_pPlayer->SetptPlayer(speed);
			if (m_pPlayer->GetptPlayer().x - PLAYER_X / 2 + 10 <= STAGE_START_X)
			{
				speed.x = STAGE_START_X + PLAYER_X / 2 - 10;
				m_pPlayer->SetptPlayer(speed);
			}
		}
		if (m_pPlayer->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer->GetptPlayer();
			speed.x--;
			m_pPlayer->SetptPlayer(speed);
		}
	}
	else if (GetAsyncKeyState('G') & 0x8000)
	{
		if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
		{
			m_pPlayer->e_charmove = RIGHT;
			POINT speed = m_pPlayer->GetptPlayer();
			speed.x += m_pPlayer->GetSpeed();
			m_pPlayer->SetptPlayer(speed);
			if (m_pPlayer->GetptPlayer().x + PLAYER_X / 2 - 10 >= STAGE_END_X)
			{
				speed.x = STAGE_END_X - PLAYER_X / 2 + 10;
				m_pPlayer->SetptPlayer(speed);
			}
		}
		if (m_pPlayer->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer->GetptPlayer();
			speed.x++;
			m_pPlayer->SetptPlayer(speed);
		}
	}
	else if (GetAsyncKeyState('R') & 0x8000)
	{
		if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
		{
			m_pPlayer->e_charmove = UP;
			POINT speed = m_pPlayer->GetptPlayer();
			speed.y -= m_pPlayer->GetSpeed();
			m_pPlayer->SetptPlayer(speed);
			if (m_pPlayer->GetptPlayer().y <= STAGE_START_Y)
			{
				speed.y = STAGE_START_Y;
				m_pPlayer->SetptPlayer(speed);
			}
		}
		if (m_pPlayer->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer->GetptPlayer();
			speed.y--;
			m_pPlayer->SetptPlayer(speed);
		}
	}
	else if (GetAsyncKeyState('F') & 0x8000)
	{
		if (m_pPlayer->e_charmove != BUBBLE && m_pPlayer->e_charmove != POP && m_pPlayer->e_charmove != DIE)
		{
			m_pPlayer->e_charmove = DOWN;

			POINT speed = m_pPlayer->GetptPlayer();
			speed.y += m_pPlayer->GetSpeed();
			m_pPlayer->SetptPlayer(speed);
			if (m_pPlayer->GetptPlayer().y >= 490)
			{
				speed.y = 490;
				m_pPlayer->SetptPlayer(speed);
			}
		}
		if (m_pPlayer->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer->GetptPlayer();
			speed.y++;
			m_pPlayer->SetptPlayer(speed);
		}
	}
}

void cMainPlay::KeyDownSecondPlayer()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
		{
			m_pPlayer2->e_charmove = LEFT;
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.x -= m_pPlayer2->GetSpeed();
			m_pPlayer2->SetptPlayer(speed);
			if (m_pPlayer2->GetptPlayer().x - PLAYER_X / 2 + 10 <= STAGE_START_X)
			{
				speed.x = STAGE_START_X + PLAYER_X / 2 - 10;
				m_pPlayer2->SetptPlayer(speed);
			}
		}
		if (m_pPlayer2->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.x--;
			m_pPlayer2->SetptPlayer(speed);
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
		{
			m_pPlayer2->e_charmove = RIGHT;
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.x += m_pPlayer2->GetSpeed();
			m_pPlayer2->SetptPlayer(speed);
			if (m_pPlayer2->GetptPlayer().x + PLAYER_X / 2 - 10 >= STAGE_END_X)
			{
				speed.x = STAGE_END_X - PLAYER_X / 2 + 10;
				m_pPlayer2->SetptPlayer(speed);
			}
		}
		if (m_pPlayer2->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.x++;
			m_pPlayer2->SetptPlayer(speed);
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
		{
			m_pPlayer2->e_charmove = UP;
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.y -= m_pPlayer2->GetSpeed();
			m_pPlayer2->SetptPlayer(speed);
			if (m_pPlayer2->GetptPlayer().y <= STAGE_START_Y)
			{
				speed.y = STAGE_START_Y;
				m_pPlayer2->SetptPlayer(speed);
			}
		}
		if (m_pPlayer2->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.y--;
			m_pPlayer2->SetptPlayer(speed);
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (m_pPlayer2->e_charmove != BUBBLE && m_pPlayer2->e_charmove != POP && m_pPlayer2->e_charmove != DIE)
		{
			m_pPlayer2->e_charmove = DOWN;

			POINT speed = m_pPlayer2->GetptPlayer();
			speed.y += m_pPlayer2->GetSpeed();
			m_pPlayer2->SetptPlayer(speed);
			if (m_pPlayer2->GetptPlayer().y >= 490)
			{
				speed.y = 490;
				m_pPlayer2->SetptPlayer(speed);
			}
		}
		if (m_pPlayer2->e_charmove == BUBBLE)
		{
			POINT speed = m_pPlayer2->GetptPlayer();
			speed.y++;
			m_pPlayer2->SetptPlayer(speed);
		}
	}
}

