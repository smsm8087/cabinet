#include "stdafx.h"
#include "cUISlotContainer.h"
#include "cUISlot.h"

cUISlotContainer::cUISlotContainer()
	: m_nSpace(5)
{
}

cUISlotContainer::~cUISlotContainer()
{
}

void cUISlotContainer::SetSlot(int nNumSlot, const char* szSlotImage)
{
	SAFE_DELETE(m_pFirstChild);

	cImage* pSlotImg = cImage::Create(szSlotImage);
	ST_SIZE stSlotSize = pSlotImg->GetSize();

	int nMaxCol = m_stSize.nWidth / (stSlotSize.nWidth + m_nSpace);

	for (int i = 0; i < nNumSlot; i++)
	{
		cUISlot* pSlot = new cUISlot();
		
		pSlot->Init(stSlotSize);
		pSlot->SetImage(pSlotImg);
		pSlot->SetTag(i);
		int nRow = i / nMaxCol;
		int nCol = i % nMaxCol;
		POINT pt;
		pt.x = (stSlotSize.nWidth + m_nSpace) * nCol;
		pt.y = (stSlotSize.nHeight + m_nSpace) * nRow;
		pSlot->SetPosition(pt);
		AddChild(pSlot);
	}
}

void cUISlotContainer::AddItem(int nSlotNo, cUIItemImage * pItemImage)
{
	cUISlot* pSlot = dynamic_cast<cUISlot*>(m_pFirstChild->GetUIObject(nSlotNo));
	if (pSlot)
	{
		pSlot->SetItemImage(pItemImage);
	}
}
