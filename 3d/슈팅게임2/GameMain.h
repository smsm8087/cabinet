#pragma once


class GameMain
{
private:
	PlayerClass * player;
	EnemyManager* enemy;
	bool isGameover;
	int CurrentTime;
public:
	GameMain();
	~GameMain();

	void Update();
	void Render();
	void isCollision();
};

