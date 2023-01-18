#pragma once
class WVPTest : public Actor
{
private:
	Vertex* vertex;
	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 worldPos2;
	D3DXVECTOR2 cameraPos;

	D3DXMATRIX world;
	D3DXMATRIX world2;
	D3DXMATRIX view;
	D3DXMATRIX view2;
	D3DXMATRIX projection;

	float mfAngle;
public:
	WVPTest();
	virtual ~WVPTest();

	void Update();
	void Render();
};

