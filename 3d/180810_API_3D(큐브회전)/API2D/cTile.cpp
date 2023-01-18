#include "stdafx.h"
#include "cTile.h"


cTile::cTile(int nRow, int nCol, int nTileType)
	: m_nRow(nRow)
	, m_nCol(nCol)
	, m_nTileType(nTileType)
	, m_nCheckDepth(0)
{
	SetRect(&m_rcTile,
		nCol * TILE_SIZE,
		nRow * TILE_SIZE,
		(nCol + 1) * TILE_SIZE,
		(nRow + 1) * TILE_SIZE);
}

cTile::~cTile()
{
}

int cTile::CheckDelete(vector<cTile*>& vecTile, eDir e, int nDepth, int nType)
{
	if (nType != m_nTileType) return nDepth - 1;
	
	cTile* p = GetTile(vecTile, e);
	if (p == NULL)
	{
		if (m_nCheckDepth < nDepth)
			m_nCheckDepth = nDepth;
		return nDepth;
	}
		
	int nRetDepth = p->CheckDelete(vecTile, e, nDepth + 1, nType);
	if (m_nCheckDepth < nRetDepth)
		m_nCheckDepth = nRetDepth;
	return nRetDepth;
}

cTile * cTile::GetTile(vector<cTile*>& vecTile, eDir e)
{
	if (m_nCol == 0 && e == eDir::E_LEFT) return NULL;
	if (m_nRow == 0 && e == eDir::E_UP) return NULL;
	if (m_nCol == TILE_H - 1 && e == eDir::E_RIGHT) return NULL;
	if (m_nRow == TILE_V - 1 && e == eDir::E_DOWN) return NULL;
	
	int r = 0;
	int c = 0;
	
	switch (e)
	{
	case cTile::E_LEFT:  c = -1; break;
	case cTile::E_RIGHT: c =  1; break;
	case cTile::E_UP:	 r = -1; break;
	case cTile::E_DOWN:	 r =  1; break;
	}
	
	return vecTile[(m_nRow + r) * TILE_H + m_nCol + c];
}

void cTile::CheckDelete(vector<cTile*>& vecTile)
{
	if (m_nCheckDepth > 0) return;
	cTile* pRight = GetTile(vecTile, E_RIGHT);
	if (pRight)
	{
		int nCheckDepth = 
			pRight->CheckDelete(vecTile, E_RIGHT, 1, m_nTileType);
		if (m_nCheckDepth < nCheckDepth)
			m_nCheckDepth = nCheckDepth;
	}
		
		
	cTile* pDown = GetTile(vecTile, E_DOWN);
	if (pDown)
	{
		int nCheckDepth =
			pDown->CheckDelete(vecTile, E_DOWN, 1, m_nTileType);
		if (m_nCheckDepth < nCheckDepth)
			m_nCheckDepth = nCheckDepth;
	}
		
}

void cTile::Update()
{
}

void cTile::Render(HDC hdc)
{
	cUtil::DrawRect(hdc, m_rcTile);

	POINT pt;
	pt.x = (m_rcTile.left + m_rcTile.right) / 2;
	pt.y = (m_rcTile.top + m_rcTile.bottom) / 2;
	COLORREF c = RGB(255, 255, 255);
	switch (m_nTileType)
	{
	case 0: c = RGB(255, 0, 0); break;
	case 1: c = RGB(0, 255, 0); break;
	case 2: c = RGB(0, 0, 255); break;
	case 3: c = RGB(255, 0, 255); break;
	case 4: c = RGB(255, 255, 0); break;
	case 5: c = RGB(0, 255, 255); break;
	case 6: c = RGB(128, 128, 128); break;
	default:
		break;
	}
	
	cUtil::DrawCircle(hdc, TILE_SIZE / 2 - 2, pt, c);

	if (m_nCheckDepth >= 2)
	{
		cUtil::DrawX(hdc, m_rcTile);
	}

	string s = to_string(m_nCheckDepth);
	TextOut(hdc,
		m_rcTile.left,
		m_rcTile.top,
		s.c_str(),
		s.length());
}

