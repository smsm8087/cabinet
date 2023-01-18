#pragma once
#include "cNode.h"

class cScv;
class cMineral;
class cCommandCenter;
class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	vector<cPoint2N>	m_vecPoint;
	vector<cPoint2N>	m_vecOutlinePoint;

	/*MyStruct m_m;*/

	//Astar
	int				count;
	vector<Wall>	m_vecAll_wall;
	stack<cNode*>   m_pathnode;
	bool			isScvgoing;
	cVector2		v_start;
	cVector2		v_dest;
	float			m_fSpeed;
	float			m_fvDirx;
	float			m_fvDiry;

	enum
	{
		E_LEFT = 1 << 0,
		E_RIGHT = 1 << 1,
		E_UP = 1 << 2,
		E_DOWN = 1 << 3,
	};
	vector<cNode*>	m_vecNode;
	set<cNode*>		m_setOpenList;
	vector<int>		m_vecDirection;
	map<int, float> m_mapDistance;
	/////////Starcraft
private:
	int			Tile_size;
	int			m_nScore;
private:
	//DRAG
	POINT	    ptDrag[4];
	bool		isDrag;
	//RbtClick
	int			RbtnCount;
	POINT		ptRbtn;
	bool		isRbt;
private:
	
	cCommandCenter*			m_commandcenter;
private:
	vector<cScv*>			m_vecScv;
	vector<cMineral*>	m_vec_nearMineral;
	vector<cMineral*>	m_vec_farMineral;
	vector<cCommandCenter*>	m_vecCmdcenter;
private:
	int Row;
	int Col;
	Wall wall;
	int Start;
	int Dest;
	vector<Wall>			m_vecWall;
	FILE* fp;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void FindPath();
	cNode* FindNode(eNodeType eNodeType);
	cNode* MinFNodeAtOpenList();
	float GetHeuristic(cNode* n1, cNode* n2);
	void Extend(cNode* pExtNode, cNode* pDest);
	cNode* GetAdjNode(cNode* pExtNode, int nDir);
	void ScvMove(cVector2 start,cVector2 dest);
};

