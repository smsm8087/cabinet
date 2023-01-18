#pragma once

#include "cUIObject.h"

class cUIItemImage;
class cUISlotContainer : public cUIObject
{
	GETSET(int, m_nSpace, Space);
public:
	cUISlotContainer();
	virtual ~cUISlotContainer();

	virtual void SetSlot(int nNumSlot, const char* szSlotImage);
	virtual void AddItem(int nSlotNo, cUIItemImage* pItemImage);
};

