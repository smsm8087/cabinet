#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	//test = new PaintTool;
	//test = new WVPTest;	
	//test = new SRTTest;
	//test = new TextureTest;
	//test = new SolarSystem;
	//test = new XmlTest;
	//test = new ShaderTest;
	test = new Solar3DTest;
	grid = new Grid;
}


MainGame::~MainGame()
{
	delete test;
	delete grid;
	Texture::Release();
}

void MainGame::Update()
{
	test->Update();

	CAMERA->Update();
}

void MainGame::Render()
{
	grid->Render();
	test->Render();
}
