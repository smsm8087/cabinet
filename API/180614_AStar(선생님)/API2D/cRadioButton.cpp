#include "stdafx.h"
#include "cRadioButton.h"

#define ITEM_HEIGHT 20

cRadioButton::cRadioButton()
	: m_nSelectedItem(0)
	, m_pDelegate(NULL)
{
}


cRadioButton::~cRadioButton()
{
}

void cRadioButton::Init(RECT rc)
{
	m_rcArea = rc;
}

void cRadioButton::Update()
{
	
}

void cRadioButton::Render(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 0, 0));
	RECT rc = m_rcArea;
	cUtil::DrawRect(hdc, m_rcArea);
	
	for (size_t i = 0; i < m_vecText.size(); i++)
	{
		cVector2 vCenter(m_rcArea.left + 15, m_rcArea.top + 10 + 20 * i);
		cUtil::DrawCircle(hdc, 7, vCenter);
		rc.left = m_rcArea.left + 30;
		rc.top = m_rcArea.top + i * ITEM_HEIGHT;
		rc.bottom = m_rcArea.top + (i + 1) * ITEM_HEIGHT;
		DrawText(hdc, m_vecText[i].c_str(), m_vecText[i].length(),
			&rc,
			DT_LEFT | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);
		if(i == m_nSelectedItem)
			cUtil::DrawCircle(hdc, 3, vCenter);
	}
}

void cRadioButton::AddItem(string s)
{
	m_vecText.push_back(s);
	m_rcArea.bottom = m_rcArea.top + m_vecText.size() * ITEM_HEIGHT;
}

bool cRadioButton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			RECT rc = m_rcArea;
			for (size_t i = 0; i < m_vecText.size(); i++)
			{
				rc.top = m_rcArea.top + i * ITEM_HEIGHT;
				rc.bottom = m_rcArea.top + (i + 1) * ITEM_HEIGHT;
				if (PtInRect(&rc, ptMouse))
				{
					m_nSelectedItem = i;
					if (m_pDelegate)
						m_pDelegate->OnSelectedItemChange(this);
					return true;
				}
			}
		}
	}
	break;
	}
	
	return false;
}
