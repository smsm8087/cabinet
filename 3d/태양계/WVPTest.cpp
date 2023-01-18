#include "stdafx.h"
#include "WVPTest.h"


WVPTest::WVPTest()
{
	worldPos = { 100, 100 };
	cameraPos = { 0, 0 };

	vertex = new Vertex[6];
	vertex[0] = Vertex(0, 0, 0xffff0000);
	vertex[1] = Vertex(100, 0, 0xffff0000);
	vertex[2] = Vertex(0, 100, 0xffff0000);
	vertex[3] = Vertex(0, 100, 0xffff0000);
	vertex[4] = Vertex(100, 0, 0xffff0000);
	vertex[5] = Vertex(100, 100, 0xffff0000);

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
	
	//world._11 = 1;
	//world._22 = 1;
	//world._33 = 1;
	//world._44 = 1;
	D3DXMatrixIdentity(&world);
	
	//world._41 = worldPos.x;
	//world._42 = worldPos.y;
	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);	
	D3DXMatrixIdentity(&world2);
}


WVPTest::~WVPTest()
{
}

void WVPTest::Update()
{
	if (KEYBOARD->keyPress(VK_RIGHT))
		worldPos.x++;
	if (KEYBOARD->keyPress(VK_LEFT))
		worldPos.x--;
	if (KEYBOARD->keyPress(VK_UP))
		worldPos.y--;
	if (KEYBOARD->keyPress(VK_DOWN))
		worldPos.y++;

	if (KEYBOARD->keyPress('D'))
		cameraPos.x++;
	if (KEYBOARD->keyPress('A'))
		cameraPos.x--;
	if (KEYBOARD->keyPress('W'))
		cameraPos.y--;
	if (KEYBOARD->keyPress('S'))
		cameraPos.y++;

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);
	D3DXMatrixTranslation(&view, cameraPos.x, cameraPos.y, 0);

	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void WVPTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));

	DEVICE->SetTransform(D3DTS_WORLD, &world2);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));
}

