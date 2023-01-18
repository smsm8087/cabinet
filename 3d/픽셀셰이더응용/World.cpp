#include "stdafx.h"
#include "World.h"


World::World()
{
	pos = { 0, 0 };
	rot = { 0, 0, 0 };
	scale = { 1, 1 };
	size = { 0, 0 };
	pivot = { 0, 0 };
	D3DXMatrixIdentity(&matWorld);
	parentWorld = NULL;
}


World::~World()
{
}

void World::Update()
{
	D3DXMATRIX P, IP;
	D3DXMATRIX matS, matR;
	D3DXMATRIX S, R, T;

	D3DXMatrixTranslation(&P, pivot.x, pivot.y, 0);
	D3DXMatrixInverse(&IP, NULL, &P);

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	D3DXMatrixRotationYawPitchRoll(&matR, rot.y, rot.x, rot.z);

	S = IP * matS * P;
	R = IP * matR * P;
	D3DXMatrixTranslation(&T, pos.x, pos.y, 0);

	matWorld = S * R * T;

	if (parentWorld)
		matWorld *= *parentWorld;
}

void World::SetWorld()
{
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
}
