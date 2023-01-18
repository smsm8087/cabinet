#include "stdafx.h"
#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	sun = new Planet(L"image/sun.png");
	sun->SetRotSpeed(0.01f);
	sun->GetWorld()->scale *= 0.3f;

	earth = new Planet(L"image/earth.png");
	earth->SetRotSpeed(0.05f);
	earth->GetWorld()->parentWorld = &sun->GetWorld()->matWorld;
	earth->GetWorld()->pos.x -= 1000;
	earth->GetWorld()->scale *= 0.3f;

	moon = new Planet(L"image/moon.png");
	moon->SetRotSpeed(0.05f);
	moon->GetWorld()->parentWorld = &earth->GetWorld()->matWorld;
	moon->GetWorld()->pos.x -= 500;
}


SolarSystem::~SolarSystem()
{
}

void SolarSystem::Update()
{
	sun->Update();
	earth->Update();
	moon->Update();
}

void SolarSystem::Render()
{
	sun->Render();
	earth->Render();
	moon->Render();
}
