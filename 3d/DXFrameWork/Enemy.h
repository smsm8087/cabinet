#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
public:
	Enemy();
	virtual ~Enemy();

private:
	Vertex * vertex;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	float mfAngle;
	float mfSpeed;
	int mHp;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render();

public:
	void SetHp(int hp) { mHp = hp; }
	int GetHp() { return mHp; }
};

