#pragma once
class SolarSystem : public Test
{
private:
	Texture* texture;
	World*  backWorld;
	Planet* sun;
	Planet* earth;
	Planet* moon;

public:
	SolarSystem();
	~SolarSystem();

	void Update();
	void Render();
};

