#pragma once
class BulletClass
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

	float fSpeed;
	float fRadian;
	float angle;
	bool isActive;


public:
	BulletClass();
	BulletClass(float speed, float radian);
	~BulletClass();

	void Update(void);
	void Render(void);

public:
	void isFire(float _x, float _y, float _angle);
	bool GetisActive(void) { return isActive; }
	void SetisActive(bool active) { isActive = active; }

	float GetLeft() { return worldPos.x; }
	float GetRight() { return worldPos.x + 20; }
	float GetY() { return worldPos.y; }
};

