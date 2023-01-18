#include "stdafx.h"
#include "ShaderTest.h"


ShaderTest::ShaderTest()
{
	bg = Texture::Add(L"image/test.png");
	sun = Texture::Add(L"image/sun.png");

	Shader::CreateShader(L"AlphaShader.hlsl", &shader);
	passNum = 0;

	sunWorld = new World;
	sunWorld->scale = { 0.3f,0.3f };
	sunWorld->pos = { 350,125 };

	bgWorld = new World;

	bgWorld->pos = { 100,100 };
}


ShaderTest::~ShaderTest()
{
}

void ShaderTest::Update()
{
	if (KEYBOARD->KeyDown(VK_RIGHT))
		passNum++;
	if (KEYBOARD->KeyDown(VK_LEFT))
		passNum--;

	bgWorld->Update();
	sunWorld->Update();
}

void ShaderTest::Render()
{
	bgWorld->SetWorld();
	bg->Render();
	shader->Begin(NULL, NULL);
	shader->BeginPass(passNum);
	sunWorld->SetWorld();
	sun->Render();
	shader->EndPass();
	shader->End();
}
