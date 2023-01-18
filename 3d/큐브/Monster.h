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

	LPD3DXEFFECT shader;
	D3DXCOLOR color;
	float colorValue;
public:
	Monster();
	~Monster();

	void Update();
	void Render();

	void LoadXml();
	void SetIdle();
};

