#include "stdafx.h"
#include "CubeTexture.h"


CubeTexture::CubeTexture()
{
	world = new World;
}


CubeTexture::~CubeTexture()
{
}

void CubeTexture::Update()
{
	world->rot.y += TIMER->TimerElapsed();
	world->Update();
}

void CubeTexture::Render()
{
	for (auto texture : cube) {
		texture->Render();
	}
}

void CubeTexture::LoadTexture(wstring fileName)
{
	for(int i = 0; i < 6; i++) {
		cube.push_back(Texture::Add(fileName));
		cube[i]->GetWorld()->parentWorld = &world->matWorld;
		world->children.push_back(cube[i]->GetWorld());
	}

	World* world;
	// Á¤¸é
	world = cube[0]->GetWorld();
	world->pos = { 0, 0, -1 };

	// µÞ¸é
	world = cube[1]->GetWorld();
	world->pos = { 0, 0, 1 };
	world->rot = { 0, D3DX_PI, 0 };

	// ¿À¸¥ÂÊ ¸é
	world = cube[2]->GetWorld();
	world->pos = { 1, 0, 0 };
	world->rot = { 0, -D3DX_PI / 2.f, 0 };

	// ¿ÞÂÊ ¸é
	world = cube[3]->GetWorld();
	world->pos = { -1, 0, 0 };
	world->rot = { 0, D3DX_PI / 2.f, 0 };

	// À­ÂÊ ¸é
	world = cube[4]->GetWorld();
	world->pos = { 0, 1, 0 };
	world->rot = { D3DX_PI / 2.f, 0, 0 };

	// ¾Æ·¡ÂÊ ¸é
	world = cube[5]->GetWorld();
	world->pos = { 0, -1, 0 };
	world->rot = { -D3DX_PI / 2.f, 0, 0 };
}
