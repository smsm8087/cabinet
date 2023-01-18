#pragma once
class MainGame
{
private:
	//Test * player;
	//vector<Enemy*> vecEnemy;
	//vector<Bullet*> vecBullet;
	Sun *pSun;

	float		m_fpassed;
public:
	MainGame();
	~MainGame();

	void Update();
	void Render();	
};

