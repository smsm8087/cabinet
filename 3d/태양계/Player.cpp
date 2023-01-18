#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	playerTexture = Texture::Add(L"image/character.png");
	world = new World;
	playerTexture->GetSize(&world->size);
	world->pivot = world->size * 0.5f;
	playerPivot = world->pivot;
}


Player::~Player()
{
	
}

void Player::Update()
{
	world->Update();
}

void Player::Render()
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

	playerTexture->Render();
	//알파연산 끝났다.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
