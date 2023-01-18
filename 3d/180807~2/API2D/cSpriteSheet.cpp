#include "stdafx.h"
#include "cSpriteSheet.h"
#include "cImage.h"

cSpriteSheet::cSpriteSheet(const char* szSheetPath)
{
	//m_pSpriteSheet = new cImage(szSheetPath);
}

cSpriteSheet::~cSpriteSheet()
{
	SAFE_DELETE(m_pSpriteSheet);
}

void cSpriteSheet::SetNumResion(int nNumRsn)
{
	m_vecResion.resize(nNumRsn);
}

size_t cSpriteSheet::GetNumResion()
{
	return m_vecResion.size();
}

void cSpriteSheet::SetResion(int nRsnNo, RECT rcSrc)
{
	m_vecResion[nRsnNo] = rcSrc;
}

void cSpriteSheet::SetResionName(int nRsnNo, string sRsnName)
{
	m_mapResion[sRsnName] = nRsnNo;
}

void cSpriteSheet::Render(HDC hdc, int nRsnNo, RECT rcDst, bool isTransparent)
{
	if (isTransparent)
	{
		//m_pSpriteSheet->TransparentRender(hdc, rcDst, m_vecResion[nRsnNo]);
	}
	else
	{
		POINT pt;
		pt.x = m_vecResion[nRsnNo].left;
		pt.y = m_vecResion[nRsnNo].top;
		//m_pSpriteSheet->Render(hdc, rcDst, pt);
	}
}
