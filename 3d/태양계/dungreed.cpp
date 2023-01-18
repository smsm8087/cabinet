#include "stdafx.h"
#include "dungreed.h"


dungreed::dungreed()
{
	player = new Player;
	player->world->pos = { 500,300 };
	weapon = new Weapon(player->GetPivot());
	weapon->world->pos = { 500,300 };

}


dungreed::~dungreed()
{
	SAFE_DELETE(player);
	SAFE_DELETE(weapon);
}

void dungreed::Update()
{
	player->Update();
	weapon->Update();

	if (KEYBOARD->keyPress('A'))
	{
		player->world->pos.x-=3;
		weapon->world->pos.x-=3;
	}
	if (KEYBOARD->keyPress('D'))
	{
		player->world->pos.x+=3;
		weapon->world->pos.x+=3;
	}
}

void dungreed::Render()
{
	player->Render();
	weapon->Render();
}
