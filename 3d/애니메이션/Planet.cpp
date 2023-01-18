#include "stdafx.h"
#include "Planet.h"


Planet::Planet(wstring fileName)
{
	texture = Texture::Add(fileName);
	world = new World;
	rotSpeed = 0;
	texture->GetSize(&world->size);
	world->pivot = world->size * 0.5f;
}

Planet::~Planet()
{
}

void Planet::Update()
{
	world->rot.z += rotSpeed;
	world->Update();
}

void Planet::Render()
{
	world->SetWorld();
	
	//���Ŀ����� �����ϰڴ�.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//���Ŀ����� �ϴµ� �������� �����ϰڴ�.
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	//DEST : �ѷ����� �� ����� ����
	//SRC : �ѷ����� ����
	//SRCALPHA : �Ѹ� ������ ���İ�
	//INVSRCALPHA : 1 - SRCALPHA

	//�� ��� �����ٰ� �Ѹ� ������ ������ ���ϰڴ�.
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�Ѹ� ���򿡴ٰ� �ڱ��ڽ��� ���İ��� ���ϰڴ�.
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	texture->Render();

	//���Ŀ��� ������.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
