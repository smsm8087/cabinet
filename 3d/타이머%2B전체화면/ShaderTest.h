#pragma once
class ShaderTest : public Test
{
private:
	Texture * bg;
	Texture * sun;
	Texture * slotmachine;
	Texture * slot[3];
	Texture * slotbottom;

	World*	slotmachinWorld;
	World*  slotWorld;
	World*  slotBottomWorld;

	World* sunWorld;
	World* bgWorld;

	LPD3DXEFFECT shader;
	UINT passNum;

	float PassedTime;
	bool isStop;
public:
	ShaderTest();
	~ShaderTest();

	void Update();
	void Render();

	float value;
	float angle;
};

