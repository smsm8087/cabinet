#include "stdafx.h"
#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	sun = new Planet(L"image/sun.png");
	sun->GetWorld()->scale *= 0.015f;
	earth = new Planet(L"image/earth.png");
	earth->GetWorld()->parentWorld = &sun->GetWorld()->matWorld;
	earth->GetWorld()->pos.x -= 3000;
	earth->GetWorld()->scale *= 0.4f;
	
	moon = new Planet(L"image/moon.png");
	moon->GetWorld()->parentWorld = &earth->GetWorld()->matWorld;
	moon->GetWorld()->pos.x -= 3000;
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
