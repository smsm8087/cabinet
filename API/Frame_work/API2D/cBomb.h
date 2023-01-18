#pragma once
class cSpriteSheetAnimation;
class cImage;
class cBomb
{
private:
	RECT					m_rcBomb;
	GETSET(vector<RECT>, m_vecrcBomb, vecrcBomb);
	GETSET(vector<RECT>, m_vecLeftBomb, vecLeftBomb);
	GETSET(vector<RECT>, m_vecRightBomb, vecRightBomb);
	GETSET(vector<RECT>, m_vecUpBomb, vecUpBomb);
	GETSET(vector<RECT>, m_vecBottomBomb, vecBottomBomb);

	//ÀüÃ¼ ÆøÅº
	GETSET(vector<vector<RECT>>, m_vecAllBomb, vecAllBomb);

	GETSET(int, m_nRow, Row);
	GETSET(int, m_nCol, Col);
	GETSET(bool, m_isleftPop, isleftPop);
	GETSET(bool, m_isrightPoP, isrighttPop);
	GETSET(bool, m_isUpPop, isUpPop);
	GETSET(bool, m_isDownPop, isDownPop);

	GETSET(bool, m_isLeftEdge, isLeftEdge);
	GETSET(bool, m_isRightEdge, isRightEdge);
	GETSET(bool, m_isUpEdge, isUpEdge);
	GETSET(bool, m_isDownEdge, isDownEdge);
	GETSET(int, m_nPower, Power);

	GETSET(int, m_nLeftPower, LeftPower);
	GETSET(int, m_nRightPower, RightPower);
	GETSET(int, m_nUpPower, UpPower);
	GETSET(int, m_nDownPower, DownPower);

	/*bool m_isLeftLine[BOMB_POWER_MAX];
	bool m_isRightLine[BOMB_POWER_MAX];
	bool m_isUpLine[BOMB_POWER_MAX];
	bool m_isDownLine[BOMB_POWER_MAX];*/

	GETSET(bool, m_isLeftLine, pLeftLine);
	GETSET(bool, m_isRightLine, pRightLine);
	GETSET(bool, m_isUpLine, pUpLine);
	GETSET(bool, m_isDownLine, pDownLine);

	GETSET(float, m_fBombTime, BombTime);
	float					m_fPopBombTime;
	cSpriteSheetAnimation*	m_pBombAni;
	GETSET(bool, m_isPopBomb, PopBomb);
	GETSET(bool, m_isEndBomb, EndBomb);

	cImage*					m_leftPop;
	cImage*					m_RightPop;
	cImage*					m_UpPop;
	cImage*					m_DownPop;
	cImage*					m_CenterPop;
	cImage*					m_Pathleft;
	cImage*					m_PathRight;
	cImage*					m_PathUp;
	cImage*					m_PathDown;

	GETSET(RECT, m_rcTile, rcTile);
	RECT					m_rcLeftPop;
	RECT					m_rcRightPop;
	RECT					m_rcUpPop;
	RECT					m_rcDownPop;
	RECT					m_rcCenterPop;
	RECT					m_rcPathleft;
	RECT					m_rcPathright;
	RECT					m_rcPathUp;
	RECT					m_rcPathDown;

	GETSET(bool, m_isLeftShiftkey, isLeftShiftkey);
	GETSET(bool, m_isRightShiftkey, isRightShiftkey);
	GETSET(bool, m_isUpShiftkey, isUpShiftkey);
	GETSET(bool, m_isDownShiftkey, isDownShiftkey);
public:
	cBomb(int power);
	~cBomb();

	void Init(int row, int col);
	void Update();
	void Render(HDC hdc);
	
	
};

