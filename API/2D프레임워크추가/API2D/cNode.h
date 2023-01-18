#pragma once

#define TILE_N 15

class cNode
{
protected:

public:
	

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

