#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	pos = { 0, 10, 20 };
	anglex = 0.f;
	angley = 0.f;
	lookAtPos = { 0,0,0 };
	lookAtTargetPos = { 0,0,0 };
	SetProjection();
}


Camera::~Camera()
{
}

void Camera::Update()
{

	D3DXVECTOR3 tempY;
	tempY = pos;



	D3DXMatrixRotationX(&RX, angley);
	D3DXMatrixRotationY(&RY, anglex);
	D3DXMATRIX R = RX * RY;
	D3DXVec3TransformCoord(&pos, &tempY, &R);



	MouseControl();

	D3DXVECTOR2 temp;
	D3DXVec2Normalize(&temp, &(mousePos - prevMouse));

	if (KEYBOARD->KeyDown(VK_RBUTTON))
	{
		prevMouse = mousePos;
	}
	if (KEYBOARD->KeyPress(VK_RBUTTON))
	{
		anglex = TIMER->TimerElapsed() * temp.x*2.f;
	}

	if (KEYBOARD->KeyUp(VK_RBUTTON))
	{
		prevMouse = mousePos;
		anglex = 0.f;
	}

	if (KEYBOARD->KeyDown(VK_LBUTTON))
	{
		prevMouse = mousePos;
	}
	if (KEYBOARD->KeyPress(VK_LBUTTON))
	{
		if (angley<D3DX_PI*0.25f && angley > -D3DX_PI * 0.25f)
		{
			angley = TIMER->TimerElapsed() * temp.y*2.f;
		}
	}

	if (KEYBOARD->KeyUp(VK_LBUTTON))
	{
		prevMouse = mousePos;
		angley = 0.f;
	}
	resultLookAt = lookAtPos + lookAtTargetPos;
	resultPos = lookAtPos + pos;

	SetView();

}

void Camera::SetView()
{
	D3DXMatrixLookAtLH(
		&view,
		&pos,//카메라의 위치
		&resultLookAt,//카메라가 보는 지점
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
void Camera::MouseControl()
{
	pos.z -= wheelState * TIMER->TimerElapsed();
	wheelState = 0;
}