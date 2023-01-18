#pragma once

#include "cUIButton.h"

class cUIImageButton : public cUIButton
{
protected:
	GETSET_ADDREF(cImage*, m_pNormal, NormalImage);
	GETSET_ADDREF(cImage*, m_pMouseOver, MouseOverImage);
	GETSET_ADDREF(cImage*, m_pSelected, SelectedImage);

public:
	cUIImageButton();
	virtual ~cUIImageButton();

	// cUIButton override
	virtual void Render(HDC hdc) override;
};

