#include "stdafx.h"
#include "cUISlot.h"
#include "cUIItemImage.h"

cUISlot::cUISlot()
{
}

cUISlot::~cUISlot()
{
}

void cUISlot::SetItemImage(cUIItemImage * pItemImage)
{
	SAFE_DELETE(m_pFirstChild);
	AddChild(pItemImage);
}
