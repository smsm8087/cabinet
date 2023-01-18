#include "stdafx.h"
#include "cAstar.h"


cAstar::cAstar()
	: m_MapCount(0)
	, m_Row(0)
	, m_Col(0)
	, m_TileCount(0)
	, m_mapTileSize(0)
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

	fscanf_s(fp, "%d", &m_MapCount);
	fscanf_s(fp, "%d", &m_Row);
	fscanf_s(fp, "%d", &m_Col);

	while (!feof(fp))
	{
		fscanf_s(fp, "%d", &m_TileCount);
		fscanf_s(fp, "%d", &pt.x);
		fscanf_s(fp, "%d", &pt.y);

		m_vecPoint.push_back(pt);
	}

	fclose(fp);


}

void cAstar::Render(HDC hdc)
{
}

void cAstar::Update()
{
}
