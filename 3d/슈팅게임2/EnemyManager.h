#pragma once
#include <vector>
using namespace std;
#include "EnemyClass.h"

class EnemyManager
{
private:
	vector<EnemyClass*> vEnemy;

public:
	EnemyManager();
	EnemyManager(UINT MaxSize);
	~EnemyManager();
	
	void Update(void);
	void Render(void);

	void Remove(UINT i);

	bool isActiveTrue();

public:
	vector<EnemyClass*> GetvEnemy() { return vEnemy; }
};

