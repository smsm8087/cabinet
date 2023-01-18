#include "stdafx.h"
#include "cUIImageButton.h"


cUIImageButton::cUIImageButton()
	: m_pNormal(NULL)
	, m_pMouseOver(NULL)
	, m_pSelected(NULL)
{
}

cUIImageButton::~cUIImageButton()
{
	SAFE_RELEASE(m_pNormal);
	SAFE_RELEASE(m_pMouseOver);
	SAFE_RELEASE(m_pSelected);
}

void cUIImageButton::Render(HDC hdc)
{
	if (!m_isShow) return;

	POINT pt = m_ptPosition;

	if (m_eButtonState == E_CLICKED)
	{
		pt = cUtil::AddPoint(pt, 1);
	}

	switch (m_eButtonState)
	{
	case cUIButton::E_NORMAL:
		m_pNormal->Render(hdc, pt, true);
		break;
	case cUIButton::E_MOUSEOVER:
		m_pMouseOver->Render(hdc, pt, true);
		break;
	case cUIButton::E_CLICKED:
		m_pSelected->Render(hdc, pt, true);
		break;
	default:
		break;
	}

	if (m_pFirstChild) m_pFirstChild->Render(hdc);
	if (m_pSibling) m_pSibling->Render(hdc);
}
