#pragma once
class Planet
{
private:
	Texture * texture;
	World* world;

	float rotSpeed;

	Vertex* vertex;

	vector<Vertex> cube;

	LPDIRECT3DTEXTURE9	texture9;
	//D3DXMATRIX matWorld;
	//D3DXMATRIX matScale;
	//D3DXMATRIX matRotate;
	//D3DXMATRIX matTrans;c

public:
	Planet(wstring fileName);
	~Planet();

	void Update();
	void Render();

	void SetRotSpeed(float speed) { rotSpeed = speed; }
	World* GetWorld() { return world; }
};

