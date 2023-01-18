#pragma once
class Solar3DTest : public Test
{
private:
	CubeTexture * sun;
	CubeTexture* earth;
	CubeTexture* moon;

	enum Target
	{
		E_SUN,
		E_EARTH,
		E_MOON
	};
	Target target;
public:
	Solar3DTest();
	~Solar3DTest();

	void Update();
	void Render();

	CubeTexture* GetSunCube() { return sun; }
	CubeTexture* GetEarthCube() { return earth; }
	CubeTexture* GetMoonCube() { return moon; }
};

