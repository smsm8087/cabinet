#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	Angle = 0.f;
	pivot = { 1,1 };

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	worldPos = { (float)viewport .Width/2,(float)viewport.Height/2 };

	vertex = new Vertex[3];
	vertex[0] = Vertex(0, -50, 0xffff0000);
	vertex[1] = Vertex(50,25 , 0xffff0000);
	vertex[2] = Vertex(-50,25, 0xffff0000);

	//뷰(카메라)의 정보를 가지고 있는 구조체
	D3DXMatrixOrthoOffCenterLH(
		&projection, 0, viewport.Width, viewport.Height, 0,
		-1, 1
	);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);//다이렉트의 조명은 검정색 false로 줘야 색이 나온다.
	D3DXMatrixIdentity(&world);

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);
}


Player::~Player()
{
	delete[] vertex;
}

void Player::Update()
{

	if (KEYBOARD->keyPress('D'))
		pivot.x+=0.1f;
	if (KEYBOARD->keyPress('A'))
		pivot.x-= 0.1f;
	if (KEYBOARD->keyPress('W'))
		pivot.y-= 0.1f;
	if (KEYBOARD->keyPress('S'))
		pivot.y+= 0.1f;


	Angle = atan2(mousePos.y - worldPos.y, mousePos.x - worldPos.x);
	D3DXMATRIX S;
	
	D3DXMATRIX matPivot;
	D3DXMatrixScaling(&S, pivot.x, pivot.y,1);
	
	
	D3DXMATRIX invPivot;
	D3DXMatrixInverse(&invPivot, NULL, &matPivot);

	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, Angle);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, worldPos.x, worldPos.y, 0);

	world = S * R * T;
	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Player::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vertex, sizeof(Vertex));
}
