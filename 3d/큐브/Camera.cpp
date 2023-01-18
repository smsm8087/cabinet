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
		&D3DXVECTOR3(camera.x, camera.y, camera.z),//카메라의 위치
		&D3DXVECTOR3(0, 0, 0),//카메라가 보는 지점
		&D3DXVECTOR3(0, 1, 0) //월드의 업 벡터
	);

	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Camera::SetProjection()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	//직교투영(깊이가 없는 투영)
	//D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewport.Width,
		//viewport.Height, 0.0f, -1, 1);

	//원근투영(깊이가 존재하는 투영변환)
	D3DXMatrixPerspectiveFovLH(
		&projection,
		D3DX_PI / 4,
		viewport.Width / (float)viewport.Height,//종횡비 = 너비/높이
		1, 1000);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}
