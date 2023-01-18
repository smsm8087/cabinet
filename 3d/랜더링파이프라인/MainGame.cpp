#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	/*player = new Player;	
	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy;
		vecEnemy.push_back(enemy);
	}
	m_fpassed = 0.f;*/
	pSun = new Sun;
	g_pTimeManager->Init();

}


MainGame::~MainGame()
{
	/*delete player;
	for (auto p : vecEnemy)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}*/
	SAFE_DELETE(pSun);
}

void MainGame::Update()
{
	g_pTimeManager->Update();
	pSun->Update();
}

void MainGame::Render()
{
	pSun->Render();
}	