#include "stdafx.h"
#include "SRTTest.h"


SRTTest::SRTTest()
{
	scale = { 1, 1 };
	rotation = { 0, 0, 0 };
	translation = { 100, 100};

	scale2 = { 1, 1 };
	rotation2 = { 0, 0, 0 };
	translation2 = { 100, 100 };

	vertex = new Vertex[3];
	vertex[0] = Vertex(0, 0, 0xffff0000);
	vertex[1] = Vertex(100, 0, 0xffff0000);
	vertex[2] = Vertex(0, 100, 0xffff0000);

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, viewport.Width,
		viewport.Height, 0.0f, -1, 1);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
}


SRTTest::~SRTTest()
{
}

void SRTTest::Update()
{
	if (KEYBOARD->KeyPress(VK_RIGHT))
		translation.x++;
	if (KEYBOARD->KeyPress(VK_LEFT))
		translation.x--;
	if (KEYBOARD->KeyPress(VK_UP))
		translation.y--;
	if (KEYBOARD->KeyPress(VK_DOWN))
		translation.y++;

	if (KEYBOARD->KeyPress('D'))
		scale.x += 0.1f;
	if (KEYBOARD->KeyPress('A'))
		scale.x -= 0.1f;
	if (KEYBOARD->KeyPress('W'))
		scale.y -= 0.1f;
	if (KEYBOARD->KeyPress('S'))
		scale.y += 0.1f;

	if (KEYBOARD->KeyPress('I'))
		rotation.z += 0.01f;
	if (KEYBOARD->KeyPress('K'))
		rotation.z -= 0.01f;

	if (KEYBOARD->KeyPress('O'))
		rotation2.z += 0.01f;
	if (KEYBOARD->KeyPress('L'))
		rotation2.z -= 0.01f;

	D3DXMATRIX T;
	D3DXMATRIX R;
	D3DXMATRIX S;

	D3DXVECTOR2 pivot = { 50, 50 };
	D3DXMATRIX matPivot;
	D3DXMATRIX invMatPivot;

	D3DXMatrixTranslation(&matPivot, pivot.x, pivot.y, 0);
	D3DXMatrixInverse(&invMatPivot, NULL, &matPivot);
	
	D3DXMATRIX matRot;
	D3DXMatrixRotationZ(&matRot, rotation.z);
	R = invMatPivot * matRot * matPivot;

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, 1);
	S = invMatPivot * matScale * matPivot;

	D3DXMatrixTranslation(&T, translation.x, translation.y, 0);

	world = S * R * T;

	D3DXMATRIX T2;
	D3DXMatrixTranslation(&T2, translation2.x,
		translation2.y, 0);

	D3DXMATRIX R2;
	D3DXMatrixRotationZ(&R2, rotation2.z);

	world2 = R2 * T2;
	//world = S * invMatPivot * matRot * matPivot * T;
	world *= world2;
	//world = S * R * T * T2;
}

void SRTTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vertex,
		sizeof(Vertex));
	DEVICE->SetTransform(D3DTS_WORLD, &world2);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vertex,
		sizeof(Vertex));
}
