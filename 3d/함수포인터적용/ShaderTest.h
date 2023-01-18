#pragma once
class ShaderTest : public Test
{
private:
	Texture* bg;
	Texture* sun;

	World*   sunWorld;
	World*   bgWorld;

	LPD3DXEFFECT shader;
	UINT passNum;
public:
	ShaderTest();
	~ShaderTest();

	

	// Test을(를) 통해 상속됨
	virtual void Update() override;

	virtual void Render() override;

};

