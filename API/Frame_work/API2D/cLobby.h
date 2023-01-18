#pragma once

class cSpriteSheetAnimation;
class cImage;
class cLobby
{
private:
	cSpriteSheetAnimation*	m_pSprite[NAMECOUNT];
	cSpriteSheetAnimation*	m_pSpriteSecond[NAMECOUNT];
	cImage*					m_pBackImage;
	cImage*					m_pRandom[2];
	cImage*					m_pPlayerBanner[NAMECOUNT];
	cImage*					m_pSecondPlayerBanner[NAMECOUNT];
	GETSET(CHARNAME, e_charname, charname);
	GETSET(CHARNAME, e_secondname, secondname);
	POINT					m_ptCursor;

	RECT					m_rcCharacter[2];
	RECT					m_rcPlayerBanner;
	RECT					m_rcSecondPlayerBanner;
	RECT					m_rcStartButton;
	RECT					m_rcQuitButton;
	RECT					m_rcDao;
	RECT					m_rcDigenie;
	RECT					m_rcUni;
	RECT					m_rcBazzi;
	RECT					m_rcRandom;
	GETSET(bool, m_isStartButton, isStartButton);
	bool					m_isLeftClick;
	bool					m_isRightClick;
	bool					m_isPlayerRandom;
	bool					m_isSecondPlayerRandom;
	bool					m_isnotSelectCharacter;

public:
	cLobby();
	~cLobby();

	void Init();
	void CharInit();
	void Update();
	void Render(HDC hdc);
	void PtinRectCollision();
};

