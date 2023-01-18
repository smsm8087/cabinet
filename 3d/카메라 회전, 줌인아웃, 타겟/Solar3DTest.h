#pragma once
class Solar3DTest : public Test
{
private:
	CubeTexture* sun;
	CubeTexture* earth;
	CubeTexture* moon;

public:
	Solar3DTest();
	~Solar3DTest();

	void Update();
	void Render();
};

