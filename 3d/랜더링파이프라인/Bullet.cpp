#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	isActive = true;
	viewPos = { 0,0 };

	vertex = new Vertex[6];
	vertex[0] = Vertex(0, 0, 0xff000000);
	vertex[1] = Vertex(10, 0, 0xff000000);
	vertex[2] = Vertex(0, 10, 0xff000000);
	vertex[3] = Vertex(0, 10, 0xff000000);
	vertex[4] = Vertex(10, 0, 0xff000000);
	vertex[5] = Vertex(10, 10, 0xff000000);
	
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(
		&projection, 0.0f, viewport.Width, viewport.Height, 0.0f, -1, 1
	);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	fSpeed = 3.f;
}



Bullet::~Bullet()
{
	delete[] vertex;
}

void Bullet::Update(void)
{
	worldPos.x += cosf(Angle) * fSpeed;
	worldPos.y += sinf(Angle) * fSpeed;

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);
	D3DXMatrixTranslation(&view, viewPos.x, viewPos.y, 0);
	DEVICE->SetTransform(D3DTS_VIEW, &view);
	SetRect(&rc, worldPos.x, worldPos.y, worldPos.x + 10, worldPos.y + 10);
}

void Bullet::Render(void)
{
	if (!isActive)return;
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex,sizeof(Vertex));
}

void Bullet::Fire(float _x, float _y, float _angle)
{
	worldPos.x = _x;
	worldPos.y = _y;
	Angle = _angle;
}
