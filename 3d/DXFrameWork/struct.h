#pragma once
struct Vertex
{
	D3DXVECTOR3 position;
	DWORD color;

	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	Vertex() {}
	Vertex(float x, float y, DWORD color)
	{
		position = { x, y, 0 };
		this->color = color;
	}
};

enum ClassType
{
	CTYPE_NONE,
	CTYPE_PLAYER,
	CTYPE_ENEMY,
	CTYPE_BULLET
};