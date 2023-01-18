#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	//test = new PaintTool;
	//test = new WVPTest;	
	//test = new SRTTest;
	test = new TextureTest;
}


MainGame::~MainGame()
{
	delete test;
}

void MainGame::Update()
{
	test->Update();

	CAMERA->Update();
}

void MainGame::Render()
{
	test->Render();
}
