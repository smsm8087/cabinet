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

		//ó�� �� Ű���̴�
		if (result.second)
		{

		}
		//Ű���� �ߺ��Ȱ��� ����
		if (!result.second)
		{
			//auto  a = mActors[key];
			//mActors[key].push_back(temp);
		}
		//mlActors.push_back(
		//	(						//����Ʈ�����ͷ� ����� ���Ϳ� �������
		//		new T(forward<Types>(args)...)	//�����ڿ� ���� �Ķ���Ͱ�
		//	));
		
//		return dynamic_cast<T*>(mlActors.back());
		return dynamic_cast<T*>(temp);

	}

public:
	void Update();
	void Render();
	void Release();
};

