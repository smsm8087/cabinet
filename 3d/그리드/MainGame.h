#pragma once
class MainGame
{
private:
	Test * test;
	Grid* grid;
public:
	MainGame();
	~MainGame();

	void Update();
	void Render();	
};

