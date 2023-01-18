#include "stdafx.h"
#include "ActorMgr.h"
#include "Enemy.h"

ActorMgr::ActorMgr()
{
	//list<Actor*> t;
	//mActors.insert(pair<int, list<Actor*>>(1, t));
	//map<int, int> tmap;
	//auto result = tmap.insert(make_pair<int, int>(0, 0));
	//result = tmap.insert(make_pair<int, int>(0, 1));
	//result = tmap.insert(make_pair<int, int>(0, 2));
	//tmap.insert(pair<int, int>(1, 1));
	//tmap.insert(pair<int, int>(2, 2));
	//tmap.insert(pair<int, int>(3, 3));


}


ActorMgr::~ActorMgr()
{
	//등록된 엑터들 삭제
	for (auto mapiter = mActors.begin(); mapiter != mActors.end(); mapiter++)
	{
		
		for (auto listiter = (*mapiter).second.begin(); listiter != (*mapiter).second.end(); )//listiter++
		{
			delete (*listiter);
			listiter =mActors[(*mapiter).first].erase(listiter);
		}
		
	}
}

void ActorMgr::Update()
{
	for (auto mapiter = mActors.begin(); mapiter != mActors.end(); mapiter++)
	{

		for (auto listiter = (*mapiter).second.begin(); listiter != (*mapiter).second.end(); listiter++)
		{
			(*listiter)->Update();
		}

	}

	//충돌 처리
	for (auto enemyiter = mActors[CTYPE_ENEMY].begin(); enemyiter != mActors[CTYPE_ENEMY].end(); enemyiter++)
	{
		for (auto bulletiter = mActors[CTYPE_BULLET].begin(); bulletiter != mActors[CTYPE_BULLET].end(); bulletiter++)
		{
			RECT crc, crc1, crc2;

			crc1 = RectMakeCenter((*enemyiter)->GetPos().x, (*enemyiter)->GetPos().y, 100, 100);
			crc2 = RectMakeCenter((*bulletiter)->GetPos().x, (*bulletiter)->GetPos().y, 10, 10);

			if (IntersectRect(&crc, &crc1, &crc2))
			{
				auto enemy =((Enemy*)(*enemyiter));
				enemy->SetHp(enemy->GetHp()-1);
				(*bulletiter)->SetDestroy(true);
			}
		}
	}

	//객체삭제
	for (auto mapiter = mActors.begin(); mapiter != mActors.end(); mapiter++)
	{
		for (auto listiter = (*mapiter).second.begin(); listiter != (*mapiter).second.end();)
		{
			if ((*listiter)->GetDestroy())
			{
				delete (*listiter);
				listiter = mActors[(*mapiter).first].erase(listiter);
			}
			else
			{
				listiter++;
			}
		}
	}
}

void ActorMgr::Render()
{
	for (auto mapiter = mActors.begin(); mapiter != mActors.end(); mapiter++)
	{

		for (auto listiter = (*mapiter).second.begin(); listiter != (*mapiter).second.end(); listiter++)
		{
			(*listiter)->Render();
		}

	}
}

void ActorMgr::Release()
{
}
