#pragma once
class Player;
class Enemy;
class Bullet;

class MainGame
{
private:
	Test * test;
	Player * mpPlayer;
	Enemy* mpEnemy;
public:
	MainGame();
	~MainGame();

	void Update();
	void Render();	
};

