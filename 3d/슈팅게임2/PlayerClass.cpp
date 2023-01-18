#include "stdafx.h"
#include "PlayerClass.h"

PlayerClass::PlayerClass()
{
	vertexCount = 3;
	worldPos = { 720,350 };
	viewPos = { 0,0 };

	vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(0, 0, 0xff0000ff);
	vertex[1] = Vertex(50, 25, 0xff0000ff);
	vertex[2] = Vertex(0, 50, 0xff0000ff);

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

	mBullet = new BulletManager(5.0f, 0.0f, 50);
}


PlayerClass::~PlayerClass()
{
	delete mBullet;
	delete[] vertex;
	vertexBuffer->Release();
}

void PlayerClass::Update()
{
	if (_KEY->StayKeyDown('D') && worldPos.x < 1425 - 50) {
		worldPos.x += 3.0f;
	}
	if (_KEY->StayKeyDown('A') && worldPos.x > 0) {
		worldPos.x -= 3.0f;
	}
	if (_KEY->StayKeyDown('W') && worldPos.y > 0) {
		worldPos.y -= 3.0f;
	}
	if (_KEY->StayKeyDown('S') && worldPos.y < 700 - 50) {
		worldPos.y += 3.0f;
	}

	angle = atan2(mousePos.y - worldPos.y - 25, mousePos.x - worldPos.x - 25);
	if (_KEY->isKeyDown(VK_LBUTTON)) {
		mBullet->isFire(worldPos.x + 25, worldPos.y + 25, angle);
	}
	
	D3DXMATRIX center;
	D3DXMatrixTranslation(&center, 25, 25, 0);
	D3DXMATRIX invCenter;
	D3DXMatrixInverse(&invCenter, NULL, &center);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, worldPos.x, worldPos.y, 0);

	D3DXMATRIX R, matRota;
	D3DXMatrixRotationZ(&matRota, angle);
	R = invCenter * matRota * center;

	world = R * T;
	mBullet->Update();
}

void PlayerClass::Render()
{
	_DEVICE->SetFVF(Vertex::fvf);
	_DEVICE->SetTransform(D3DTS_VIEW, &view);
	
	_DEVICE->SetTransform(D3DTS_WORLD, &world);
	_DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	_DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	mBullet->Render();
}
