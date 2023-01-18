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

	playerTexture->Render();
	//���Ŀ��� ������.
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
