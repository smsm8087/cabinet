#pragma once
class Shader
{
public:
	Shader();
	~Shader();

	static void CreateShader(wstring _fileName, LPD3DXEFFECT* shader);
};

