#pragma once
class World
{
public:
	D3DXVECTOR2 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR2 scale;

	D3DXVECTOR2 size;

	D3DXVECTOR2 pivot;

	D3DXMATRIX matWorld;
	D3DXMATRIX* parentWorld;
	World();
	~World();

	void Update();
	void SetWorld();
};

