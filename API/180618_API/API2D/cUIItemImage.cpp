#include "stdafx.h"
#include "cUIItemImage.h"
#include "cUISlot.h"

cUIItemImage::cUIItemImage()
	: m_isPicked(false)
	, m_isAttatchToMouse(false)
{
}


cUIItemImage::~cUIItemImage()
{
}

void cUIItemImage::Render(HDC hdc)
{
	if (!m_isShow) return;

	if (m_pImage)
	{
		if (m_isAttatchToMouse)
		{
			m_pImage->Render(hdc, m_ptMouse, true);
		}
		else
		{
			m_pImage->Render(hdc, m_ptScreen, true);
		}
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

bool cUIItemImage::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (cUIObject::WndProc(hWnd, message, wParam, lParam)) return true;

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		RECT rc;
		SetRect(&rc,
			m_ptScreen.x,
			m_ptScreen.y,
			m_ptScreen.x + m_stSize.nWidth,
			m_ptScreen.y + m_stSize.nHeight);

		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);

		m_isPicked = PtInRect(&rc, pt);
		if (m_isPicked)
		{
			m_ptPickPosition = pt;
			return true;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_isPicked)
		{
			m_ptMouse.x = LOWORD(lParam);
			m_ptMouse.y = HIWORD(lParam);

			if (m_isAttatchToMouse == false)
			{
				float fLenSq = cUtil::LengthSq(m_ptMouse, m_ptPickPosition);
				if (fLenSq > 25.0f)
				{
					m_isAttatchToMouse = true;

					cUIObject* pRoot = GetRootUIObject();
					m_pParent->RemoveFirstChild();
					pRoot->AddChild(this);
				}
			}
			
			return true;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (m_isPicked == true)
		{
			m_isPicked = false;
			if (m_isAttatchToMouse)
			{
				cUIObject* pRoot = GetRootUIObject();
				m_ptMouse.x = LOWORD(lParam);
				m_ptMouse.y = HIWORD(lParam);
				list<cUIObject*> lst;
				pRoot->UIAtPoint(lst, m_ptMouse);

				cUISlot* pSlot = NULL;
				for (auto p : lst)
				{
					pSlot = dynamic_cast<cUISlot*>(p);
					if (pSlot)
					{
						break;
					}
				}

				if (pSlot)
				{
					m_pParent->RemoveChild(this, &m_pParent);
					pSlot->AddChild(this);
					m_isAttatchToMouse = false;
					m_isPicked = false;
				}
				else
				{
					//m_pParent->RemoveFirstChild();
					//delete this;
				}

			}
			return true;
		}
	}
	break;
	}
	return false;
}
