#include "stdafx.h"
#include "EnemyManager.h"
#include <time.h>

EnemyManager::EnemyManager()
{
}

EnemyManager::EnemyManager(UINT MaxSize)
{
	for (UINT i = 0; i < MaxSize; i++) {
		EnemyClass* temp = new EnemyClass();
		temp->SetisActive(false);
		vEnemy.push_back(temp);
	}
	srand(time(NULL));
}


EnemyManager::~EnemyManager()
{
	for (UINT i = 0; i < vEnemy.size(); i++) {
		SafeDelete(vEnemy[i]);
	}
}

void EnemyManager::Update(void)
{
	for (UINT i = 0; i < vEnemy.size(); i++)
		vEnemy[i]->Update();
}

void EnemyManager::Render(void)
{
	for (UINT i = 0; i < vEnemy.size(); i++)
		vEnemy[i]->Render();
}

void EnemyManager::Remove(UINT i)
{
	vEnemy[i]->SetisActive(false);
}

bool EnemyManager::isActiveTrue()
{
	float randX = rand() % 1400;
	float randY = rand() % 650;
	for (UINT i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy[i]->GetisActive()) continue;

		vEnemy[i]->isActiveTrue(randX, randY);
		return true;
	}
	return false;
}
