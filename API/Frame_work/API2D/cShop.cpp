#include "stdafx.h"
#include "cShop.h"
#include"cButton.h"
#include"cImage.h"

cShop::cShop()
	
{
	FILE* fp = NULL;
	fopen_s(&fp, "shopdata.txt", "r");
	if (fp==nullptr)return;
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


cShop::~cShop()
{
}

void cShop::Init(int Width, int Height, itemType itemtype,int nData)
{
	//char a[1024] = "helmet.bmp";
	//m_pImage[0] = new cImage(a);
	
	
	
	m_exitbutton = new cButton();
	for (size_t i = 0; i < 5; i++)
	{
		m_pImage[i]->isdrawing = true;
	}
	m_width = Width;
	m_height = Height;
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			shp = new Shop();
			shp->rcSlot.left = rcInven.left+ m_width * j;
			shp->rcSlot.top = rcInven.top + 100 + m_height * i;
			shp->rcSlot.right = shp->rcSlot.left + m_width;
			shp->rcSlot.bottom = shp->rcSlot.top + m_height;
			shp->m_nDataNum = nData;
			shp->isselected = false;
			shp->m_nType = itemtype;
			m_vecShop.push_back(shp);
		}
	}
	
}

void cShop::Update()
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

void cShop::Render(HDC hdc)
{
	if (isentershop)
	{
		//inventory window
		Rectangle(hdc, rcInven.left, rcInven.top, rcInven.right, rcInven.bottom);
		//menu
		Rectangle(hdc, rcMenubar.left, rcMenubar.top, rcMenubar.right, rcMenubar.bottom);
		//btn
		m_exitbutton->Render(hdc);
		//Name
		TextOut(hdc, rcMenubar.left + (rcMenubar.right - rcMenubar.left) / 2-40,
			rcMenubar.top + (rcMenubar.bottom - rcMenubar.top) / 2-15,"<상점>",strlen("<상점>"));
		//slot
		for (auto p : m_vecShop)
		{
			Rectangle(hdc, p->rcSlot.left, p->rcSlot.top, p->rcSlot.right, p->rcSlot.bottom);
		}
		//image
		rcImage[0] = m_vecShop[0]->rcSlot;
		rcImage[1] = m_vecShop[1]->rcSlot;
		rcImage[2] = m_vecShop[2]->rcSlot;
		rcImage[3] = m_vecShop[3]->rcSlot;
		rcImage[4] = m_vecShop[4]->rcSlot;

		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->isdrawing)
			{
				m_pImage[i]->Render(hdc, rcImage[i], true);
			}
		}
	}
}

bool cShop::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'S':
		{
			isentershop = true;
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
			isentershop = false;
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (PtInRect(&rcImage[i], pt))
			{
				m_pImage[i]->m_isclicked = true;
				ismoving = true;
				m_nCount[0] = i;
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
					if (i * 5 + j < m_vecShop.size())
					{
						m_vecShop[i * 5 + j]->rcSlot.left = rcInven.left + m_width * j;
						m_vecShop[i * 5 + j]->rcSlot.top = rcInven.top + 100 + m_height * i;
						m_vecShop[i * 5 + j]->rcSlot.right = shp->rcSlot.left + m_width;
						m_vecShop[i * 5 + j]->rcSlot.bottom = shp->rcSlot.top + m_height;
					}
				}

			}
			return true;
		}
		
		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->m_isclicked && ismoving)
			{
				m_vecShop[i]->rcSlot.left = pt.x;
				m_vecShop[i]->rcSlot.top = pt.y;
				m_vecShop[i]->rcSlot.right = pt.x + 40;
				m_vecShop[i]->rcSlot.bottom = pt.y + 40;
			}
		}
		
		

	}break;
	case WM_LBUTTONUP:
	{
		isInvenmove = false;
		for (size_t i = 0; i < 5; i++)
		{
			if (m_pImage[i]->m_isclicked)
			{
				m_pImage[i]->isdrawing = false;
				ismoving = false;
				m_vecShop[i]->rcSlot.left = rcInven.left + m_width * i;
				m_vecShop[i]->rcSlot.top = rcInven.top + 100 + m_height;
				m_vecShop[i]->rcSlot.right = m_vecShop[i]->rcSlot.left + m_width;
				m_vecShop[i]->rcSlot.bottom = m_vecShop[i]->rcSlot.top + m_height;
			}
		}
		
	}break;
	}
	return false;
}
