#pragma once

class cButton;

class iButtonDelegate
{
public:
	virtual void OnClick(cButton* pSender) = 0;
};

class cButton
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
	RECT			m_rcArea;
	char			m_szText[64];
	eButtonState	m_eButtonState;
	RECT			m_aStateRect[E_STATE_COUNT];
	GETSET(iButtonDelegate*, m_pDelegate, Delegate);
	GETSET(int, m_nTag, Tag);
public:
	cButton();
	virtual ~cButton();

	void Init(RECT rc, const char* szText);
	void Update();
	void Render(HDC hdc);
};

