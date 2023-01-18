#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	SetProjection();
}


Camera::~Camera()
{
}

void Camera::Update()
{
}

void Camera::SetProjection()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewport.Width,
		viewport.Height, 0.0f, -1, 1);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
}
