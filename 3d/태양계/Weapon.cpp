#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon(D3DXVECTOR2 _pivot)
{
	weaponTexture = Texture::Add(L"image/sword.png");
	world = new World;
	weaponRotZ = 0;
	world->pivot = _pivot;
}


Weapon::~Weapon()
{
}

void Weapon::Update()
{
	weaponRotZ = atan2f(mousePos.y - world->pos.y, mousePos.x - world->pos.x);
	world->rot.z = weaponRotZ;
	world->Update();

	if (KEYBOARD->keyPress(VK_LBUTTON))
	{
		Bullet* bullet = new Bullet(weaponRotZ);
		bullet->world->pos = world->pos;
		bullets.push_back(bullet);
	}
	for (auto p : bullets)
	{
		p->Update();
		/*if (p->world->pos.x > 1400 || p->world->pos.x < 0 || p->world->pos.y > 800 || p->world->pos.y < 0)
		{
			SAFE_DELETE(p);
		}*/
	}
}

void Weapon::Render()
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

	weaponTexture->Render();
	for (auto p : bullets)
	{
		p->Render();
	}
	//���Ŀ��� ������.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
