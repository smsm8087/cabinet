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
	test = new ShaderTest;
}


MainGame::~MainGame()
{
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
	test->Render();
}
