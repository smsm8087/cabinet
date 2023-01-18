#pragma once
class Camera final
{
public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
private:
	Camera();
public:

	virtual ~Camera();

private:
	D3DXVECTOR2 mPos;
	float mfSpeed;
public:
	D3DXVECTOR2 GetCameraPos() { return mPos; }

	void Update();

};

