#pragma once

class cButton;

//버튼의 대리자
class iButtonDelegate
{
public:
	//순수가상함수
	virtual void OnClick(cButton* pSender) = 0;
};

class cButton
{
protected:
	//버튼의 상태
	enum eButtonState
	{
		E_NORMAL,			//가만히잇냐
		E_MOUSEOVER,		//마우스가지나가냐
		E_CLICKED,			//마우스로 클릭했냐
		E_STATE_COUNT		//상태카운트
	};

protected:
	
	char			m_szText[64];
	eButtonState	m_eButtonState;//이넘변수
	RECT			m_aStateRect[E_STATE_COUNT];	//상태카운트만큼의 렉트
	//겟셋매크로 (타입 , 변수명 , 함수이름)
	GETSET(iButtonDelegate*, m_pDelegate, Delegate);
	GETSET(int, m_nTag, Tag);
	GETSETREF(RECT, m_rcArea, Area);

public:
	cButton();
	virtual ~cButton();

	void Init(RECT rc, const char* szText);
	void Update();
	void Render(HDC hdc);
	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

