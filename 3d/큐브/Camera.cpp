#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	camera = { 50,50,-50 };
	SetProjection();
}


Camera::~Camera()
{
}

void Camera::Update()
{
	SetView();

	if (KEYBOARD->KeyPress('W'))
	{
		camera.y += 0.2f;
	}
	if (KEYBOARD->KeyPress('S'))
	{
		camera.y -= 0.2f;
	}
	if (KEYBOARD->KeyPress('D'))
	{
		camera.x += 0.2f;
	}
	if (KEYBOARD->KeyPress('A'))
	{
		camera.x -= 0.2f;
	}
	if (KEYBOARD->KeyPress(VK_UP))
	{
		camera.z += 0.2f;
	}
	if (KEYBOARD->KeyPress(VK_DOWN))
	{
		camera.z -= 0.2f;
	}
}

void Camera::SetView()
{

	D3DXMatrixLookAtLH(
		&view,
		&D3DXVECTOR3(camera.x, camera.y, camera.z),//ī�޶��� ��ġ
		&D3DXVECTOR3(0, 0, 0),//ī�޶� ���� ����
		&D3DXVECTOR3(0, 1, 0) //������ �� ����
	);

	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Camera::SetProjection()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	//��������(���̰� ���� ����)
	//D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewport.Width,
		//viewport.Height, 0.0f, -1, 1);

	//��������(���̰� �����ϴ� ������ȯ)
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DX_PI / 4,
		viewport.Width / (float)viewport.Height,//��Ⱦ�� = �ʺ�/����
		1, 1000);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}
