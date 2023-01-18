#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	pos = { 0, 10, -10 };
	lookAtPos = { 0, 0, 0 };
	resultPos = pos;
	resultLookAtPos = lookAtPos;

	targetIndex = 0;

	SetView();
	SetProjection();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	SetTarget();
	MouseControl();
	CameraRotation();
	SetView();
}

void Camera::SetView()
{
	D3DXMatrixLookAtLH(
		&view,
		&resultPos,//카메라의 위치
		&resultLookAtPos,//카메라가 보는 지점
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
	D3DXVECTOR3 dir = pos - lookAtPos;
	float dist = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
	D3DXVECTOR3 normalDir = dir / dist;

	dir += -normalDir * wheelState * TIMER->TimerElapsed() * 5;

	pos = lookAtPos + dir;

	wheelState = 0;
}

void Camera::CameraRotation()
{
	if (KEYBOARD->KeyDown(VK_RBUTTON)) {
		lastMousePos = mousePos;
	}

	if (KEYBOARD->KeyPress(VK_RBUTTON)) {
		rot.y -= (lastMousePos.x - mousePos.x) * TIMER->TimerElapsed() * 3.f;
		rot.x -= (lastMousePos.y - mousePos.y) * TIMER->TimerElapsed() * 3.f;
		
		lastMousePos = mousePos;
	}

	D3DXVECTOR3 dir = pos - lookAtPos;
	D3DXMATRIX R;
	D3DXMatrixRotationYawPitchRoll(&R, rot.y, rot.x, rot.z);
	D3DXVECTOR3 newPos = { dir.x * R._11 + dir.y * R._21 + dir.z * R._31,
						dir.x * R._12 + dir.y * R._22 + dir.z * R._32,
						dir.x * R._13 + dir.y * R._23 + dir.z * R._33 };

	resultPos = newPos + resultLookAtPos;
}

void Camera::AddTarget(World * targetWorld)
{
	targetWorlds.push_back(targetWorld);
}

void Camera::SetTarget()
{
	if (KEYBOARD->KeyDown(VK_RIGHT)) {
		targetIndex = (targetIndex + 1) % targetWorlds.size();
	}
	else if (KEYBOARD->KeyDown(VK_LEFT)) {
		targetIndex = (targetIndex - 1 + targetWorlds.size()) % targetWorlds.size();
	}

	if (targetIndex == 1)
		int b = 1;

	D3DXVECTOR3 targetWorldPos = targetWorlds[targetIndex]->GetWorldPos();
	resultPos = targetWorldPos + pos;
	resultLookAtPos = targetWorldPos + lookAtPos;
}
