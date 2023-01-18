#pragma once
#define TILESIZE 50;


class cAstar
{

	enum eStratEnd
	{
		E_START,
		E_END
	};
	enum eState
	{
		E_OPEN,
		E_CLOSE,
		E_WALL,
		E_NONE,
	};

	enum eDir
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		LT,
		LB,
		RT,
		RB
	};

	struct RectInfo
	{
		int F;
		int G;
		int H;
		eState RectState;
		POINT RectPt;
		int Row;
		int Col;
		RectInfo() {}
		RectInfo(int _f, int _g, int _h, eState _eState, POINT _RectPt, int _row, int _col)
			:F(_f),
			G(_g),
			H(_h),
			RectState(_eState),
			RectPt(_RectPt),
			Row(_row),
			Col(_col)
		{

		}
		
	};
private:
	int m_MapCount;
	int m_Row;
	int m_Col;
	int m_TileCount;
	int m_mapTileSize;

	RectInfo m_RectInfo;


	//bool isClose;
	eStratEnd eSE;

	vector<POINT> m_vecPoint;
	vector<RectInfo> m_vecRectInfo;
	//vector<POINT> m_vecPoint2;

public:
	cAstar();
	~cAstar();
	void Init();
	void Render(HDC hdc);
	void Update();

	void Astar();

};
