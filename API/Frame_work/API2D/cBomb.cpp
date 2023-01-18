#include "stdafx.h"
#include "cBomb.h"
#include"cSpriteSheetAnimation.h"
#include"cImage.h"
cBomb::cBomb(int power)
	:m_pBombAni(NULL)
{
	m_nLeftPower = 1;
	m_nRightPower = 1;
	m_nUpPower = 1;
	m_nDownPower = 1;
	m_nPower = power;
}


cBomb::~cBomb()
{
	//SAFE_DELETE(m_pBombAni);

	SAFE_DELETE(m_leftPop);
	SAFE_DELETE(m_RightPop);
	SAFE_DELETE(m_UpPop);
	SAFE_DELETE(m_DownPop);
	SAFE_DELETE(m_CenterPop);
	SAFE_DELETE(m_Pathleft);
	SAFE_DELETE(m_PathRight);
	SAFE_DELETE(m_PathUp);
	SAFE_DELETE(m_PathDown);
}

void cBomb::Init(int row, int col)
{
	m_nRow = row;
	m_nCol = col;
	m_rcBomb.right = STAGE_START_X + row * 40 + 40;
	m_rcBomb.bottom = STAGE_START_Y + col * 40 + 40;
	m_rcBomb.left = m_rcBomb.right-40;
	m_rcBomb.top = m_rcBomb.bottom-44;
	m_vecrcBomb.push_back(m_rcBomb);

	
	

	m_pBombAni = new cSpriteSheetAnimation("image/bomb.bmp");
	m_pBombAni->SetInterval(0.7f);
	POINT pt; pt.x = 0; pt.y = 0;
	m_pBombAni->SetAnimationFrame(2,2,pt,ST_SIZE(40,44));
	//Pop

	m_leftPop = new cImage("image/bomb_line.bmp");
	m_RightPop = new cImage("image/bomb_line.bmp");
	m_UpPop = new cImage("image/bomb_line.bmp");
	m_DownPop = new cImage("image/bomb_line.bmp");
	m_CenterPop = new cImage("image/bomb_line.bmp");

	SetRect(&m_rcCenterPop, 0, 0, 40, 40);
	SetRect(&m_rcLeftPop, 120, 0, 160, 40);
	SetRect(&m_rcRightPop, 160, 0, 200, 40);
	SetRect(&m_rcUpPop, 40, 0, 80, 40);
	SetRect(&m_rcDownPop, 80, 0, 120, 40);


	m_Pathleft = new cImage("image/bomb_line.bmp");
	m_PathRight = new cImage("image/bomb_line.bmp");
	m_PathUp = new cImage("image/bomb_line.bmp");
	m_PathDown = new cImage("image/bomb_line.bmp");

	SetRect(&m_rcPathleft, 240, 0, 280, 40);
	SetRect(&m_rcPathright, 240, 0, 280, 40);
	SetRect(&m_rcPathUp, 200, 0, 240, 40);
	SetRect(&m_rcPathDown, 200, 0, 240, 40);


	//왼
	
	for (int i = 1; i <m_nPower; i++)
	{
		//왼쪽긴물줄기

		SetRect(&m_rcTile, m_rcBomb.left - i * 40, m_rcBomb.bottom - 40, m_rcBomb.right - i * 40, m_rcBomb.bottom);
		m_vecLeftBomb.push_back(m_rcTile);
	}
	SetRect(&m_rcTile, m_rcBomb.left - m_nPower * 40, m_rcBomb.bottom - 40, m_rcBomb.right - m_nPower * 40, m_rcBomb.bottom);
	m_vecLeftBomb.push_back(m_rcTile);
	//오
	
	for (int i = 1; i <m_nPower; i++)
	{
		//오른쪽긴물줄기
		SetRect(&m_rcTile, m_rcBomb.left + i * 40, m_rcBomb.bottom - 40, m_rcBomb.right + i * 40, m_rcBomb.bottom);
		m_vecRightBomb.push_back(m_rcTile);
	}
	SetRect(&m_rcTile, m_rcBomb.left + m_nPower * 40, m_rcBomb.bottom - 40, m_rcBomb.right + m_nPower * 40, m_rcBomb.bottom);
	m_vecRightBomb.push_back(m_rcTile);
	
	//위

	
	for (int i = 1; i <m_nPower; i++)
	{
		//위쪽긴물줄기
		SetRect(&m_rcTile, m_rcBomb.left, m_rcBomb.bottom - 40 - i * 40, m_rcBomb.right, m_rcBomb.bottom - i * 40);
		m_vecUpBomb.push_back(m_rcTile);
	}
	SetRect(&m_rcTile, m_rcBomb.left, m_rcBomb.bottom - 40 - m_nPower * 40, m_rcBomb.right, m_rcBomb.bottom - m_nPower * 40);
	m_vecUpBomb.push_back(m_rcTile);
	//아래
	
	for (int i = 1; i <m_nPower; i++)
	{
		//아래쪽긴물줄기
		SetRect(&m_rcTile, m_rcBomb.left, m_rcBomb.bottom - 40 + i * 40, m_rcBomb.right, m_rcBomb.bottom + i * 40);
		m_vecBottomBomb.push_back(m_rcTile);
	}
	SetRect(&m_rcTile, m_rcBomb.left, m_rcBomb.bottom - 40 + m_nPower * 40, m_rcBomb.right, m_rcBomb.bottom + m_nPower * 40);
	m_vecBottomBomb.push_back(m_rcTile);

	//센터
	m_vecAllBomb.push_back(m_vecrcBomb);
	m_vecAllBomb.push_back(m_vecLeftBomb);
	m_vecAllBomb.push_back(m_vecRightBomb);
	m_vecAllBomb.push_back(m_vecUpBomb);
	m_vecAllBomb.push_back(m_vecBottomBomb);
}

void cBomb::Update()
{
	
	m_pBombAni->Update();
	m_fBombTime += g_pTimeManager->GetElapsedTime();
	if (m_fBombTime >= 2.5f && m_isPopBomb == false)
	{
		m_fBombTime -= 2.5f;
		m_isPopBomb = true;
	}
	if (m_isPopBomb)
	{
		m_fPopBombTime += g_pTimeManager->GetElapsedTime();
		if (m_fPopBombTime >= 0.5f)
		{
			m_fPopBombTime -= 0.5f;
			m_isEndBomb = true;
		}
	}

}

void cBomb::Render(HDC hdc)
{
	if(!m_isPopBomb)//풍선이 터지지않았을때
		m_pBombAni->Render(hdc,m_rcBomb);
	else//풍선이 터졌을때
	{
		if (!m_isEndBomb)//풍선터지는게 끝나지 않았을때
		{
			m_CenterPop->TransparentRender(hdc, m_vecrcBomb[0], m_rcCenterPop);
			
			for (int i = 1; i <= m_nLeftPower; ++i)
			{
				if (m_vecLeftBomb.size() <= i - 1)break;
				if (i == m_nPower)
				{
					m_leftPop->TransparentRender(hdc,m_vecLeftBomb[i-1], m_rcLeftPop);
				}
				else
				{
					m_Pathleft->TransparentRender(hdc, m_vecLeftBomb[i - 1], m_rcPathleft);
				}
				
			}

			for (int i = 1; i <= m_nRightPower; ++i)
			{
				if (i == m_nPower)
				{
					m_RightPop->TransparentRender(hdc, m_vecRightBomb[i-1], m_rcRightPop);
				}
				else
				{
					m_PathRight->TransparentRender(hdc, m_vecRightBomb[i - 1], m_rcPathright);
				}
			}
			for (int i = 1; i <= m_nUpPower; i++)
			{
				if (i == m_nPower)
				{
					m_UpPop->TransparentRender(hdc, m_vecUpBomb[i - 1], m_rcUpPop);
				}
				else
				{
					m_PathUp->TransparentRender(hdc, m_vecUpBomb[i - 1], m_rcPathUp);
				}
			}
			for (int i = 1; i <= m_nDownPower; i++)
			{
				if (i == m_nPower)
				{
					m_DownPop->TransparentRender(hdc, m_vecBottomBomb[i - 1], m_rcDownPop);
				}
				else
				{
					m_PathDown->TransparentRender(hdc, m_vecBottomBomb[i - 1], m_rcPathDown);
				}
			}
		}
	}
}

