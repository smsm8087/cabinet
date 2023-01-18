#include "stdafx.h"
#include "cMyAccount.h"
#include"cButton.h"
#include"cImage.h"

cMyAccount::cMyAccount()
{
	FILE* fp = NULL;
	fopen_s(&fp, "accountdata.txt", "r");
	if (fp == nullptr)return;
	char a[1024];
	fgets(a, 1024, fp);
	fscanf_s(fp, "rcInven.left=%d;\n", &rcInven.left);
	fscanf_s(fp, "rcInven.top=%d;\n", &rcInven.top);
	fscanf_s(fp, "rcInven.width=%d;\n", &invenwidth);
	fscanf_s(fp, "rcInven.height=%d;\n", &invenheight);
	rcInven.right = rcInven.left + invenwidth;
	rcInven.bottom = rcInven.top + invenheight;
	fgets(a, 1024, fp);
	char*  backdata;
	for (size_t i = 0; i < 5; i++)
	{
		fgets(a, 1024, fp);
		strtok_s(a, "\n", &backdata);
		m_pImage[i] = new cImage(a);
	}
	fclose(fp);
	

}


cMyAccount::~cMyAccount()
{
}

void cMyAccount::Init(int Width, int Height, itemType itemtype, int nData)
{
	m_width = Width;
	m_height = Height;
	m_exitbutton = new cButton();
	m_nCount[2] = -1;
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			account = new Account();
			account->rcSlot.left = rcInven.left + m_width * j;
			account->rcSlot.top = rcInven.top + 100 + m_height * i;
			account->rcSlot.right = account->rcSlot.left + m_width;
			account->rcSlot.bottom = account->rcSlot.top + m_height;
			account->m_nDataNum = nData;
			account->m_nType = itemtype;
			m_vecAccount.push_back(account);
		}

	}
}

void cMyAccount::Update()
{
	rcMenubar.left = rcInven.left + 10;
	rcMenubar.top = rcInven.top + 40;
	rcMenubar.right = rcMenubar.left + 180;
	rcMenubar.bottom = rcMenubar.top + 40;
	

	rcExitbtn.left = rcMenubar.right - 40;
	rcExitbtn.top = rcMenubar.top;
	rcExitbtn.right = rcExitbtn.left + 30;
	rcExitbtn.bottom = rcExitbtn.top + 30;
	m_exitbutton->Init(rcExitbtn, "X");


	moveinven.left = rcInven.left;
	moveinven.top = rcInven.top;
	moveinven.right = rcInven.right;
	moveinven.bottom = rcMenubar.bottom - 10;

}

void cMyAccount::Render(HDC hdc)
{
	if (isenteraccount)
	{
		//inventory window
		Rectangle(hdc, rcInven.left, rcInven.top, rcInven.right, rcInven.bottom);
		//menu
		Rectangle(hdc, rcMenubar.left, rcMenubar.top, rcMenubar.right, rcMenubar.bottom);
		//btn
		m_exitbutton->Render(hdc);
		//Name
		TextOut(hdc, rcMenubar.left + (rcMenubar.right - rcMenubar.left) / 2 - 40,
			rcMenubar.top + (rcMenubar.bottom - rcMenubar.top) / 2 - 15, "<창고>", strlen("<창고>"));
		//slot
		for (auto p : m_vecAccount)
		{
			Rectangle(hdc, p->rcSlot.left, p->rcSlot.top, p->rcSlot.right, p->rcSlot.bottom);
		}
		//image
		rcImage[0] = m_vecAccount[0]->rcSlot;
		rcImage[1] = m_vecAccount[1]->rcSlot;
		rcImage[2] = m_vecAccount[2]->rcSlot;
		rcImage[3] = m_vecAccount[3]->rcSlot;
		rcImage[4] = m_vecAccount[4]->rcSlot;

		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->isdrawing)
			{
				m_pImage[i]->Render(hdc, rcImage[i], true);
			}
		}

	}
}

bool cMyAccount::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'P':
		{
			isenteraccount = true;
			return true;
		}break;

		default:
			break;
		}
	}
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		//ptinrect movebar

		if (PtInRect(&moveinven, pt))
		{
			isInvenmove = true;
		}
		//ptinrect movebar
		if (PtInRect(&rcExitbtn, pt))
		{
			isenteraccount = false;
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (PtInRect(&rcImage[i], pt))
			{
				m_pImage[i]->m_isclicked = true;
				ismoving = true;
				m_nCount[2] = i;
			}
		}
		for (auto p : m_vecAccount)
		{
			if (PtInRect(&p->rcSlot, pt))
			{
				p->isselected = true;
			}
		}

	}break;
	case WM_MOUSEMOVE:
	{
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		//ptinrect movebar

		if (isInvenmove)
		{
			rcInven.left = pt.x;
			rcInven.top = pt.y;
			rcInven.right = pt.x + 200;
			rcInven.bottom = pt.y + 400;
			for (size_t i = 0; i < 5; i++)
			{
				for (size_t j = 0; j < 5; j++)
				{
					if (i * 5 + j < m_vecAccount.size())
					{
						m_vecAccount[i * 5 + j]->rcSlot.left = rcInven.left + m_width * j;
						m_vecAccount[i * 5 + j]->rcSlot.top = rcInven.top + 100 + m_height * i;
						m_vecAccount[i * 5 + j]->rcSlot.right = account->rcSlot.left + m_width;
						m_vecAccount[i * 5 + j]->rcSlot.bottom = account->rcSlot.top + m_height;
					}
				}

			}
			return true;
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->m_isclicked && ismoving)
			{
				m_vecAccount[i]->rcSlot.left = pt.x;
				m_vecAccount[i]->rcSlot.top = pt.y;
				m_vecAccount[i]->rcSlot.right = pt.x + 40;
				m_vecAccount[i]->rcSlot.bottom = pt.y + 40;
			}
		}
	}break;
	case WM_LBUTTONUP:
	{
		isInvenmove = false;
		if (m_nCount[1] != -1)
		{
			m_pImage[m_nCount[1]]->isdrawing = true;
		}
		
		for (auto p : m_vecAccount)
		{
			if (p->isselected)
			{
				p->isdrawing = false;
			}
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->m_isclicked)
			{
				m_pImage[i]->isdrawing = false;
				ismoving = false;
				m_vecAccount[i]->rcSlot.left = rcInven.left + m_width * i;
				m_vecAccount[i]->rcSlot.top = rcInven.top + 100 + m_height;
				m_vecAccount[i]->rcSlot.right = m_vecAccount[i]->rcSlot.left + m_width;
				m_vecAccount[i]->rcSlot.bottom = m_vecAccount[i]->rcSlot.top + m_height;
			}
		}
	}break;
	}
	return false;
}
