#pragma once
class Camera
{
private:
	D3DXMATRIX view;
	D3DXMATRIX projection;


	D3DXVECTOR3 pos;
	D3DXVECTOR3 lookAtPos;
	D3DXVECTOR3 lookAtTargetPos;
	D3DXMATRIX RY;
	D3DXMATRIX RX;
	D3DXVECTOR2 prevMouse;
	float anglex;
	float angley;

	D3DXVECTOR3 resultLookAt;
	D3DXVECTOR3 resultPos;

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

	void SetTarget(D3DXVECTOR3 _lookAt) { lookAtTargetPos = _lookAt; }
};