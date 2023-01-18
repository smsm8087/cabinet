#include "stdafx.h"
#include "ShaderTest.h"


ShaderTest::ShaderTest()
{
	//bg = Texture::Add(L"image/test.png");
	//sun = Texture::Add(L"image/sun.png");

	Shader::CreateShader(L"MultiShader.hlsl", &shader);
	passNum = 0;

	//sunWorld = new World;
	//sunWorld->scale = { 0.3f, 0.3f };
	//sunWorld->pos = { 200, 50 };
	//sunWorld->pivot = { 0.5f,0.5f };

	//bgWorld = new World;

	/*TwBar* bar = UI->GetBar();
	TwAddVarRW(bar, "PassNum", TW_TYPE_UINT32, &passNum, "");*/

	slotmachine = Texture::Add(L"Image/½½·Ô¸Ó½Å.png");
	for (int i = 0; i < 3; i++)
	{
		slot[i] = Texture::Add(L"Image/½½·Ô.png");
	}
	slotbottom = Texture::Add(L"Image/½½·ÔÇÏ´Ü.png");

	slotmachinWorld = new World;
	slotWorld = new World[3];
	RECT rc; GetClientRect(hWnd, &rc);
	slotmachinWorld->pos = { 0,0 };

	for (int i = 0; i < 3; i++)
	{
		slotWorld[i].pos = { (float)(210 + 120 * i),234 };
	}

	slotBottomWorld = new World;
	slotBottomWorld->pos = {210,(600-186)};
	value = 0;
	angle = 0.f;
	PassedTime = 0.f;
	isStop = false;
}


ShaderTest::~ShaderTest()
{
}

void ShaderTest::Update()
{
	if (KEYBOARD->KeyPress('S'))
	{
		isStop = false;
		
	}
	if (KEYBOARD->KeyPress('D'))
	{
		isStop = true;
		//170.7 9°³
	}
	if (!isStop)
	{
		value += TIMER->TimerElapsed();
		if (value > 1.0f)
		{
			value = 0;
		}
	}
	else
	{
		
		
	}
		

	
	//angle += TIMER->TimerElapsed();

	//sunWorld->Update();
	slotmachinWorld->Update();
	for (int i = 0; i < 3; i++)
	{
		slotWorld[i].Update();
	}
	slotBottomWorld->Update();

}

void ShaderTest::Render()
{
	slotmachinWorld->SetWorld();
	slotmachine->Render();

	//shader->SetTexture("map1", slotmachine->GetTexture());
	shader->SetTexture("map1", slot[0]->GetTexture());
	shader->SetFloat("value", value);
	//shader->SetFloat("angle", angle);
	//bgWorld->SetWorld();
	//bg->Render();
	shader->Begin(NULL, NULL);
	shader->BeginPass(passNum);
	//sunWorld->SetWorld();
	//sun->Render();
	
	for (int i = 0; i < 3; i++)
	{
		slotWorld[i].SetWorld();
		slot[i]->Render();
	}
	
	shader->EndPass();
	shader->End();

	slotBottomWorld->SetWorld();
	slotbottom->Render();
	
	
}
