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
	// ���ڿ��� ī�Ǻ��� ���
	strcpy_s(m_szText, szText);
}

void cButton::Update()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	if (PtInRect(&m_rcArea, ptMouse))
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eButtonState == E_MOUSEOVER)
			{
				m_eButtonState = E_CLICKED;
			}
		}
		else
		{
			if (m_eButtonState == E_CLICKED)
			{
				// ��ư Ŭ��
				if (m_pDelegate)
				{
					m_pDelegate->OnClick(this);
				}
			}
			m_eButtonState = E_MOUSEOVER;
		}
	}
	else
	{
		m_eButtonState = E_NORMAL;
	}
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