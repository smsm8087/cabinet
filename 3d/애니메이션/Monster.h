#pragma once
class Monster
{
private:
	enum AniState
	{
		IDLE,
		RUN,
		ATTACK
	}state;
	
	vector<Animator*> actions;
	World* world;
public:
	Monster();
	~Monster();

	void Update();
	void Render();

	void LoadXml();
};

