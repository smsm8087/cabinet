#pragma once
class dungreed : public Test
{
private:
	Player * player;
	Weapon* weapon;
public:
	dungreed();
	~dungreed();

	void Update();
	void Render();
};

