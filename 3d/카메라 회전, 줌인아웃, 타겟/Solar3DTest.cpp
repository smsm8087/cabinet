#include "stdafx.h"
#include "Solar3DTest.h"


Solar3DTest::Solar3DTest()
{
	sun = new CubeTexture;
	sun->LoadTexture(L"image/sun.png");
	sun->GetWorld()->rot.z = 0.2f;
	sun->GetWorld()->scale = { 2, 2, 2 };
		
	earth = new CubeTexture;
	earth->LoadTexture(L"image/earth.png");
	earth->GetWorld()->pos.x = 10;
	earth->GetWorld()->parentWorld = &sun->GetWorld()->matWorld;
	earth->GetWorld()->parentSWorld = &sun->GetWorld()->S;
	earth->GetWorld()->rot.z = 0.3f;

	moon = new CubeTexture;
	moon->LoadTexture(L"image/moon.png");
	moon->GetWorld()->pos.x = 5;
	moon->GetWorld()->parentWorld = &earth->GetWorld()->matWorld;

	CAMERA->AddTarget(sun->GetWorld());
	CAMERA->AddTarget(earth->GetWorld());
	CAMERA->AddTarget(moon->GetWorld());
}


Solar3DTest::~Solar3DTest()
{
}

void Solar3DTest::Update()
{
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
