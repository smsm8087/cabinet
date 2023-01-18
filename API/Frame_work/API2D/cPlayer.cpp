#include "stdafx.h"
#include "cPlayer.h"
#include "cSpriteSheetAnimation.h"
#include"cMap.h"
#include"cImage.h"
#include"cBomb.h"

cPlayer::cPlayer()
{
	m_fSpeed = 3.f;
	//BOMB
	m_nBombCount = 0;
	m_nPlayerBombCount = 0;
	m_BombPower = 1;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pIcon[BAZZI]);
	SAFE_DELETE(m_pSprite[MOVECOUNT]);
}

void cPlayer::Init(int x, int y,int iconplayer,CHARNAME charname)
{
	RECT rc; GetClientRect(g_hWnd, &rc);
	rcIcon.left = 660;
	rcIcon.top = iconplayer;
	rcIcon.right = rcIcon.left + 40;
	rcIcon.bottom = rcIcon.top + 30;

	m_ptPlayer.x = x;
	m_ptPlayer.y = y;

	/////////////////////////////////캐릭터상태값
	e_charname = charname;
	e_charmove = STAND;
	/////////////////////////////////

	switch (e_charname)
	{
	case DAO:
	{
		//icon
		m_pIcon[DAO] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pIcon[DAO]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pIcon[DAO]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 37));
		//STAND
		m_pSprite[STAND] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[STAND]->SetInterval(0.4f);
		pt; pt.x = 0; pt.y = 0;
		m_pSprite[STAND]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//UP
		m_pSprite[UP] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[UP]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 60;
		m_pSprite[UP]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//DOWN
		m_pSprite[DOWN] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[DOWN]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 120;
		m_pSprite[DOWN]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//LEFT
		m_pSprite[LEFT] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[LEFT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 180;
		m_pSprite[LEFT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//RIGHT
		m_pSprite[RIGHT] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[RIGHT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 240;
		m_pSprite[RIGHT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//DEAD
		m_pSprite[DIE] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[DIE]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//Bubble
		m_pSprite[BUBBLE] = new cSpriteSheetAnimation("image/dao_bubble.bmp");
		m_pSprite[BUBBLE]->SetInterval(0.6f);
		pt.x = 0; pt.y = 0;
		m_pSprite[BUBBLE]->SetAnimationFrame(7, 7, pt, ST_SIZE(60, 60));

		//Pop
		m_pSprite[POP] = new cSpriteSheetAnimation("image/dao_pop.bmp");
		m_pSprite[POP]->SetInterval(0.2f);
		pt.x = 0; pt.y = 0;
		m_pSprite[POP]->SetAnimationFrame(1, 1, pt, ST_SIZE(70, 70));

		m_pSprite[DIE] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[DIE]->SetInterval(0.2f);
		pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(2, 2, pt, ST_SIZE(50, 60));
	}
	break;
	case DIGENIE:
	{
		//m_nBombCount = 1;
		m_nBombCount = 1;
		//icon
		m_pIcon[DIGENIE] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pIcon[DIGENIE]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pIcon[DIGENIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 37));
		//STAND
		m_pSprite[STAND] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[STAND]->SetInterval(0.4f);
		pt; pt.x = 0; pt.y = 0;
		m_pSprite[STAND]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//UP
		m_pSprite[UP] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[UP]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 60;
		m_pSprite[UP]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//DOWN
		m_pSprite[DOWN] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[DOWN]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 120;
		m_pSprite[DOWN]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//LEFT
		m_pSprite[LEFT] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[LEFT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 180;
		m_pSprite[LEFT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//RIGHT
		m_pSprite[RIGHT] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[RIGHT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 240;
		m_pSprite[RIGHT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//DEAD
		m_pSprite[DIE] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[DIE]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//Bubble
		m_pSprite[BUBBLE] = new cSpriteSheetAnimation("image/digenie_bubble.bmp");
		m_pSprite[BUBBLE]->SetInterval(0.6f);
		pt.x = 0; pt.y = 0;
		m_pSprite[BUBBLE]->SetAnimationFrame(7, 7, pt, ST_SIZE(60, 60));

		//Pop
		m_pSprite[POP] = new cSpriteSheetAnimation("image/digenie_pop.bmp");
		m_pSprite[POP]->SetInterval(0.2f);
		pt.x = 0; pt.y = 0;
		m_pSprite[POP]->SetAnimationFrame(1, 1, pt, ST_SIZE(70, 70));

		m_pSprite[DIE] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[DIE]->SetInterval(0.2f);
		pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(2, 2, pt, ST_SIZE(50, 60));
	}
	break;
	case BAZZI:
	{
		//icon
		m_pIcon[BAZZI] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pIcon[BAZZI]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pIcon[BAZZI]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 37));
		//STAND
		m_pSprite[STAND] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[STAND]->SetInterval(0.4f);
		pt; pt.x = 0; pt.y = 0;
		m_pSprite[STAND]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//UP
		m_pSprite[UP] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[UP]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 60;
		m_pSprite[UP]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//DOWN
		m_pSprite[DOWN] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[DOWN]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 120;
		m_pSprite[DOWN]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//LEFT
		m_pSprite[LEFT] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[LEFT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 180;
		m_pSprite[LEFT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//RIGHT
		m_pSprite[RIGHT] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[RIGHT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 240;
		m_pSprite[RIGHT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//DEAD
		m_pSprite[DIE] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[DIE]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//Bubble
		m_pSprite[BUBBLE] = new cSpriteSheetAnimation("image/bazzi_bubble.bmp");
		m_pSprite[BUBBLE]->SetInterval(0.6f);
		pt.x = 0; pt.y = 0;
		m_pSprite[BUBBLE]->SetAnimationFrame(7, 7, pt, ST_SIZE(60, 60));

		//Pop
		m_pSprite[POP] = new cSpriteSheetAnimation("image/bazzi_pop.bmp");
		m_pSprite[POP]->SetInterval(0.2f);
		pt.x = 0; pt.y = 0;
		m_pSprite[POP]->SetAnimationFrame(1, 1, pt, ST_SIZE(70, 70));

		m_pSprite[DIE] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[DIE]->SetInterval(0.2f);
		pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(2, 2, pt, ST_SIZE(50, 60));
	}
	break;
	case UNI:
	{
		//m_BombPower = 2;
		m_BombPower = 1;
		//icon
		m_pIcon[UNI] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pIcon[UNI]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pIcon[UNI]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 37));
		//STAND
		m_pSprite[STAND] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[STAND]->SetInterval(0.4f);
		pt; pt.x = 0; pt.y = 0;
		m_pSprite[STAND]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//UP
		m_pSprite[UP] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[UP]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 60;
		m_pSprite[UP]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//DOWN
		m_pSprite[DOWN] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[DOWN]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 120;
		m_pSprite[DOWN]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//LEFT
		m_pSprite[LEFT] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[LEFT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 180;
		m_pSprite[LEFT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));

		//RIGHT
		m_pSprite[RIGHT] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[RIGHT]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 240;
		m_pSprite[RIGHT]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//DEAD
		m_pSprite[DIE] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[DIE]->SetInterval(0.1f);
		pt; pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		//Bubble
		m_pSprite[BUBBLE] = new cSpriteSheetAnimation("image/uni_bubble.bmp");
		m_pSprite[BUBBLE]->SetInterval(0.6f);
		pt.x = 0; pt.y = 0;
		m_pSprite[BUBBLE]->SetAnimationFrame(7, 7, pt, ST_SIZE(60, 60));

		//Pop
		m_pSprite[POP] = new cSpriteSheetAnimation("image/uni_pop.bmp");
		m_pSprite[POP]->SetInterval(0.2f);
		pt.x = 0; pt.y = 0;
		m_pSprite[POP]->SetAnimationFrame(1, 1, pt, ST_SIZE(70, 70));

		m_pSprite[DIE] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[DIE]->SetInterval(0.2f);
		pt.x = 0; pt.y = 300;
		m_pSprite[DIE]->SetAnimationFrame(2, 2, pt, ST_SIZE(50, 60));

	}
	break;
	case RANDOM:
	{

	}
		break;
	default:
		break;
	}
	



	//OUTSIDE
	SetRect(&m_rcLeftSide,0,81,60,720);
	SetRect(&m_rcRightSide,580,81,640,720);
	SetRect(&m_rcUpSide,60,0,580,81);
	SetRect(&m_rcDownSide,60,720,580,801);
}

void cPlayer::Update()
{

	SetRect(&m_rcTempPlayer,(int) m_ptPlayer.x - 15, (int)m_ptPlayer.y, (int)m_ptPlayer.x + 15, (int)m_ptPlayer.y + 30);
	m_pIcon[e_charname]->Update();
	m_pSprite[STAND]->Update();
	RECT rcTemp;

	

	//Bubble 
	if (e_charmove == BUBBLE)
	{
		m_pSprite[BUBBLE]->Update();
		m_fBubbleTime += g_pTimeManager->GetElapsedTime();
		if (m_fBubbleTime >= 4.2f)
		{
			m_fBubbleTime -= 4.2f;
			e_charmove = POP;
		}
	}
	if (e_charmove == POP)
	{
		m_fPoptime += g_pTimeManager->GetElapsedTime();
		m_pSprite[POP]->Update();
		if (m_fPoptime >= 0.2f)
		{
			m_fPoptime -= 0.2f;
			e_charmove = DIE;
		}
	}
	if (e_charmove == DIE)
	{
		m_fDietime += g_pTimeManager->GetElapsedTime();
		m_pSprite[DIE]->Update();
		if (m_fDietime >= 0.4f)
		{
			m_isPlayerdie = true;
		}
		else if (m_fDietime > 0.4f && m_fDietime <= 0.8f)
		{
			m_fDietime -= 0.8f;
			m_isPlayerdie = false;
		}
	}
	if (e_charmove == LEFT)
	{
		m_pSprite[LEFT]->Update();
	}
	else if (e_charmove == RIGHT)
	{
		m_pSprite[RIGHT]->Update();
	}
	else if (e_charmove == UP)
	{
		m_pSprite[UP]->Update();
	}
	else if (e_charmove == DOWN)
	{
		m_pSprite[DOWN]->Update();
	}

	///////////////////////플레이어와 폭탄의 충돌

	for (auto p : m_vecBomb)
	{
		if (p->GetPopBomb())
		{
			//가운데
			if (m_nRow == p->GetRow() && m_nCol == p->GetCol())
			{
				e_charmove = BUBBLE;
			}

			//왼
			for (int i = 0; i < p->GetLeftPower(); i++)
			{
				if (m_nRow == p->GetRow() - (i + 1) && m_nCol == p->GetCol())
				{
					e_charmove = BUBBLE;
				}

			}
			//오
			for (int i = 0; i < p->GetRightPower(); i++)
			{
				if (m_nRow == p->GetRow() + (i + 1) && m_nCol == p->GetCol())
				{
					e_charmove = BUBBLE;
				}
			}
			//업
			for (int i = 0; i < p->GetUpPower(); i++)
			{
				if (m_nCol == p->GetCol() - (i + 1) && m_nRow == p->GetRow())
				{
					e_charmove = BUBBLE;
				}
			}
			//다운
			for (int i = 0; i < p->GetDownPower(); i++)
			{
				if (m_nCol == p->GetCol() + (i + 1)&&m_nRow == p->GetRow())
				{
					e_charmove = BUBBLE;
				}
			}
		}
	}
	//물폭탄 삭제 터질시
	auto p = m_vecBomb.begin();
	for (p; p != m_vecBomb.end();)
	{
		if ((*p)->GetEndBomb() == true)
		{
			SAFE_DELETE(*p);
			p = m_vecBomb.erase(p);
			m_nPlayerBombCount--;
		}
		else
		{
			p++;
		}
	}
	
}
void cPlayer::Render(HDC hdc)
{
	SetRect(&rcPlayer, m_ptPlayer.x - 30, m_ptPlayer.y - 30, m_ptPlayer.x + 30, m_ptPlayer.y + 30);
	
	////bomb;

	for (auto p : m_vecBomb)
	{
		p->Render(hdc);
	}
	switch (e_charname)
	{
	case BAZZI:
	{
		switch (e_charmove)
		{
		case STAND:
		{
			m_pSprite[STAND]->Render(hdc, rcPlayer);
		}
		break;
		case UP:
		{
			m_pSprite[UP]->Render(hdc, rcPlayer);
		}
		break;
		case DOWN:
		{
			m_pSprite[DOWN]->Render(hdc, rcPlayer);
		}
		break;
		case LEFT:
		{
			m_pSprite[LEFT]->Render(hdc, rcPlayer);
		}
		break;
		case RIGHT:
		{
			m_pSprite[RIGHT]->Render(hdc, rcPlayer);
		}
		break;
		case DIE:
		{
			if(m_fDietime)
				m_pSprite[DIE]->Render(hdc, rcPlayer);
		}
		break;
		case BUBBLE:
		{
			m_pSprite[BUBBLE]->Render(hdc, rcPlayer);
		}
		break;
		case POP:
		{
			m_pSprite[POP]->Render(hdc, rcPlayer);
		}
		break;
		default:
			break;
		}
	}break;
	case DAO:
	{
		switch (e_charmove)
		{
		case STAND:
		{
			m_pSprite[STAND]->Render(hdc, rcPlayer);
		}
		break;
		case UP:
		{
			m_pSprite[UP]->Render(hdc, rcPlayer);
		}
		break;
		case DOWN:
		{
			m_pSprite[DOWN]->Render(hdc, rcPlayer);
		}
		break;
		case LEFT:
		{
			m_pSprite[LEFT]->Render(hdc, rcPlayer);
		}
		break;
		case RIGHT:
		{
			m_pSprite[RIGHT]->Render(hdc, rcPlayer);
		}
		break;
		case DIE:
		{
			if (m_fDietime)
				m_pSprite[DIE]->Render(hdc, rcPlayer);
		}
		break;
		case BUBBLE:
		{
			m_pSprite[BUBBLE]->Render(hdc, rcPlayer);
		}
		break;
		case POP:
		{
			m_pSprite[POP]->Render(hdc, rcPlayer);
		}
		break;
		default:
			break;
		}
	}break;
	case UNI:
	{
		switch (e_charmove)
		{
		case STAND:
		{
			m_pSprite[STAND]->Render(hdc, rcPlayer);
		}
		break;
		case UP:
		{
			m_pSprite[UP]->Render(hdc, rcPlayer);
		}
		break;
		case DOWN:
		{
			m_pSprite[DOWN]->Render(hdc, rcPlayer);
		}
		break;
		case LEFT:
		{
			m_pSprite[LEFT]->Render(hdc, rcPlayer);
		}
		break;
		case RIGHT:
		{
			m_pSprite[RIGHT]->Render(hdc, rcPlayer);
		}
		break;
		case DIE:
		{
			if (m_fDietime)
				m_pSprite[DIE]->Render(hdc, rcPlayer);
		}
		break;
		case BUBBLE:
		{
			m_pSprite[BUBBLE]->Render(hdc, rcPlayer);
		}
		break;
		case POP:
		{
			m_pSprite[POP]->Render(hdc, rcPlayer);
		}
		break;
		default:
			break;
		}
	}break;
	case DIGENIE:
	{
		switch (e_charmove)
		{
		case STAND:
		{
			m_pSprite[STAND]->Render(hdc, rcPlayer);
		}
		break;
		case UP:
		{
			m_pSprite[UP]->Render(hdc, rcPlayer);
		}
		break;
		case DOWN:
		{
			m_pSprite[DOWN]->Render(hdc, rcPlayer);
		}
		break;
		case LEFT:
		{
			m_pSprite[LEFT]->Render(hdc, rcPlayer);
		}
		break;
		case RIGHT:
		{
			m_pSprite[RIGHT]->Render(hdc, rcPlayer);
		}
		break;
		case DIE:
		{
			if (m_fDietime)
				m_pSprite[DIE]->Render(hdc, rcPlayer);
		}
		break;
		case BUBBLE:
		{
			m_pSprite[BUBBLE]->Render(hdc, rcPlayer);
		}
		break;
		case POP:
		{
			m_pSprite[POP]->Render(hdc, rcPlayer);
		}
		break;
		default:
			break;
		}
	}break;
	default:
		break;
	}

	//icon
	switch (e_charname)
	{
	case DAO:
	{
		m_pIcon[DAO]->Render(hdc, rcIcon);
	}
	break;
	case DIGENIE:
	{
		m_pIcon[DIGENIE]->Render(hdc, rcIcon);
	}
	break;
	case BAZZI:
	{
		m_pIcon[BAZZI]->Render(hdc, rcIcon);
	}
	break;
	case UNI:
	{
		m_pIcon[UNI]->Render(hdc, rcIcon);
	}
	break;
	case RANDOM:
	{

	}
	break;
	default:
		break;
	}

	

}
bool cPlayer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	return false;
}
