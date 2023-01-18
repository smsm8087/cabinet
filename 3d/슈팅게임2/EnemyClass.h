#pragma once
class EnemyClass
{
	struct Vertex {
		D3DXVECTOR3 position;
		DWORD color;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vertex() {}
		Vertex(float x, float y, DWORD color) {
			position = { x,y,0 };
			this->color = color;
		}
	};

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	Vertex* vertex;
	UINT vertexCount;

	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 viewPos;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	bool upMove;

	bool isActive;

public:
	EnemyClass();
	~EnemyClass();

	void Update();
	void Render();


public:
	float GetLeft() { return worldPos.x; }
	float GetRight() { return worldPos.x + 50; }
	float GetTop() { return worldPos.y; }
	float GetBottom() { return worldPos.y + 50; }

	void isActiveTrue(float _x, float _y);
	bool GetisActive(void) { return isActive; }
	void SetisActive(bool active) { isActive = active; }
};

