#pragma once
class SolarSystem : public Test
{
private:
	Planet* sun;
	Planet* earth;
	Planet* moon;

public:
	SolarSystem();
	~SolarSystem();

	void Update();
	void Render();
};

