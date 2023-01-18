#pragma once
class SRTTest : public Test
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

	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 translation;

	D3DXVECTOR2 scale2;
	D3DXVECTOR3 rotation2;
	D3DXVECTOR2 translation2;

	D3DXMATRIX world;
	D3DXMATRIX world2;
	D3DXMATRIX projection;
public:
	SRTTest();
	~SRTTest();

	void Update();
	void Render();
};

