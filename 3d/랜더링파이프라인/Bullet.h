#pragma once
class Bullet : public Test
{
private:

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

	Vertex* vertex;
	D3DXVECTOR2 viewPos;

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;

	RECT  rc;
	float fSpeed;
	bool isActive;
public:
	Bullet();
	~Bullet();

	void Update(void);
	void Render(void);
	void Fire(float _x, float _y, float _angle);
	RECT GetBulletRc() { return rc; }

};

