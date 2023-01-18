#pragma once
#include "Actor.h"
class Bullet :
	public Actor
{
public:
	Bullet();
	virtual ~Bullet();
private:
	Vertex * vertex;
	D3DXVECTOR2 mvDir;
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	float mfAngle;
	float mfSpeed;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SetBulletPos(D3DXVECTOR2 pos) { mPos = pos; }
	void SetDir(D3DXVECTOR2 dir) { mvDir = dir; }
};

