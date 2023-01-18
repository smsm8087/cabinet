#include "stdafx.h"
#include "Texture.h"

LPDIRECT3DVERTEXBUFFER9 Texture::vertexBuffer = NULL;
vector<Texture*> Texture::textures;
map<wstring, LPDIRECT3DTEXTURE9> Texture::textureMap;



Texture::Texture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd)
{
	this->texture = texture;
	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	textureSize.x = (float)desc.Width;
	textureSize.y = (float)desc.Height;

	uvStart.x = cutStart.x / textureSize.x;
	uvStart.y = cutStart.y / textureSize.y;
	uvEnd.x = (cutEnd.x > 0) ? cutEnd.x / textureSize.x : 1.0f;
	uvEnd.y = (cutEnd.y > 0) ? cutEnd.y / textureSize.y : 1.0f;

	this->cutStart = cutStart;

	this->cutEnd.x = (cutEnd.x < 1) ? textureSize.x : cutEnd.x;
	this->cutEnd.y = (cutEnd.y < 1) ? textureSize.y : cutEnd.y;

	world = new World;
}

Texture::~Texture()
{
	
}

void Texture::CreateVertexBuffer()
{
	SAFE_RELEASE(vertexBuffer);

	UINT vertexCount = textures.size() * 6;
	UINT vertexSize = vertexCount * sizeof(Vertex);

	DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	Vertex* vertex = new Vertex[vertexCount];	
	for (size_t i = 0; i < textures.size(); i++)
	{
		D3DXVECTOR2 size = { 1, 1 };
		// textures[i]->GetSize(&size);

		D3DXVECTOR2 start = textures[i]->uvStart;
		D3DXVECTOR2 end = textures[i]->uvEnd;

		vertex[i * 6 + 0] = Vertex(-size.x, size.y, start.x, start.y);
		vertex[i * 6 + 1] = Vertex(size.x, size.y, end.x, start.y);
		vertex[i * 6 + 2] = Vertex(-size.x, -size.y, start.x, end.y);
		vertex[i * 6 + 3] = Vertex(-size.x, -size.y, start.x, end.y);
		vertex[i * 6 + 4] = Vertex(size.x, size.y, end.x, start.y);
		vertex[i * 6 + 5] = Vertex(size.x, -size.y, end.x, end.y);
	}

	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();

	SAFE_DELETE_ARRAY(vertex);
}

Texture * Texture::Add(wstring fileName, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd)
{
	LPDIRECT3DTEXTURE9 dxTexture;
	if (textureMap.count(fileName) < 1)
	{
		D3DXCreateTextureFromFileEx(
			DEVICE,
			fileName.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			0xffff00ff,
			NULL,
			NULL,
			&dxTexture
		);

		textureMap.insert({ fileName, dxTexture });
		//textureMap[fileName] = dxTexture;
	}
	else
	{
		dxTexture = textureMap[fileName];
	}

	Texture* texture = new Texture(dxTexture, cutStart, cutEnd);
	texture->number = textures.size();

	textures.push_back(texture);

	CreateVertexBuffer();

	return texture;
}

void Texture::Release()
{
	SAFE_RELEASE(vertexBuffer);

	for (auto iter : textures)
	{
		SAFE_DELETE(iter);
	}
	for (auto iter : textureMap)
	{
		SAFE_RELEASE(iter.second);
	}
}

void Texture::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);
	world->SetWorld();
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));

	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, number * 6, 2);
}
