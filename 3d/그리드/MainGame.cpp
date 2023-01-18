#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	grid = new Grid;
	//test = new PaintTool;
	//test = new WVPTest;	
	//test = new SRTTest;
	//test = new TextureTest;
	//test = new SolarSystem;
	//test = new XmlTest;
	//test = new ShaderTest;
	//test = new CubeTest;
	test = new Solar3DTest;
}


MainGame::~MainGame()
{
	delete grid;
	delete test;
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
