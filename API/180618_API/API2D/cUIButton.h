#pragma once

#include "cUIObject.h"

class cUIButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_CLICKED,
		E_STATE_COUNT
	};

protected:
	
	char			m_szText[64];
	eButtonState	m_eButtonState;
	RECT			m_aStateRect[E_STATE_COUNT];

	GETSET(iButtonDelegate*, m_pDelegate, Delegate);
	//GETSET(int, m_nTag, Tag);
	//GETSETREF(RECT, m_rcArea, Area);

public:
	cUIButton();
	virtual ~cUIButton();

	// cUIObject override
	//virtual void Init(ST_SIZE stSize) override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

