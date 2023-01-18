#pragma once
class cTile
{
public:
	cTile(int nRow, int nCol, int nTileType);
	~cTile();

	int		m_nRow;
	int		m_nCol;
	RECT	m_rcTile;
	int		m_nTileType;
	int		m_nCheckDepth;

	enum eDir
	{
		E_LEFT,
		E_RIGHT,
		E_UP,
		E_DOWN,
	};

protected:
	int CheckDelete(vector<cTile*>& vecTile, eDir e, int nDepth, int nType);
	cTile* GetTile(vector<cTile*>& vecTile, eDir e);

public:
	void CheckDelete(vector<cTile*>& vecTile);
	void Update();
	void Render(HDC hdc);
};

