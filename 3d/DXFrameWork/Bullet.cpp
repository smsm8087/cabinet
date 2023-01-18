#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	delete[] vertex;
}

void Bullet::Init()
{
	mPos = { 200, 200 };
	mbDestroy = false;

	vertex = new Vertex[6];
	vertex[0] = Vertex(-10, -10, 0xffffffff);
	vertex[1] = Vertex(10, -10, 0xffffffff);
	vertex[2] = Vertex(-10, 10, 0xffffffff);
	vertex[3] = Vertex(-10, 10, 0xffffffff);
	vertex[4] = Vertex(10, -10, 0xffffffff);
	vertex[5] = Vertex(10, 10, 0xffffffff);

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);
	//RECT rect;
	//GetClientRect(hWnd, &rect);
	//뷰(카메라)의 정보를 가지고 있는 구조체
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(
		&projection, 0, viewport.Width, viewport.Height, 0,
		-1, 1
	);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	mfAngle = 0.0f;
	mfSpeed = 10.0f;
}

void Bullet::Update()
{
	D3DXMatrixTranslation(&world, mPos.x, mPos.y, 0);

	//if (KEYBOARD->KeyDown('1'))
	//{
	//	D3DXMatrixTranslation(&view2, 100, 100, 0);
	//	DEVICE->SetTransform(D3DTS_VIEW, &view2);
	//}
	//else if (KEYBOARD->KeyDown('2'))
	//{
	//}
	mPos += mvDir * mfSpeed;

	D3DXMatrixTranslation(&view, Camera::Instance().GetCameraPos().x, Camera::Instance().GetCameraPos().y, 0);
	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Bullet::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));
}
