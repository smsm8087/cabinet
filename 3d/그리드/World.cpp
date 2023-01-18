#include "stdafx.h"
#include "World.h"


World::World()
{
	pos = { 0, 0, 0 };
	rot = { 0, 0, 0 };
	scale = { 1, 1, 1 };
	size = { 0, 0, 0 };
	pivot = { 0, 0, 0 };
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

	D3DXMatrixTranslation(&P, pivot.x, pivot.y, pivot.z);
	D3DXMatrixInverse(&IP, NULL, &P);

	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&matR, rot.y, rot.x, rot.z);

	S = IP * matS * P;
	R = IP * matR * P;
	D3DXMatrixTranslation(&T, pos.x, pos.y, pos.z);

	matWorld = S * R * T;

	if (parentWorld)
	{
		if (parentSWorld)
		{
			D3DXMATRIX invScale;
			D3DXMatrixInverse(&invScale, NULL, parentSWorld);
			matWorld *= invScale * *parentWorld;
		}else
			matWorld *= *parentWorld;
	}

	for (auto child : children)
		child->Update();
}

void World::SetWorld()
{
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
}
D3DXVECTOR3 World::GetWorldPos()
{
	D3DXMATRIX pWorld, IS, IR;
	D3DXMatrixInverse(&IS, NULL, &S);
	D3DXMatrixInverse(&IR, NULL, &R);
	pWorld = IR * IS * matWorld;

	/*D3DXVECTOR3 resultVec = { pos.x * pWorld._11 + pos.y * pWorld._21 + pos.z * pWorld._31,
							pos.x * pWorld._12 + pos.y * pWorld._22 + pos.z * pWorld._32,
							pos.x * pWorld._13 + pos.y * pWorld._23 + pos.z * pWorld._33 };*/
	D3DXVECTOR3 resultVec;
	//resultVec = { pWorld._41, pWorld._42, pWorld._43 };
	D3DXVec3TransformCoord(&resultVec, &pos, &matWorld);
	return resultVec;
}
