#include "stdafx.h"
#include "Solar3DTest.h"


Solar3DTest::Solar3DTest()
{
	sun = new CubeTexture;
	sun->LoadTexture(L"image/sun.png");
	sun->GetWorld()->rot.x = 0.3f;
	sun->GetWorld()->scale = { 2, 2, 2 };

	earth = new CubeTexture;
	earth->LoadTexture(L"image/earth.png");	
	earth->GetWorld()->pos.x = 10;
	earth->GetWorld()->parentWorld = &sun->GetWorld()->matWorld;
	earth->GetWorld()->parentSWorld = &sun->GetWorld()->S;
	earth->GetWorld()->rot.x = 0.5f;
	//sun->GetWorld()->children.push_back(earth->GetWorld());

	moon = new CubeTexture;
	moon->LoadTexture(L"image/moon.png");
	moon->GetWorld()->pos.x = 5;
	moon->GetWorld()->parentWorld = &earth->GetWorld()->matWorld;
	target = E_SUN;
}


Solar3DTest::~Solar3DTest()
{
}

void Solar3DTest::Update()
{

	if (KEYBOARD->KeyDown('1'))
	{
		target = E_SUN;
	}
	if (KEYBOARD->KeyDown('2'))
	{
		target = E_EARTH;
	}
	if (KEYBOARD->KeyDown('3'))
	{
		target = E_MOON;
	}

	switch (target)
	{
	case Solar3DTest::E_SUN:
		CAMERA->SetTarget(sun->GetWorld()->GetWorldPos());
		break;
	case Solar3DTest::E_EARTH:
		CAMERA->SetTarget(earth->GetWorld()->GetWorldPos());
		break;
	case Solar3DTest::E_MOON:
		CAMERA->SetTarget(moon->GetWorld()->GetWorldPos());
		break;
	default:
		break;
	}
	sun->Update();
	earth->Update();
	moon->Update();
}

void Solar3DTest::Render()
{
	sun->Render();
	earth->Render();
	moon->Render();
}
