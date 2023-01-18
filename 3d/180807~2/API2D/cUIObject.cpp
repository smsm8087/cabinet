#include "stdafx.h"
#include "cUIObject.h"
#include "cImage.h"

cUIObject::cUIObject()
	: m_pParent(NULL)
	, m_pFirstChild(NULL)
	, m_pSibling(NULL)
	, m_pImage(NULL)
	, m_nTag(0)
	, m_nDepth(0)
	, m_isShow(true)
	, m_stSize(0, 0)
	, m_isDebugMode(false)
{
	m_ptPosition.x = 0;
	m_ptPosition.y = 0;

	m_ptScreen.x = 0;
	m_ptScreen.y = 0;
}


cUIObject::~cUIObject()
{
	SAFE_RELEASE(m_pImage);

	Destroy();
}

void cUIObject::Init(ST_SIZE stSize)
{
	m_stSize = stSize;
}

void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->m_pParent = this;

	if (m_pFirstChild == NULL)
	{
		m_pFirstChild = pChild;
	}
	else
	{
		m_pFirstChild->AddSibling(pChild, &m_pFirstChild);
	}
}

void cUIObject::Update(POINT * pParent)
{
	m_ptScreen = m_ptPosition;
	if (pParent)
	{
		m_ptScreen = cUtil::AddPoint(m_ptPosition, *pParent);
	}

	if (m_pFirstChild) m_pFirstChild->Update(&m_ptScreen);
	if (m_pSibling) m_pSibling->Update(pParent);
}

void cUIObject::Render(HDC hdc)
{
	if (!m_isShow) return;

	if (m_pImage)
	{
		m_pImage->Render(hdc, m_ptScreen, true);
	}

	if (m_isDebugMode)
	{
		Rect rc(m_ptScreen.x, m_ptScreen.y, m_stSize.nWidth, m_stSize.nHeight);
		Graphics g(hdc);
		g.DrawRectangle(&Pen(&SolidBrush(Color::Red)), rc);
	}

	if (m_pFirstChild) m_pFirstChild->Render(hdc);
	if (m_pSibling) m_pSibling->Render(hdc);
}

bool cUIObject::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!m_isShow) return false;

	if (m_pFirstChild)
	{
		if (m_pFirstChild->WndProc(hWnd, message, wParam, lParam))
			return true;
	}

	if (m_pSibling)
	{
		if (m_pSibling->WndProc(hWnd, message, wParam, lParam))
			return true;
	}

	return false;
}

ST_SIZE cUIObject::GetImageSize()
{
	if (m_pImage) return m_pImage->GetSize();
	return ST_SIZE(0, 0);
}

void cUIObject::ToggleShow()
{
	m_isShow = !m_isShow;
}

void cUIObject::SetDebugMode(bool isDebugMode)
{
	m_isDebugMode = isDebugMode;
	if (m_pFirstChild) m_pFirstChild->SetDebugMode(isDebugMode);
	if (m_pSibling) m_pSibling->SetDebugMode(isDebugMode);
}

cUIObject * cUIObject::GetUIObject(int nTag)
{
	if (m_nTag == nTag) return this;
	
	cUIObject * pObject = NULL;
	if (m_pFirstChild)
	{
		pObject = m_pFirstChild->GetUIObject(nTag);
	}
	if (pObject) return pObject;

	if (m_pSibling)
	{
		pObject = m_pSibling->GetUIObject(nTag);
	}
	if (pObject) return pObject;

	return nullptr;
}

cUIObject * cUIObject::GetRootUIObject()
{
	if (m_pParent)
		return m_pParent->GetRootUIObject();
	return this;
}

void cUIObject::UIAtPoint(list<cUIObject*>& lst, POINT pt)
{
	if (m_pFirstChild)
	{
		m_pFirstChild->UIAtPoint(lst, pt);
	}

	if (m_pSibling)
	{
		m_pSibling->UIAtPoint(lst, pt);
	}

	if (PtInRect(&cUtil::MakeRect(m_ptScreen, m_stSize), pt))
	{
		lst.push_back(this);
	}
}

cUIObject * cUIObject::RemoveFirstChild()
{
	cUIObject * pChild = m_pFirstChild;
	m_pFirstChild = NULL;
	return pChild;
}

cUIObject* cUIObject::RemoveChild(cUIObject* pChild, cUIObject** ppThis)
{
	if (pChild == this)
	{
		*ppThis = m_pSibling;
		m_pSibling = NULL;
		m_pParent = NULL;
		return this;
	}

	cUIObject* pRemoveObject = NULL;
	if (m_pFirstChild)
	{
		pRemoveObject = m_pFirstChild->RemoveChild(pChild, &m_pFirstChild);
	}
	if (pRemoveObject) return pRemoveObject;

	if (m_pSibling)
	{
		pRemoveObject = m_pSibling->RemoveChild(pChild, &m_pSibling);
	}
	if (pRemoveObject) return pRemoveObject;

	return nullptr;
}

void cUIObject::Destroy()
{
	if (m_pFirstChild)
	{
		SAFE_DELETE(m_pFirstChild);
	}

	if (m_pSibling)
	{
		SAFE_DELETE(m_pSibling);
	}
}

void cUIObject::AddSibling(cUIObject * pSibling, cUIObject** ppThis)
{
	if (m_nDepth <= pSibling->m_nDepth)
	{
		*ppThis = pSibling;
		pSibling->m_pSibling = this;
	}
	else if(m_pSibling)
	{
		m_pSibling->AddSibling(pSibling, &m_pSibling);
	}
	else
	{
		m_pSibling = pSibling;
	}
}
