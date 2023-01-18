#pragma once
#include <vector>
using namespace std;
#include "BulletClass.h"

class BulletManager
{
private:
	vector<BulletClass*> vBullet;

public:
	BulletManager();
	BulletManager(float Speed, float Radian, UINT MaxSize);
	~BulletManager();

	void Update(void);
	void Render(void);

	void Remove(UINT i);

	bool isFire(float x, float y, float angle);

public:
	vector<BulletClass*> GetvBullet() { return vBullet; }
};

