#pragma once

#define TILE_N 16

class cNode
{
protected:

public:
	enum eNodeType
	{
		E_EMPTY,
		E_WALL,
		E_START,
		E_DEST,
		E_PATH
	};

	enum eNodeState
	{
		E_NONE,
		E_OPEN,
		E_CLOSE
	};

	cNode();
	virtual ~cNode();
	
	float		F;
	float		G;
	float		H;
	cNode*		m_pParent;
	eNodeType	m_eNodeType;
	eNodeState	m_eNodeState;
	int			m_nIndex;
	int			m_nRow;
	int			m_nCol;

	void Init(int nIndex, eNodeType eType);
	void Update();
	void Render(HDC hdc);
};

