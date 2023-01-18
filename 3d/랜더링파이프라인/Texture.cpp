#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
}

Texture::Texture(wstring  _imageName,Vertex* _vertex, LPDIRECT3DTEXTURE9 _texture)
{
	vertex = _vertex;
	texture = _texture;
	D3DXCreateTextureFromFile(DEVICE, _imageName.c_str(), &texture);
}


Texture::~Texture()
{
	delete[] vertex;
	SAFE_DELETE(texture);
}

void Texture::Update()
{
}

void Texture::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTexture(0, texture);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2,
		vertex, sizeof(Vertex));
}
