#pragma once
class Texture;
class Sun : public Test
{
private:

	/*struct Vertex
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
	};*/
	Texture* Sunimage;
	Texture* Earthimage;
	Texture * Moonimage;


	Vertex* Sunvertex;
	Vertex* Earthvertex;
	Vertex* Moonvertex;

	LPDIRECT3DTEXTURE9 Suntexture;
	LPDIRECT3DTEXTURE9 Earthtexture;
	LPDIRECT3DTEXTURE9 Moontexture;

	D3DXMATRIX Sunworld;
	D3DXVECTOR2 Sunworldpos;
	D3DXVECTOR2 Sunpivot;
	D3DXVECTOR3 Sunrotation;
	

	D3DXMATRIX Earthworld;
	D3DXVECTOR2 Earthworldpos;
	D3DXVECTOR2 Earthpivot;
	D3DXVECTOR3 Earthrotation;

	D3DXMATRIX view;
	D3DXMATRIX projection;


	D3DXMATRIX Moonworld;
	D3DXVECTOR2 Moonworldpos;
	D3DXVECTOR2 Moonpivot;
	D3DXVECTOR3 Moonrotation;


public:
	Sun();
	~Sun();

	void Update();
	void Render();
};

