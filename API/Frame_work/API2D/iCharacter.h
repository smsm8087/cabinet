#pragma once
class cSpriteSheetAnimation;

class iCharacter
{
protected:

	
	//character
	RECT						rcIcon;
	GETSET(POINT, m_ptPlayer, ptPlayer);
	GETSET(bool, m_isleftmove, isleftmove);
	GETSET(bool, m_isrightmove, isrightmove);
	GETSET(bool, m_isupmove, isupmove);
	GETSET(bool, m_isdownmove, isdownmove);
	CHARNAME				e_charname;
	CHARMOVE				e_charmove;
	cSpriteSheetAnimation*	m_pSprite[MOVECOUNT];
	cSpriteSheetAnimation*	m_pIcon[NAMECOUNT];
	GETSET(float,m_fSpeed,Speed);
	GET(RECT, rcPlayer, rcplayer);
	
	//data
	GETSET(PLAYER,e_Player,player);

public:

	virtual void Init(int x, int y, int iconplayer, CHARNAME charname) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	//virtual void SwitchIntToEnum(int num) =0;
	//virtual void SwitchIntToEnumSkill(int num) = 0;

};

