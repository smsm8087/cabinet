#include "stdafx.h"
#include "ShaderTest.h"


ShaderTest::ShaderTest()
{
	bg = Texture::Add(L"image/test.png");
	sun = Texture::Add(L"image/sun.png");

	//Shader::CreateShader(L"AlphaShader.hlsl", &shader);
	//Shader::CreateShader(L"MultiShader.hlsl", &shader);
	//Shader::CreateShader(L"BlurShader.hlsl", &shader);
	Shader::CreateShader(L"MosaicShader.hlsl", &shader);
	passNum = 0;

	sunWorld = new World;
	sunWorld->scale = {5.f, 5.f };
	sunWorld->pos = { -600, -400 };
	bgWorld = new World;

	//D3DTOP_MODULATE;

	TwBar* bar = UI->GetBar();
	TwAddVarRW(bar, "PassNum", TW_TYPE_UINT32,
		&passNum, "");

	value = 0;
	blurCount = 0;

	TwAddVarRW(bar, "BlurCount", TW_TYPE_UINT32,
		&blurCount, "");

	bg->GetSize(&imageSize);

	color = { 1, 1, 1, 1 };
	TwAddVarRW(bar, "Color", TW_TYPE_COLOR4F, &color, "");
}


ShaderTest::~ShaderTest()
{
}

void ShaderTest::Update()
{
	if (KEYBOARD->KeyPress(VK_RIGHT))
		sunWorld->pos.x += TIMER->TimerElapsed() * 100;
	if (KEYBOARD->KeyPress(VK_LEFT))
		sunWorld->pos.x -= TIMER->TimerElapsed() * 100;

	value += TIMER->TimerElapsed();
	if (value > 1.0f)
		value = 0;

	sunWorld->Update();
}

void ShaderTest::Render()
{
	//bgWorld->SetWorld();
	//bg->Render();
	//shader->SetTexture("map1", sun->GetTexture());
	//shader->SetTexture("map2", bg->GetTexture());
	//shader->SetFloat("value", value);
	//shader->SetFloatArray("imageSize", (float*)&imageSize, 2);
	//shader->SetInt("blurCount", blurCount);
	shader->SetFloat("mosaicSize", blurCount);
	shader->SetFloatArray("color", (float*)&color, 4);
	shader->Begin(NULL, NULL);
	shader->BeginPass(passNum);
	sunWorld->SetWorld();
	//sun->Render();
	bg->Render();
	shader->EndPass();
	shader->End();
}
