#include "stdafx.h"
#include "Grid.h"


Grid::Grid()
{
	D3DXMatrixIdentity(&world);

	int lineNum = 10;
	float interval = 1.0f;

	DWORD c = 0xffffffff;

	for (int i = -lineNum; i <= lineNum; i++) {
		vertex.push_back(ColorVertex(-lineNum, 0, i, c));
		vertex.push_back(ColorVertex(lineNum, 0, i, c));

		vertex.push_back(ColorVertex(i, 0, -lineNum, c));
		vertex.push_back(ColorVertex(i, 0, lineNum, c));
	}

	c = 0xffff0000;
	vertex.push_back(ColorVertex(-lineNum, 0, 0, c));
	vertex.push_back(ColorVertex(lineNum, 0, 0, c));

	c = 0xff0000ff;
	vertex.push_back(ColorVertex(0, -lineNum, 0, c));
	vertex.push_back(ColorVertex(0, lineNum, 0, c));

	c = 0xff00ff00;
	vertex.push_back(ColorVertex(0, 0, -lineNum, c));
	vertex.push_back(ColorVertex(0, 0, lineNum, c));
}


Grid::~Grid()
{
}

void Grid::Render()
{
	DEVICE->SetFVF(ColorVertex::fvf);
	DEVICE->SetTexture(0, NULL);
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, vertex.size() / 2, vertex.begin()._Ptr, sizeof(ColorVertex));
}
