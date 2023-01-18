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
	//글자의 색을 검정색으로 만듬
	SetTextColor(hdc, RGB(0, 0, 0));
	RECT rc;
	cUtil::DrawRect(hdc, m_rcArea);
	
	for (size_t i = 0; i < m_vecText.size(); i++)
	{
		cVector2 vCenter(m_rcArea.left + 15, m_rcArea.top + 10 + ITEM_HEIGHT * i);//렉트의 값들을 벡터의값으로바꾸기위해 캐스팅
		cUtil::DrawCircle(hdc, 7, vCenter);//반지름만큼 원을 하나씩 밑으로내려가면서 만든다.
		rc.left = m_rcArea.left + 30;
		rc.top = m_rcArea.top + i * ITEM_HEIGHT;
		rc.bottom = m_rcArea.top + (i + 1) * ITEM_HEIGHT;
		auto a = m_vecText[i];
		DrawText(hdc, m_vecText[i].c_str(), m_vecText[i].length(),//인자값을맞추기위해 string을 const형식인 c_str사용
			&rc,
			DT_LEFT | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);
		//이넘대신 사용
		if(i == m_nSelectedItem)
			cUtil::DrawCircle(hdc, 3, vCenter);
		
	}
}

void cRadioButton::AddItem(string s)
{
	m_vecText.push_back(s);
	m_rcArea.bottom = m_rcArea.top + m_vecText.size() * ITEM_HEIGHT;//위에것만하면 사각형이 포문을돌면서 더커지기떄문에 
																	//바텀을 맞춰준다
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
					m_nSelectedItem = i; //아이템번호를 저장
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
