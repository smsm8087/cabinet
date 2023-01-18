#include "stdafx.h"
#include "GameMain.h"

void GameMain::isCollision() {
	
	for (UINT i = 0; i < player->GetmBullet()->GetvBullet().size(); i++) {
		for (UINT j = 0;j < enemy->GetvEnemy().size();j++) {
			if (enemy->GetvEnemy()[j]->GetTop() < player->GetmBullet()->GetvBullet()[i]->GetY() &&
				enemy->GetvEnemy()[j]->GetBottom() > player->GetmBullet()->GetvBullet()[i]->GetY() &&
				enemy->GetvEnemy()[j]->GetRight() > player->GetmBullet()->GetvBullet()[i]->GetLeft() &&
				enemy->GetvEnemy()[j]->GetLeft() < player->GetmBullet()->GetvBullet()[i]->GetRight() &&
				player->GetmBullet()->GetvBullet()[i]->GetisActive()) {

				enemy->Remove(j);
				player->GetmBullet()->Remove(i);
				return;
			}
		}
	}
}