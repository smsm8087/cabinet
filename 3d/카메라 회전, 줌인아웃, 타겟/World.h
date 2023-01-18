#pragma once
class World
{
public:
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;

	D3DXVECTOR3 size;

	D3DXVECTOR3 pivot;

	D3DXMATRIX matWorld;
	D3DXMATRIX* parentWorld;

	D3DXMATRIX S, R, T;
	D3DXMATRIX* parentSWorld;

	vector<World*> children;

	World();
	~World();

	void Update();
	void SetWorld();

	D3DXVECTOR3 GetWorldPos();

	bool IsCollision(World* world);
};

