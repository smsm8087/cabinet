#pragma once

#include "cUIObject.h"

class cUIItemImage;

class cUISlot : public cUIObject
{
protected:
	cUIItemImage* m_pItemImage;

public:
	cUISlot();
	virtual ~cUISlot();

	void SetItemImage(cUIItemImage* pItemImage);
};

