#pragma once
#include "WVPTest.h"
class ActorMgr final
{
public:
	static ActorMgr& Instance()
	{
		static ActorMgr instance;
		return instance;
	}
private:
	ActorMgr();
public:
	~ActorMgr();

private:
	map<int, list<Actor*>> mActors;
	list<Actor*> mlActors;

public:
	template<class T, class...Types> inline
		T* Create(int key)
	{
		list<Actor*> templist;

		auto result = mActors.insert(pair<int, list<Actor*>>(key,
			templist));
		T* temp = new T();
		mActors[key].push_back(temp);

		//처음 들어간 키값이다
		if (result.second)
		{

		}
		//키값이 중복된값이 들어갔다
		if (!result.second)
		{
			//auto  a = mActors[key];
			//mActors[key].push_back(temp);
		}
		//mlActors.push_back(
		//	(						//스마트포인터로 만들고 엑터에 집어넣음
		//		new T(forward<Types>(args)...)	//생성자에 들어가는 파라미터값
		//	));
		
//		return dynamic_cast<T*>(mlActors.back());
		return dynamic_cast<T*>(temp);

	}

public:
	void Update();
	void Render();
	void Release();
};

