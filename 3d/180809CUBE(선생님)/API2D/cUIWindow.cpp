#include "stdafx.h"
#include "cUIWindow.h"

cUIWindow::cUIWindow()
	: m_sTitle("Window")
	, m_fTitleBarHeight(30.f)
	, m_pTitleBarBack(NULL)
	, m_isPicked(false)
{
	m_ptPrevPosition = cUtil::PointZero();
}

cUIWindow::~cUIWindow()
{
	SAFE_RELEASE(m_pTitleBarBack);
}

void cUIWindow::Init(ST_SIZE stSize)
{
	cUIObject::Init(stSize);

	cUIImageButton* pCloseButton = new cUIImageButton;
	POINT pt;
	pt.x = stSize.nWidth - 29;
	pt.y = 1;
	pCloseButton->Init(ST_SIZE(28, 28));
	pCloseButton->SetPosition(pt);
	pCloseButton->SetNormalImage(cImage::Create("UI/xbtn_nor.bmp"));
	pCloseButton->SetMouseOverImage(cImage::Create("UI/xbtn_mov.bmp"));
	pCloseButton->SetSelectedImage(cImage::Create("UI/xbtn_sel.bmp"));
	pCloseButton->SetDelegate(this);
	AddChild(pCloseButton);
}

void cUIWindow::Render(HDC hdc)
{
	if (!m_isShow) return;

	Rectangle(hdc,
		m_ptScreen.x, 
		m_ptScreen.y, 
		m_ptScreen.x + m_stSize.nWidth, 
		m_ptScreen.y + m_stSize.nHeight);

	if (m_pImage)
	{
		POINT pt = m_ptScreen;
		pt.y += (int)m_fTitleBarHeight;
		m_pImage->Render(hdc, pt);
	}

	if (m_pTitleBarBack)
	{
		m_pTitleBarBack->Render(hdc, m_ptScreen);
	}
	else
	{
		Rectangle(hdc, 
			m_ptScreen.x, 
			m_ptScreen.y,
			m_ptScreen.x + m_stSize.nWidth, 
			m_ptScreen.y + m_fTitleBarHeight);
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

bool cUIWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (cUIObject::WndProc(hWnd, message, wParam, lParam))
	{
		return true;
	}

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		RECT rc;
		SetRect(&rc,
			m_ptScreen.x,
			m_ptScreen.y,
			m_ptScreen.x + m_stSize.nWidth,
			m_ptScreen.y + m_fTitleBarHeight);
		
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
	
		m_isPicked = PtInRect(&rc, pt);
		if (m_isPicked)
		{
			m_ptPrevPosition = pt;
			return true;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_isPicked)
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);

			POINT ptDelta = cUtil::SubPoint(pt, m_ptPrevPosition);
			m_ptPosition = cUtil::AddPoint(m_ptPosition, ptDelta);
			m_ptPrevPosition = pt;
			return true;
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (m_isPicked == true)
		{
			m_isPicked = false;
			return true;
		}
	}
	break;
	}
	return false;
}

void cUIWindow::OnClick(cUIButton * pSender)
{
	ToggleShow();
}
