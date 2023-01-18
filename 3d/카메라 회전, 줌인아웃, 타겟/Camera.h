#pragma once
class Camera
{
private:
	D3DXMATRIX view;
	D3DXMATRIX projection;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 lookAtPos;
	D3DXVECTOR3 resultPos;
	D3DXVECTOR3 resultLookAtPos;

	D3DXVECTOR3 rot;

	D3DXVECTOR2 lastMousePos;

	int targetIndex;
	vector<World*> targetWorlds;

	Camera();
	~Camera();
public:
	static Camera* GetInstance()
	{
		static Camera instance;
		return &instance;
	}

	void Update();

	void SetView();
	void SetProjection();

	void MouseControl();
	void CameraRotation();
	void AddTarget(World* targetWorld);
	void SetTarget();
};

