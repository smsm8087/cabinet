#include "stdafx.h"
#include "DeviceModule.h"


DeviceModule::DeviceModule()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS param = { 0 };
	param.Windowed = TRUE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	param.AutoDepthStencilFormat = D3DFMT_D16;
	param.EnableAutoDepthStencil = TRUE;
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&param,
		&device
	);
}


DeviceModule::~DeviceModule()
{
}

void DeviceModule::BeginDraw()
{
	device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xfffffff5,
		1.0f,
		0
	);

	device->BeginScene();
}

void DeviceModule::EndDraw()
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}