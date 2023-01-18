#pragma once
class Planet
{
private:
	Texture * texture;
	World* world;

	float rotSpeed;

public:
	Planet(wstring fileName);
	~Planet();

	void Update();
	void Render();

	void SetRotSpeed(float speed) { rotSpeed = speed; }
	World* GetWorld() { return world; }
};

