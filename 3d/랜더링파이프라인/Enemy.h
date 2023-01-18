#pragma once
class Enemy : public Test
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

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	RECT rc;

	int			upNum;
	int			downNum;
	bool		isUpMoving;

public:
	Enemy();
	~Enemy();

	void Update();
	void Render();

	RECT GetRect() {
		SetRect(&rc, worldPos.x, worldPos.y - 100, worldPos.x + 100, worldPos.y);
		return rc;
	}
};

