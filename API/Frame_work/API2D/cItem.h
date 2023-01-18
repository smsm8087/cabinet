#pragma once
class cImage;
class cItem
{
private:
	cImage * m_pSpeed;
	cImage * m_pPower;
	cImage * m_pAddBomb;
	cImage * m_pFullPower;

	GET(int, m_nRow, Row);
	GET(int, m_nCol, Col);
	int		 m_nRandom;

	float	 m_fUppassedTime;
	float	 m_fDownpassedTime;
	float	 m_fPossibleDeleteTime;
	GETSET(bool, m_isPossibleDelete, isPossibleDelete);
	RECT	 m_rcItem;
	GETSET(RECT, m_rcOwnItem, rcOwnItem);

	RECT	 m_rcSpeedImage;
	RECT	 m_rcPowerImage;
	RECT	 m_rcAddBombImage;
	RECT	 m_rcFullPowerImage;
	

	ItemMove	e_itemmove;
	GETSET(ItemValue, e_itemValue, itemValue);
public:
	cItem();
	~cItem();

	void Init(int Col, int Row);
	void Update();
	void Render(HDC hdc);

};

