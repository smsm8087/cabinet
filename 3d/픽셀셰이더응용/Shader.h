#pragma once
class Shader
{
public:
	Shader();
	~Shader();

	static void CreateShader(wstring fileName,
		LPD3DXEFFECT* shader);
};

