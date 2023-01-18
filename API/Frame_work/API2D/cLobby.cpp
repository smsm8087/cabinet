#include "stdafx.h"
#include "cLobby.h"
#include"cSpriteSheetAnimation.h"
#include"cImage.h"

cLobby::cLobby()
{
}


cLobby::~cLobby()
{
	for (int i = 0; i < NAMECOUNT; i++)
	{
		SAFE_DELETE(m_pSprite[i]);
	}
	for (int i = 0; i < NAMECOUNT; i++)
	{
		SAFE_DELETE(m_pSpriteSecond[i]);
	}
	SAFE_DELETE(m_pBackImage);
	SAFE_DELETE(m_pRandom[0]);
	SAFE_DELETE(m_pRandom[1]);
	for (int i = 0; i < NAMECOUNT; i++)
	{
		SAFE_DELETE(m_pPlayerBanner[i]);
	}
	for (int i = 0; i < NAMECOUNT; i++)
	{
		SAFE_DELETE(m_pSecondPlayerBanner[i]);
	}
}

void cLobby::Init()
{
	m_pBackImage = new cImage("image/room.bmp");
	m_pRandom[0] = new cImage("image/random_mark.bmp");
	m_pRandom[1] = new cImage("image/random_mark.bmp");
	e_charname = NAMECOUNT;
	e_secondname = NAMECOUNT;

	//rect
	//그리기용 렉트
	SetRect(&m_rcCharacter[0],40,105,110,180);//w = 90, h 95
	SetRect(&m_rcCharacter[1],145,105,215,180);//2p
	SetRect(&m_rcPlayerBanner, 800 - 310, 8, 800 - 30, 93);//w = 280 ,h =85
	SetRect(&m_rcSecondPlayerBanner, 800 - 310, 100, 800 - 30, 185);

	
	//충돌용렉트
	SetRect(&m_rcStartButton,800-287,600-100,800-100,600-50);
	SetRect(&m_rcQuitButton,750,600-25,800-20,595);

	SetRect(&m_rcDao, 488, 191, 488+65, 191+41);
	SetRect(&m_rcDigenie, 561, 191, 561+65, 191+41);
	SetRect(&m_rcBazzi, 632, 191, 632+65, 191+41);
	SetRect(&m_rcUni, 704, 191, 704 + 65, 191 + 41);
	SetRect(&m_rcRandom, 488, 237, 488 + 65, 237 + 41);
}

void cLobby::CharInit()
{
	switch (e_charname)
	{
	case DAO:
	{
		//STAND
		m_pSprite[DAO] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSprite[DAO]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSprite[DAO]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pPlayerBanner[DAO] = new cImage("image/dao_image.bmp");
	}
	break;
	case DIGENIE:
	{
		//STAND
		m_pSprite[DIGENIE] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSprite[DIGENIE]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSprite[DIGENIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pPlayerBanner[DIGENIE] = new cImage("image/digenie_image.bmp");
	}
	break;
	case BAZZI:
	{
		//STAND
		m_pSprite[BAZZI] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSprite[BAZZI]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSprite[BAZZI]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pPlayerBanner[BAZZI] = new cImage("image/bazzi_image.bmp");
	}
	break;
	case UNI:
	{
		//STAND
		m_pSprite[UNI] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSprite[UNI]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSprite[UNI]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pPlayerBanner[UNI] = new cImage("image/uni_image.bmp");
	}
	break;
	default:
		break;
	}
	//2p
	switch (e_secondname)
	{
	case DAO:
	{
		//STAND
		m_pSpriteSecond[DAO] = new cSpriteSheetAnimation("image/dao.bmp");
		m_pSpriteSecond[DAO]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSpriteSecond[DAO]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pSecondPlayerBanner[DAO] = new cImage("image/dao_image.bmp");
	}
	break;
	case DIGENIE:
	{
		//STAND
		m_pSpriteSecond[DIGENIE] = new cSpriteSheetAnimation("image/digenie.bmp");
		m_pSpriteSecond[DIGENIE]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSpriteSecond[DIGENIE]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pSecondPlayerBanner[DIGENIE] = new cImage("image/digenie_image.bmp");
	}
	break;
	case BAZZI:
	{
		//STAND
		m_pSpriteSecond[BAZZI] = new cSpriteSheetAnimation("image/bazzi.bmp");
		m_pSpriteSecond[BAZZI]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSpriteSecond[BAZZI]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pSecondPlayerBanner[BAZZI] = new cImage("image/bazzi_image.bmp");
	}
	break;
	case UNI:
	{
		//STAND
		m_pSpriteSecond[UNI] = new cSpriteSheetAnimation("image/uni.bmp");
		m_pSpriteSecond[UNI]->SetInterval(0.4f);
		POINT pt; pt.x = 0; pt.y = 0;
		m_pSpriteSecond[UNI]->SetAnimationFrame(4, 4, pt, ST_SIZE(50, 60));
		m_pSecondPlayerBanner[UNI] = new cImage("image/uni_image.bmp");
	}
	break;
	default:
		break;
	}
}

void cLobby::Update()
{
	PtinRectCollision();

	if (!m_isnotSelectCharacter)
	{
		if (m_isLeftClick)
		{
			for (int i = 0; i < RANDOM; i++)
			{
				if (m_pSprite[i] != NULL)
				{
					m_pSprite[i]->Update();
				}
			}
		}
		if (m_isRightClick)
		{
			for (int i = 0; i < RANDOM; i++)
			{
				if (m_pSpriteSecond[i] != NULL)
				{
					m_pSpriteSecond[i]->Update();
				}
			}
		}
	}
}

void cLobby::Render(HDC hdc)
{
	RECT rc; GetClientRect(g_hWnd, &rc);
	m_pBackImage->RenderCharater(hdc,rc,true);
	if (m_isnotSelectCharacter)return;
	if (m_isLeftClick)
	{
		switch (e_charname)
		{
		case DAO:
		{
			m_pSprite[DAO]->Render(hdc, m_rcCharacter[0]);
			m_pPlayerBanner[DAO]->RenderCharater(hdc, m_rcPlayerBanner, true);
		}
		break;
		case DIGENIE:
		{
			m_pSprite[DIGENIE]->Render(hdc, m_rcCharacter[0]);
			m_pPlayerBanner[DIGENIE]->RenderCharater(hdc, m_rcPlayerBanner, true);
		}
		break;
		case BAZZI:
		{
			m_pSprite[BAZZI]->Render(hdc, m_rcCharacter[0]);
			m_pPlayerBanner[BAZZI]->RenderCharater(hdc, m_rcPlayerBanner, true);
		}
		break;
		case UNI:
		{
			m_pSprite[UNI]->Render(hdc, m_rcCharacter[0]);
			m_pPlayerBanner[UNI]->RenderCharater(hdc, m_rcPlayerBanner, true);
		}
		break;
		case RANDOM:
		{
			RECT rcRandom;
			SetRect(&rcRandom, 0, 0, 50, 60);
			m_pRandom[0]->TransparentRender(hdc, m_rcCharacter[0], rcRandom);
		}break;
		default:
			break;
		}
	}
	if (m_isRightClick)
	{
		//2p
		switch (e_secondname)
		{
		case DAO:
		{
			m_pSpriteSecond[DAO]->Render(hdc, m_rcCharacter[1]);
			m_pSecondPlayerBanner[DAO]->RenderCharater(hdc, m_rcSecondPlayerBanner, true);
		}
		break;
		case DIGENIE:
		{
			m_pSpriteSecond[DIGENIE]->Render(hdc, m_rcCharacter[1]);
			m_pSecondPlayerBanner[DIGENIE]->RenderCharater(hdc, m_rcSecondPlayerBanner, true);
		}
		break;
		case BAZZI:
		{
			m_pSpriteSecond[BAZZI]->Render(hdc, m_rcCharacter[1]);
			m_pSecondPlayerBanner[BAZZI]->RenderCharater(hdc, m_rcSecondPlayerBanner, true);
		}
		break;
		case UNI:
		{
			m_pSpriteSecond[UNI]->Render(hdc, m_rcCharacter[1]);
			m_pSecondPlayerBanner[UNI]->RenderCharater(hdc, m_rcSecondPlayerBanner, true);
		}
		break;
		case RANDOM:
		{
			RECT rcRandom;
			SetRect(&rcRandom, 50, 0, 100, 60);
			m_pRandom[1]->TransparentRender(hdc, m_rcCharacter[1], rcRandom);
		}break;
		default:
			break;
		}
	}
}

void cLobby::PtinRectCollision()
{
	GetCursorPos(&m_ptCursor);
	ScreenToClient(g_hWnd, &m_ptCursor);
	//start
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		m_isLeftClick = true;
		m_isPlayerRandom = false;
		if (PtInRect(&m_rcStartButton, m_ptCursor))
		{
			if (!m_isnotSelectCharacter)
			{
				m_isStartButton = true;
				m_isPlayerRandom = true;
				m_isSecondPlayerRandom = true;
			}
			else
			{
				MessageBox(g_hWnd, "캐릭터를 선택하세요!", 0, 0);
				return;
			}
		}
		//end
		else if (PtInRect(&m_rcQuitButton, m_ptCursor))
		{
			PostQuitMessage(0);
		}
		//CHARACTER
		else if (PtInRect(&m_rcDao, m_ptCursor))
		{
			e_charname = DAO;
			CharInit();
		}
		else if (PtInRect(&m_rcDigenie, m_ptCursor))
		{
			e_charname = DIGENIE;
			CharInit();
		}
		else if (PtInRect(&m_rcBazzi, m_ptCursor))
		{
			e_charname = BAZZI;
			CharInit();
		}
		else if (PtInRect(&m_rcUni, m_ptCursor))
		{
			e_charname = UNI;
			CharInit();
		}
		else if (PtInRect(&m_rcRandom, m_ptCursor))
		{
			/*int random = rand() % RANDOM;
			e_charname = (CHARNAME)random;*/
			e_charname = RANDOM;
			m_isPlayerRandom = true;
		}
	}

	//2p
	if (GetAsyncKeyState(VK_RBUTTON) & 0x0001)
	{
		m_isSecondPlayerRandom = false;
		m_isRightClick = true;
		//CHARACTER
		if (PtInRect(&m_rcDao, m_ptCursor))
		{
			e_secondname = DAO;
			CharInit();
		}
		else if (PtInRect(&m_rcDigenie, m_ptCursor))
		{
			e_secondname = DIGENIE;
			CharInit();
		}
		else if (PtInRect(&m_rcBazzi, m_ptCursor))
		{
			e_secondname = BAZZI;
			CharInit();
		}
		else if (PtInRect(&m_rcUni, m_ptCursor))
		{
			e_secondname = UNI;
			CharInit();
		}
		else if (PtInRect(&m_rcRandom, m_ptCursor))
		{
			/*int random = rand() % RANDOM;
			e_secondname = (CHARNAME)random;*/
			e_secondname = RANDOM;
			m_isSecondPlayerRandom = true;
		}
	}
	if (e_charname == NAMECOUNT && e_secondname == NAMECOUNT)
	{
		m_isnotSelectCharacter = true;
	}
	else
	{
		m_isnotSelectCharacter = false;
	}
}
