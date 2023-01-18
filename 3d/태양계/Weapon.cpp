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

	//알파연산을 시작하겠다.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//알파연산을 하는데 덧셈으로 연산하겠다.
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	//DEST : 뿌려지는 뒷 배경의 색깔
	//SRC : 뿌려지는 색깔
	//SRCALPHA : 뿌릴 색깔의 알파값
	//INVSRCALPHA : 1 - SRCALPHA

	//뒷 배경 색에다가 뿌릴 색깔의 역수를 곱하겠다.
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//뿌릴 색깔에다가 자기자신의 알파값을 곱하겠다.
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	weaponTexture->Render();
	for (auto p : bullets)
	{
		p->Render();
	}
	//알파연산 끝났다.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
