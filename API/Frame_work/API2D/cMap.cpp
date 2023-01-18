#include "stdafx.h"
#include "cMap.h"
#include"cImage.h"

cMap::cMap()
{
}


cMap::~cMap()
{
}

void cMap::Init()
{
	fp = NULL;
	fopen_s(&fp, "stage2.txt", "r");
	
	if (!fp)return;
	char szBuf[1024];

	for (int i = 0; i < STAGE_COL; i++)
	{
		fgets(szBuf, 1024, fp);
		char* backData;
		for (int j = 0; j < STAGE_ROW; j++)
		{
			strtok_s(szBuf, " ", &backData);
			m_nTile[i][j] = atoi(szBuf);
			//m_vecTileSource.push_back(&m_nTile[i][j]);
			
			m_rcTile[i][j].left = j * TILE_W + STAGE_START_X;
			m_rcTile[i][j].right = m_rcTile[i][j].left + TILE_W;
			m_rcTile[i][j].top = i * TILE_H + STAGE_START_Y;
			m_rcTile[i][j].bottom = m_rcTile[i][j].top + TILE_H;

			//m_vecTileRect.push_back(&m_rcTile[i][j]);
			if (m_nTile[i][j] != 0)
			{
				m_bRoad[i][j] = false;
			}
			else
				m_bRoad[i][j] = true;
			strcpy_s(szBuf, 1024, backData);
		}
	}

	fclose(fp);
	m_pRedBlock			= new cImage("image/block_red.bmp");
	m_pOrangeBlock		= new cImage("image/block_orange.bmp");
	m_pRedHouse			= new cImage("image/house_red.bmp");
	m_pBlueHouse		= new cImage("image/house_blue.bmp");
	m_pYellowHouse		= new cImage("image/house_yellow.bmp");
	m_pTree				= new cImage("image/tree.bmp");
}

void cMap::Update()
{
}

void cMap::Render(HDC hdc)
{

	for (size_t i = 0; i < STAGE_COL; i++)
	{
		for (size_t j = 0; j < STAGE_ROW; j++)
		{
			switch (m_nTile[i][j])
			{
			case 1:
			{
				RECT rcBlock;
				m_ptPivot[0].x = m_rcTile[i][j].left + (m_rcTile[i][j].right - m_rcTile[i][j].left) / 2;
				m_ptPivot[0].y = m_rcTile[i][j].top + (m_rcTile[i][j].bottom - m_rcTile[i][j].top) / 2;
				SetRect(&rcBlock, m_ptPivot[0].x - m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[0].y - m_pRedBlock->GetstSize().nHeight / 2
					, m_ptPivot[0].x + m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[0].y + m_pRedBlock->GetstSize().nHeight / 2);
				m_pRedBlock->RenderCharater(hdc, rcBlock, true);
			}break;
			case 2:
			{
				RECT rcBlock;
				m_ptPivot[1].x = m_rcTile[i][j].left + (m_rcTile[i][j].right - m_rcTile[i][j].left) / 2;
				m_ptPivot[1].y = m_rcTile[i][j].top + (m_rcTile[i][j].bottom - m_rcTile[i][j].top) / 2;
				SetRect(&rcBlock, m_ptPivot[1].x - m_pOrangeBlock->GetstSize().nWidth / 2, m_ptPivot[1].y - m_pOrangeBlock->GetstSize().nHeight / 2
					, m_ptPivot[1].x + m_pOrangeBlock->GetstSize().nWidth / 2, m_ptPivot[1].y + m_pOrangeBlock->GetstSize().nHeight / 2);
				m_pOrangeBlock->RenderCharater(hdc, rcBlock, true);
			}break;
			case 3:
			{
				RECT rcBlock;
				m_ptPivot[2].x = m_rcTile[i][j].left + (m_rcTile[i][j].right - m_rcTile[i][j].left) / 2;
				m_ptPivot[2].y = m_rcTile[i][j].top + (m_rcTile[i][j].bottom - m_rcTile[i][j].top) / 2;
				SetRect(&rcBlock, m_ptPivot[2].x - m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[2].y - m_pRedHouse->GetstSize().nHeight / 2
					-(m_pRedHouse->GetstSize().nHeight / 2- m_pRedBlock->GetstSize().nHeight / 2)
					, m_ptPivot[2].x + m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[2].y + m_pRedBlock->GetstSize().nHeight / 2);
				m_pRedHouse->RenderCharater(hdc, rcBlock, true);
			}break;
			case 4:
			{
				RECT rcBlock;
				m_ptPivot[3].x = m_rcTile[i][j].left + (m_rcTile[i][j].right - m_rcTile[i][j].left) / 2;
				m_ptPivot[3].y = m_rcTile[i][j].top + (m_rcTile[i][j].bottom - m_rcTile[i][j].top) / 2;
				SetRect(&rcBlock, m_ptPivot[3].x - m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[3].y - m_pBlueHouse->GetstSize().nHeight / 2
					- (m_pBlueHouse->GetstSize().nHeight / 2 - m_pRedBlock->GetstSize().nHeight / 2)
					, m_ptPivot[3].x + m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[3].y + m_pRedBlock->GetstSize().nHeight / 2);
				m_pBlueHouse->RenderCharater(hdc, rcBlock, true);
			}break;
			case 5:
			{
				RECT rcBlock;
				m_ptPivot[4].x = m_rcTile[i][j].left + (m_rcTile[i][j].right - m_rcTile[i][j].left) / 2;
				m_ptPivot[4].y = m_rcTile[i][j].top + (m_rcTile[i][j].bottom - m_rcTile[i][j].top) / 2;
				SetRect(&rcBlock, m_ptPivot[4].x - m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[4].y - m_pYellowHouse->GetstSize().nHeight / 2
					- (m_pYellowHouse->GetstSize().nHeight / 2 - m_pRedBlock->GetstSize().nHeight / 2)
					, m_ptPivot[4].x + m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[4].y + m_pRedBlock->GetstSize().nHeight / 2);
				m_pYellowHouse->RenderCharater(hdc, rcBlock, true);
			}break;
			case 6:
			{
				RECT rcBlock;
				m_ptPivot[5].x = m_rcTile[i][j].left + (m_rcTile[i][j].right - m_rcTile[i][j].left) / 2;
				m_ptPivot[5].y = m_rcTile[i][j].top + (m_rcTile[i][j].bottom - m_rcTile[i][j].top) / 2;
				SetRect(&rcBlock, m_ptPivot[5].x - m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[5].y - m_pTree->GetstSize().nHeight / 2
					- (m_pTree->GetstSize().nHeight / 2 - m_pRedBlock->GetstSize().nHeight / 2)
					, m_ptPivot[5].x + m_pRedBlock->GetstSize().nWidth / 2, m_ptPivot[5].y + m_pRedBlock->GetstSize().nHeight / 2);
				m_pTree->RenderCharater(hdc, rcBlock, true);
			}break;
			default:
				break;
			}
			
		}
	}
}
int cMap::GetTile(int x, int y)
{
	return m_nTile[x][y];
}
void cMap::SetTile(int x, int y,int num)
{
	m_nTile[x][y] = num;
}
bool cMap::GetRoad(int x, int y)
{
	return m_bRoad[x][y];
}
RECT cMap::GetRectTile(int x, int y)
{
	return m_rcTile[x][y];
}
void cMap::SetTileRect(int x, int y, int left, int top, int right, int bottom)
{
	m_rcTile[x][y].left = left;
	m_rcTile[x][y].top = top;
	m_rcTile[x][y].right = right;
	m_rcTile[x][y].bottom = bottom;
}
void cMap::SetBoolRoad(bool b, int x, int y)
{
	m_bRoad[x][y] = b;
}
bool cMap::GetBoolItem(int x, int y)
{
	return m_bItem[x][y];
}
void cMap::SetBoolItem(bool b, int x, int y)
{
	m_bItem[x][y] = b;
}