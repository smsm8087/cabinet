#pragma once
#include "BulletManager.h"

class PlayerClass
{
private:
	struct Vertex {
		D3DXVECTOR3 position;
		DWORD color;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vertex() {}
		Vertex(float x, float y, DWORD color) {
			position = { x,y,0 };
			this->color = color;
		}
	};

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	Vertex* vertex;
	UINT vertexCount;

	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 viewPos;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	BulletManager* mBullet;
	float angle;

public:
	PlayerClass();
	~PlayerClass();

	void Update();
	void Render();

	float GetLeft() { return worldPos.x; }
	float GetRight() { return worldPos.x + 50; }
	float GetTop() { return worldPos.y; }
	float GetBottom() { return worldPos.y + 50; }
	BulletManager* GetmBullet() { return mBullet; }
};

