#include "stdafx.h"
#include "cBag.h"
#include "cButton.h"
#include "cImage.h"

cBag::cBag()
{
	FILE* fp = NULL;
	fopen_s(&fp, "bagdata.txt", "r");
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


cBag::~cBag()
{
}

void cBag::Init(int Width, int Height, itemType itemtype, int nData)
{
	m_nCount[1] = -1;
	m_exitbutton = new cButton();
	m_width = Width;
	m_height = Height;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			bag = new Bag();
			bag->rcSlot.left = rcInven.left + m_width * j;
			bag->rcSlot.top = rcInven.top + 100 + m_height * i;
			bag->rcSlot.right = bag->rcSlot.left + m_width;
			bag->rcSlot.bottom = bag->rcSlot.top + m_height;
			bag->m_nDataNum = nData;
			bag->m_nType = itemtype;
			m_vecBag.push_back(bag);
		}

	}
}

void cBag::Update()
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

void cBag::Render(HDC hdc)
{
	if (isenterbag)
	{
		//inventory window

		Rectangle(hdc, rcInven.left, rcInven.top, rcInven.right, rcInven.bottom);
		//menu
		Rectangle(hdc, rcMenubar.left, rcMenubar.top, rcMenubar.right, rcMenubar.bottom);
		//btn
		m_exitbutton->Render(hdc);
		//Name
		TextOut(hdc, rcMenubar.left + (rcMenubar.right - rcMenubar.left) / 2 - 40,
			rcMenubar.top + (rcMenubar.bottom - rcMenubar.top) / 2 - 15, "<가방>", strlen("<가방>"));
		//slot
		for (auto p : m_vecBag)
		{
			Rectangle(hdc, p->rcSlot.left, p->rcSlot.top, p->rcSlot.right, p->rcSlot.bottom);
		}

		//image
		rcImage[0] = m_vecBag[0]->rcSlot;
		rcImage[1] = m_vecBag[1]->rcSlot;
		rcImage[2] = m_vecBag[2]->rcSlot;
		rcImage[3] = m_vecBag[3]->rcSlot;
		rcImage[4] = m_vecBag[4]->rcSlot;

		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->isdrawing)
			{
				m_pImage[i]->Render(hdc, rcImage[i], true);
			}
		}
	}
}

bool cBag::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'I':
		{
			isenterbag = true;
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
		//ptinrect exit
		if (PtInRect(&rcExitbtn, pt))
		{
			isenterbag = false;
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (PtInRect(&rcImage[i], pt))
			{
				m_pImage[i]->m_isclicked = true;
				ismoving = true;
				m_nCount[1] = i;
			}
		}
		for (auto p : m_vecBag)
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
					if (i * 5 + j < m_vecBag.size())
					{
						m_vecBag[i * 5 + j]->rcSlot.left = rcInven.left + m_width * j;
						m_vecBag[i * 5 + j]->rcSlot.top = rcInven.top + 100 + m_height * i;
						m_vecBag[i * 5 + j]->rcSlot.right = bag->rcSlot.left + m_width;
						m_vecBag[i * 5 + j]->rcSlot.bottom = bag->rcSlot.top + m_height;
					}
				}

			}
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->m_isclicked && ismoving)
			{
				m_vecBag[i]->rcSlot.left = pt.x;
				m_vecBag[i]->rcSlot.top = pt.y;
				m_vecBag[i]->rcSlot.right = pt.x + 40;
				m_vecBag[i]->rcSlot.bottom = pt.y + 40;
			}
		}

	}break;
	case WM_LBUTTONUP:
	{
		isInvenmove = false;

		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		m_pImage[m_nCount[0]]->isdrawing = true;
		if (m_nCount[2] != -1)
		{
			m_pImage[m_nCount[2]]->isdrawing = true;
		}
		for (auto p : m_vecBag)
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
				m_vecBag[i]->rcSlot.left = rcInven.left + m_width * i;
				m_vecBag[i]->rcSlot.top = rcInven.top + 100 + m_height;
				m_vecBag[i]->rcSlot.right = m_vecBag[i]->rcSlot.left + m_width;
				m_vecBag[i]->rcSlot.bottom = m_vecBag[i]->rcSlot.top + m_height;
			}
		}
		
		//ptinrect moveitem
		
	}break;
	}
	return false;
}
