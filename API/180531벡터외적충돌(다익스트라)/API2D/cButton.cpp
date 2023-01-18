#include "stdafx.h"
#include "cButton.h"

cButton::cButton()
	: m_eButtonState(E_NORMAL)
	, m_pDelegate(NULL)
	, m_nTag(0)
{
}

cButton::~cButton()
{
}

void cButton::Init(RECT rc, const char * szText)
{
	m_rcArea = rc;
	m_aStateRect[E_NORMAL] = rc;
	m_aStateRect[E_NORMAL].bottom -= 5;
	m_aStateRect[E_NORMAL].right -= 5;

	m_aStateRect[E_MOUSEOVER] = rc;
	m_aStateRect[E_MOUSEOVER].bottom -= 5;
	m_aStateRect[E_MOUSEOVER].right -= 5;

	m_aStateRect[E_CLICKED] = rc;
	m_aStateRect[E_CLICKED].top += 5;
	m_aStateRect[E_CLICKED].left += 5;

	// m_szText = szText;
	// 문자열은 카피본을 사용
	strcpy_s(m_szText, szText);
}

void cButton::Update()
{
	
}

void cButton::Render(HDC hdc)
{
	cUtil::DrawRect(hdc, m_aStateRect[m_eButtonState]);
	if (m_eButtonState == E_NORMAL || m_eButtonState == E_MOUSEOVER)
	{
		RECT rc = m_aStateRect[m_eButtonState];
		for (int i = 0; i <= 5; i++)
		{
			MoveToEx(hdc, rc.left + i, rc.bottom + i, NULL);
			LineTo(hdc, rc.right + i, rc.bottom + i);

			MoveToEx(hdc, rc.right + i, rc.top + i, NULL);
			LineTo(hdc, rc.right + i, rc.bottom + i);
		}
	}
	
	if (m_eButtonState == E_NORMAL)
		SetTextColor(hdc, RGB(0, 0, 0));
	else 
		SetTextColor(hdc, RGB(128, 128, 128));
	
	DrawText(hdc, m_szText, strlen(m_szText),
		&m_aStateRect[m_eButtonState],
		DT_CENTER | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);
}

bool cButton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT ptMouse;
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);

		if (PtInRect(&m_rcArea, ptMouse))
		{
			if (m_eButtonState == E_MOUSEOVER)
			{
				m_eButtonState = E_CLICKED;
			}
			return true;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT ptMouse;
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);

		if (PtInRect(&m_rcArea, ptMouse))
		{
			m_eButtonState = E_MOUSEOVER;
			return true;
		}
		else
		{
			m_eButtonState = E_NORMAL;
			return false;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (m_eButtonState == E_CLICKED)
		{
			// 버튼 클릭
			if (m_pDelegate)
			{
				m_pDelegate->OnClick(this);
			}
			m_eButtonState = E_MOUSEOVER;
			return true;
		}
		return false;
	}
	break;
	}
	
	return false;
}
