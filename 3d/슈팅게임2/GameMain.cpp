#include "stdafx.h"
#include "GameMain.h"


GameMain::GameMain()
{
	player = new PlayerClass;
	enemy = new EnemyManager(10);
	isGameover = false;
	CurrentTime = 0;
}


GameMain::~GameMain()
{
	delete player;
	delete enemy;

	_DeviceInstance->ReleaseSingleton();
	_KEY->ReleaseSingleton();
}


void GameMain::Update()
{
	CurrentTime++;
	if (CurrentTime % 30 == 0) {
		CurrentTime = 0;
		enemy->isActiveTrue();
	}
	if(isGameover) return;
	player->Update();
	enemy->Update();
	isCollision();
}

void GameMain::Render()
{
	player->Render();
	enemy->Render();
}
