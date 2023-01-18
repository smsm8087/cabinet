#pragma once
class Player :public Actor
{
public:
	Player();
	virtual ~Player();
private:
	Vertex * vertex;
	D3DXVECTOR2 worldPos2;
	D3DXVECTOR2 cameraPos;
	D3DXVECTOR2 mvDir;

	D3DXMATRIX world;
	D3DXMATRIX world2;
	D3DXMATRIX view;
	D3DXMATRIX view2;
	D3DXMATRIX projection;

	float mfAngle;
	float mfSpeed;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();
};

