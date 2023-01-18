#include "stdafx.h"
#include "EnemyClass.h"



EnemyClass::EnemyClass()
{
	vertexCount = 6;
	worldPos = { 0, 0 };
	viewPos = { 0,0 };

	vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(0, 0, 0xffff0000);
	vertex[1] = Vertex(50, 0, 0xffff0000);
	vertex[2] = Vertex(0, 50, 0xffff0000);
	vertex[3] = Vertex(0, 50, 0xffff0000);
	vertex[4] = Vertex(50, 0, 0xffff0000);
	vertex[5] = Vertex(50, 50, 0xffff0000);

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	_DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf, D3DPOOL_DEFAULT,&vertexBuffer, NULL);
	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();
	
	D3DVIEWPORT9 viewport;
	_DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewport.Width, viewport.Height, 0.0f, -1, 1);

	_DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	_DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);

	upMove = false;
}


EnemyClass::~EnemyClass()
{
	delete[] vertex;
	vertexBuffer->Release();
}

void EnemyClass::Update()
{
	if (!isActive) return;
	if (upMove) {
		worldPos.y-=5.0f;
		if (worldPos.y < 0)
			upMove = false;
	}
	else {
		worldPos.y+=5.0f;
		if (worldPos.y > 700-100)
			upMove = true;
	}

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);
}

void EnemyClass::Render()
{
	if (!isActive) return;
	_DEVICE->SetFVF(Vertex::fvf);
	_DEVICE->SetTransform(D3DTS_VIEW, &view);

	_DEVICE->SetTransform(D3DTS_WORLD, &world);
	_DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}

void EnemyClass::isActiveTrue(float _x, float _y)
{
	worldPos.x = _x;
	worldPos.y = _y;

	isActive = true;
}