#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Enemy.h"

MainGame::MainGame()
{
	srand((unsigned int)time(0));
	//test = new PaintTool;
	//test = new WVPTest;	
	//WVPTest* a = ActorMgr::Instance().Create<WVPTest>(CTYPE_PLAYER);
	//WVPTest* b = ActorMgr::Instance().Create<WVPTest>(CTYPE_PLAYER);
	mpPlayer = ActorMgr::Instance().Create<Player>(CTYPE_PLAYER);
	mpPlayer->Init();
	mpEnemy = ActorMgr::Instance().Create<Enemy>(CTYPE_ENEMY);
	mpEnemy->Init();
	//MActorManager::Instance().Create<World>
		//(spriteBatch, spriteFont, mScreenWidth, mScreenHeight);

}


MainGame::~MainGame()
{
	delete test;
}

void MainGame::Update()
{
	Camera::Instance().Update();
	ActorMgr::Instance().Update();
	//test->Update();
}

void MainGame::Render()
{
	ActorMgr::Instance().Render();

	//test->Render();
}
