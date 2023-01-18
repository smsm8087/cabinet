#pragma once
#include "SingletonBase.h"

/*DWORD VertexTest::Vertex::fvf
= D3DFVF_XYZRHW | D3DFVF_DIFFUSE;*/


class DeviceModule : public SingletonBase<DeviceModule>
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 device;

public:
	DeviceModule();
	~DeviceModule();

	void BeginDraw();
	void EndDraw();

	LPDIRECT3DDEVICE9 GetDevice() { return device; }

};

