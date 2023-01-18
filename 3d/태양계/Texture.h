#pragma once
class Texture
{
private:
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_TEX1;

		Vertex() {}
		Vertex(float x, float y, float u, float v)
		{
			position = { x, y, 0 };
			uv = { u, v };
		}
	};

	UINT number;
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR2 textureSize;

	D3DXVECTOR2 cutStart;
	D3DXVECTOR2 cutEnd;
	D3DXVECTOR2 uvStart;
	D3DXVECTOR2 uvEnd;

	static LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	static vector<Texture*> textures;
	static map<wstring, LPDIRECT3DTEXTURE9> textureMap;

	Texture(LPDIRECT3DTEXTURE9 texture, 
		D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd);
	~Texture();

	static void CreateVertexBuffer();
public:
	static Texture* Add(wstring fileName,
		D3DXVECTOR2 cutStart = D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2 cutEnd = D3DXVECTOR2(0.0f, 0.0f)
	);

	void Render();

	void GetSize(D3DXVECTOR2* size) { *size = cutEnd - cutStart; }
};

