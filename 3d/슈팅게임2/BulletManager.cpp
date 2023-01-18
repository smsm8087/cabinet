#include "stdafx.h"
#include "BulletManager.h"

BulletManager::BulletManager()
{
}

BulletManager::BulletManager(float Speed, float Radian, UINT MaxSize)
{
	for (UINT i = 0; i < MaxSize; ++i) {
		BulletClass* Temp = new BulletClass(Speed, Radian);
		Temp->SetisActive(false);
		vBullet.push_back(Temp);
	}
}

BulletManager::~BulletManager()
{
	for (UINT i = 0; i < vBullet.size(); ++i) {
		SafeDelete(vBullet[i]);
	}
}

void BulletManager::Update(void)
{
	for (UINT i = 0; i < vBullet.size(); ++i)
		vBullet[i]->Update();
}

void BulletManager::Render(void)
{
	for (UINT i = 0; i < vBullet.size(); ++i)
		vBullet[i]->Render();
}

void BulletManager::Remove(UINT i)
{
	vBullet[i]->SetisActive(false);
}

bool BulletManager::isFire(float x, float y, float angle)
{
	for (UINT i = 0; i < vBullet.size(); ++i) {
		if (vBullet[i]->GetisActive()) continue;

		vBullet[i]->isFire(x, y, angle);
		return true;
	}

	return false;
}