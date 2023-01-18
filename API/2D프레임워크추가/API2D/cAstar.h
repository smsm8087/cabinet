#pragma once
class cAstar
{
private:
	int m_MapCount;
	int m_Row;
	int m_Col;
	int m_TileCount;
	int m_mapTileSize;

	vector<POINT> m_vecPoint;

public:
	cAstar();
	~cAstar();

	void Init();
	void Render(HDC hdc);
	void Update();
};

