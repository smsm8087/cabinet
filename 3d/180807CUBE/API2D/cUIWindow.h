#pragma once

#include "cUIObject.h"
#include "cUIImageButton.h"
#include "cImage.h"


class cUIWindow
	: public cUIObject
	, public iButtonDelegate
{
protected:
	bool			m_isPicked;
	POINT			m_ptPrevPosition;
	
	GETSET(string, m_sTitle, Title);
	GETSET(float, m_fTitleBarHeight, TitleBarHeight);
	GETSET_ADDREF(cImage*, m_pTitleBarBack, TitleBarBack);
	/*
	GETSET_ADDREF(cImage*, m_pCloseBtnN, CloseBtnN);
	GETSET_ADDREF(cImage*, m_pCloseBtnM, CloseBtnM);
	GETSET_ADDREF(cImage*, m_pCloseBtnS, CloseBtnS);
	*/
public:
	cUIWindow();
	virtual ~cUIWindow();

	// cUIObject override
	virtual void Init(ST_SIZE stSize) override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  override;

	// iButtonDelegate override
	virtual void OnClick(cUIButton* pSender) override;
};

