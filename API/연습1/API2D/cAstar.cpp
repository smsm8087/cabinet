#include "stdafx.h"
#include "cAstar.h"



cAstar::cAstar()
	:m_MapCount(0)
	, m_Row(0)
	, m_Col(0)
	, m_mapTileSize(0)
	, m_TileCount(0)
{
}


cAstar::~cAstar()
{
}

void cAstar::Init()
{

	m_mapTileSize = 50;
	POINT pt;
	pt.x = 0;
	pt.y = 0;

	FILE* fp = nullptr;

	fopen_s(&fp, "data.txt", "r");
	if (fp == nullptr) return;

	
	fscanf_s(fp, "%d", &m_Row);
	fscanf_s(fp, "%d", &m_Col);

	while (!feof(fp))
	{
		
		fscanf_s(fp, "%d", &pt.x);
		fscanf_s(fp, "%d", &pt.y);

		m_vecPoint.push_back(pt);
	}

	fclose(fp);

	int RectLen = m_Row * m_Col;
	for (int i = 0; i < RectLen; i++)
	{
		POINT RectPt;
		RectPt.x = i / m_Col;
		RectPt.y = i % m_Col;
		m_vecRectInfo.push_back(RectInfo(0, 0, 0, E_NONE, RectPt, RectPt.x, RectPt.y));
		for (auto p : m_vecPoint)
		{
			if (RectPt.x*50 == p.x && RectPt.y*50 == p.y)
			{
				m_vecRectInfo.back().RectState = E_WALL;
			}
		}
	}


	

}

void cAstar::Render(HDC hdc)
{
	RECT rc;
	//FillRect(hdc, &rc, GetSysColorBrush(COLOR_WINDOW));



	for (int i = 0; i < m_Row; i++)
	{
		for (int j = 0; j < m_Col; j++)
		{
			Rectangle(hdc, i * 50, j * 50, (i * 50) + m_mapTileSize, (j * 50) + m_mapTileSize);
		}
	}

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	for (auto a : m_vecPoint)
	{
		Rectangle(hdc, a.x, a.y, a.x + m_mapTileSize, a.y + m_mapTileSize);
	}

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);




}

void cAstar::Update()
{

}

void cAstar::Astar()
{
	//F = G+H
	int Start = -1;
	int End = 0;

}