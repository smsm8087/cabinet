#include "stdafx.h"
#include "Device.h"


Device::Device()
{
	//시스템의 물리적 하드웨어 장치에 대한 정보를 얻는 객체
	//IDirect3D9* d3d;
	LPDIRECT3D9 d3d;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
		
	//Device 객체의 성격을 결정하는데 이용
	D3DPRESENT_PARAMETERS param = {};
	param.Windowed = FALSE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//플리핑 체인의 버퍼가 교환되는 방법을 지정하는
	//D3DWSWAPEFFECT열거형 맴버, 
	//DISCARD를 지정하는 것이 가장 효과적이다
	param.AutoDepthStencilFormat = D3DFMT_D16;
	//깊이,스텐실 버퍼의 포멧
	param.EnableAutoDepthStencil = TRUE;

	//VSync(Vertical Sycronization) : 수직동기화 끄기 fps제한풀어버리기
	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//켜기
	//param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	D3DDISPLAYMODE mode;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);

	param.BackBufferWidth = mode.Width;
	param.BackBufferHeight = mode.Height;
	param.BackBufferFormat = mode.Format;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&param,
		&device
	);

	d3d->Release();
}


Device::~Device()
{
	device->Release();
}

Device * Device::GetInstance()
{
	//if (instance == NULL)
		//instance = new Device;
	static Device instance;
	
	return &instance;
}

void Device::DrawBegin()
{
	device->Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//소거할 대상 지정
		//target : 후면버퍼, zbuffer : 깊이버퍼
		0xff555555,
		1.0f,
		0
	);
	device->BeginScene();//장면시작
}

void Device::DrawEnd()
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}
