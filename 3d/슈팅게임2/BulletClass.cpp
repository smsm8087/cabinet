#include "stdafx.h"
#include "BulletClass.h"


BulletClass::BulletClass()
{
}

BulletClass::BulletClass(float speed, float radian)
{
	vertexCount = 6;
	worldPos = { 0,0 };
	viewPos = { 0,0 };

	vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(0, 0, 0xff000000);
	vertex[1] = Vertex(10, 0, 0xff000000);
	vertex[2] = Vertex(0, 10, 0xff000000);
	vertex[3] = Vertex(0, 10, 0xff000000);
	vertex[4] = Vertex(10, 0, 0xff000000);
	vertex[5] = Vertex(10, 10, 0xff000000);

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	_DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();

	D3DVIEWPORT9 viewport;
	_DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(
		&projection, 0.0f, viewport.Width, viewport.Height, 0.0f, -1, 1
	);

	_DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);

	fSpeed = speed;
	fRadian = radian;
}


BulletClass::~BulletClass()
{
}

void BulletClass::Update(void)
{
	if (!isActive) return;
	if (worldPos.x > 1450 + fRadian || worldPos.x < -fRadian ||
		worldPos.y > 700 + fRadian || worldPos.y < -fRadian) {
		isActive = false;
		return;
	}
	worldPos.x += cosf(angle) * fSpeed;
	worldPos.y += sinf(angle) * fSpeed;

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);
	D3DXMatrixTranslation(&view, viewPos.x, viewPos.y, 0);

}

void BulletClass::Render(void)
{
	if (!isActive) return;

	_DEVICE->SetFVF(Vertex::fvf);
	_DEVICE->SetTransform(D3DTS_VIEW, &view);

	_DEVICE->SetTransform(D3DTS_WORLD, &world);
	_DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	
}

void BulletClass::isFire(float _x, float _y, float _angle)
{
	worldPos.x = _x;
	worldPos.y = _y;
	angle = _angle;

	isActive = true;
}
