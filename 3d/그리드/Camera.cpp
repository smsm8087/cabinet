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
		&pos,//ī�޶��� ��ġ
		&resultLookAt,//ī�޶� ���� ����
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
void Camera::MouseControl()
{
	pos.z -= wheelState * TIMER->TimerElapsed();
	wheelState = 0;
}