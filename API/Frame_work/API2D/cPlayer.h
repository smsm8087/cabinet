#pragma once
#include"iCharacter.h"

class cMap;
class cBomb;
class cPlayer : public iCharacter
{
private:
	GETSET(int, m_nRow, Row);
	GETSET(int, m_nCol, Col);
	GETSET(RECT, m_rcTempPlayer, rcTempPlayer);
	GETSET(vector<cBomb*>, m_vecBomb, vecBomb);
	vector<RECT>   m_vecLeft;

	GETSET(int, m_nBombCount, BombCount);
	GETSET(int, m_nPlayerBombCount, PlayerBombCount);
	GETSET(int, m_BombPower, bombPower);

	bool		isBombPop;
	float		m_fBubbleTime;
	float		m_fPoptime;
	float		m_fDietime;

	bool		m_isPlayerdie;

	bool		m_isntLeftLine;
	bool		m_isntRightLine;
	bool		m_isntUpLine;
	bool		m_isntDownLine;

	bool		m_isLefttGroundNext;
	bool		m_isRightGroundNext;
	bool		m_isUpGroundNext;
	bool		m_isDownGroundNext;


	RECT		m_rcLeftSide;
	RECT		m_rcRightSide;
	RECT		m_rcUpSide;
	RECT		m_rcDownSide;

	vector<RECT> vecLeftTemp;
	vector<RECT> vecRightTemp;
	vector<RECT> vecUpTemp;
	vector<RECT> vecDownTemp;

public:
	cPlayer();
	~cPlayer();

	virtual void Init(int x, int y, int iconplayer, CHARNAME charname) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	//virtual void SwitchIntToEnum(int num) ;
	//virtual void SwitchIntToEnumSkill(int num) ;
};

