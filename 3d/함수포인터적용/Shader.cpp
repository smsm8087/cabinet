#include "stdafx.h"
#include "Shader.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::CreateShader(wstring _fileName, LPD3DXEFFECT * shader)
{
	HRESULT result = 
		D3DXCreateEffectFromFile(DEVICE, _fileName.c_str(), NULL, NULL, D3DXSHADER_DEBUG, NULL, shader, NULL);
	assert(SUCCEEDED(result));
}
