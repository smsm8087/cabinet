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

	

	// Test��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

};

