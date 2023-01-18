#pragma once
class cImage;
class cMap
{
private:
	
	FILE*		fp;

	//장애물들
	int			m_nTile[STAGE_COL][STAGE_ROW];
	RECT		m_rcTile[STAGE_COL][STAGE_ROW];
	bool		m_bRoad[STAGE_COL][STAGE_ROW];
	bool		m_bItem[STAGE_COL][STAGE_ROW];
	GETSET(vector<RECT*>, m_vecTileRect, vecTileRect);
	GETSET(vector<int*>, m_vecTileSource, vecTileSource);
	POINT		m_ptPivot[6];
	cImage*		m_pRedBlock;
	cImage*		m_pOrangeBlock;
	cImage*		m_pRedHouse;
	cImage*		m_pBlueHouse;
	cImage*		m_pYellowHouse;
	cImage*		m_pTree;

	
public:
	cMap();
	~cMap();

	void Init();
	void Update();
	void Render(HDC hdc);

	bool GetRoad(int x, int y);
	int GetTile(int x, int y);
	void SetTile(int x, int y, int num);
	RECT GetRectTile(int x, int y);
	void SetTileRect(int x, int y, int left, int top, int right, int bottom);
	void SetBoolRoad(bool b, int x, int y);

	bool GetBoolItem(int x, int y);
	void SetBoolItem(bool b, int x, int y);

};

