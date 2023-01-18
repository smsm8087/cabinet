#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(float _Rotz)
{
	texture = Texture::Add(L"image/bullet.png");
	world = new World;
	texture->GetSize(&world->size);
	world->pivot = world->size * 0.5f;
	bulletRotZ = _Rotz;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	world->Update();
	world->pos.x += cosf(bulletRotZ) * 10;//10�� �ӵ�
	world->pos.y += sinf(bulletRotZ) * 10;
}

void Bullet::Render()
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
