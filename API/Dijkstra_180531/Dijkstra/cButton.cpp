#include "stdafx.h"
#include "cButton.h"

cButton::cButton() :m_eState(IDLE)
, m_iType(11)
, m_iXSize(100)
, m_iYSize(50)
, m_iDelegate(NULL)
{
}


cButton::~cButton()
{
}

void cButton::Init(POINT pos, char* str, int type)
{
	m_PPos = pos;

	m_RButton[IDLE].left = m_PPos.x - m_iXSize / 2;
	m_RButton[IDLE].top = m_PPos.y - m_iYSize / 2;
	m_RButton[IDLE].right = m_RButton[IDLE].left + m_iXSize;
	m_RButton[IDLE].bottom = m_RButton[IDLE].top + m_iYSize;

	m_RButton[MOUSEON] = m_RButton[IDLE];

	m_RButton[CLICKED].left = m_PPos.x - m_iXSize / 2 + 5;
	m_RButton[CLICKED].top = m_PPos.y - m_iYSize / 2 + 5;
	m_RButton[CLICKED].right = m_RButton[CLICKED].left + m_iXSize;
	m_RButton[CLICKED].bottom = m_RButton[CLICKED].top + m_iYSize;

	strcpy_s(m_cStr, str);
	m_iType = type;
}

void cButton::Update()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	RECT rc = m_RButton[IDLE];

	// 버튼 영역에 마우스 진입
	if (PtInRect(&rc, ptMouse)) {
		// 마우스 왼쪽 버튼 누름
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			m_eState = CLICKED;
		}
		else {
			if (m_eState == CLICKED) {
				// 버튼을 눌렀다고 판단
				m_iDelegate->OnClick(m_iType);
			}
			m_eState = MOUSEON;
		}
	}
	else
	{
		m_eState = IDLE;
	}
}

void cButton::Render(HDC hdc)
{
	// 색칠
	HBRUSH hBrush, hOldBrush;

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	// 사각형 그리기
	Rectangle(hdc, m_RButton[m_eState].left, m_RButton[m_eState].top, m_RButton[m_eState].right, m_RButton[m_eState].bottom);

	DeleteObject(hBrush);
	DeleteObject(hOldBrush);

	// 텍스트 쓰기
	char szBuf[32];
	HFONT myFont = CreateFont(m_iXSize / 10, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "궁서체");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);

	SetTextColor(hdc, RGB(150, 150, 150));
	SetTextAlign(hdc, TA_CENTER);

	wsprintf(szBuf, m_cStr);


	if (m_eState == CLICKED) {
		TextOut(hdc, m_PPos.x + 5, m_PPos.y, szBuf, strlen(szBuf));
	}
	else {
		if (m_eState == IDLE)
		{
			SetTextColor(hdc, RGB(0, 0, 0));
		}
		TextOut(hdc, m_PPos.x, m_PPos.y - 5, szBuf, strlen(szBuf));
		for (int i = 0; i < 5; i++)
		{
			MoveToEx(hdc, m_RButton[m_eState].left + i, m_RButton[m_eState].bottom + i, NULL);
			LineTo(hdc, m_RButton[m_eState].right + i, m_RButton[m_eState].bottom + i);
			MoveToEx(hdc, m_RButton[m_eState].right + i, m_RButton[m_eState].top + i, NULL);
			LineTo(hdc, m_RButton[m_eState].right + i, m_RButton[m_eState].bottom + i);
		}
	}

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void cButton::SetDelegate(iButtonDelegate * delegate)
{
	m_iDelegate = delegate;
}

iButtonDelegate * cButton::GetDelegate()
{
	return m_iDelegate;
}
