#include "stdafx.h"
#include "Device.h"


Device::Device()
{
	//�ý����� ������ �ϵ���� ��ġ�� ���� ������ ��� ��ü
	//IDirect3D9* d3d;
	LPDIRECT3D9 d3d;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);
		
	//Device ��ü�� ������ �����ϴµ� �̿�
	D3DPRESENT_PARAMETERS param = {};
	param.Windowed = FALSE;
	param.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//�ø��� ü���� ���۰� ��ȯ�Ǵ� ����� �����ϴ�
	//D3DWSWAPEFFECT������ �ɹ�, 
	//DISCARD�� �����ϴ� ���� ���� ȿ�����̴�
	param.AutoDepthStencilFormat = D3DFMT_D16;
	//����,���ٽ� ������ ����
	param.EnableAutoDepthStencil = TRUE;

	//VSync(Vertical Sycronization) : ��������ȭ ���� fps����Ǯ�������
	param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//�ѱ�
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
		//�Ұ��� ��� ����
		//target : �ĸ����, zbuffer : ���̹���
		0xff555555,
		1.0f,
		0
	);
	device->BeginScene();//������
}

void Device::DrawEnd()
{
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}
