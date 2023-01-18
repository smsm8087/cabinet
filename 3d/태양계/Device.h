#pragma once
class Device
{
private:
	LPDIRECT3DDEVICE9 device;
	
	//static Device* instance;

	Device();
	~Device();
public:
	static Device* GetInstance();
	
	LPDIRECT3DDEVICE9 GetDevice() { return device; }

	void DrawBegin();
	void DrawEnd();
};

