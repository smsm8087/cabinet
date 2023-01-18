#pragma once
class WVPTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR3 position;
		DWORD color;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vertex() {}
		Vertex(float x, float y, DWORD color)
		{
			position = { x, y, 0 };
			this->color = color;
		}
	};

	Vertex* vertex;

	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 cameraPos;

	D3DXMATRIX world;
	D3DXMATRIX world2;
	D3DXMATRIX view;
	D3DXMATRIX projection;
public:
	WVPTest();
	~WVPTest();

	void Update();
	void Render();
};

