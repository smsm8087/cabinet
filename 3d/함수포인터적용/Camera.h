#pragma once
class Camera
{
private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

	Camera();
	~Camera();
public:
	static Camera* GetInstance()
	{
		static Camera instance;
		return &instance;
	}

	void Update();

	void SetProjection();
};

