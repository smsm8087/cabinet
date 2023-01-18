#pragma once
class ShaderTest : public Test
{
private:
	Texture * bg;
	Texture * sun;

	World* sunWorld;
	World* bgWorld;

	LPD3DXEFFECT shader;
	UINT passNum;
	UINT blurCount;
	float value;
	D3DXVECTOR2 imageSize;
	D3DXCOLOR color;
public:
	ShaderTest();
	~ShaderTest();

	void Update();
	void Render();
};

