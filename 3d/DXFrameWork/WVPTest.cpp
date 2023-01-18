#include "stdafx.h"
#include "WVPTest.h"


WVPTest::WVPTest()
{
	worldPos = { 200, 200 };
	worldPos2 = { 50, 50 };
	cameraPos = { 0, 0 };

	vertex = new Vertex[6];
	vertex[0] = Vertex(-50, -50, 0xffff0000);
	vertex[1] = Vertex(50, -50, 0xffff0000);
	vertex[2] = Vertex(-50, 50, 0xffff0000);
	vertex[3] = Vertex(-50, 50, 0xffff0000);
	vertex[4] = Vertex(50, -50, 0xffff0000);
	vertex[5] = Vertex(50, 50, 0xffff0000);

	//vertex[0] = Vertex(0, 0, 0xffff0000);
	//vertex[1] = Vertex(100, 0, 0xffff0000);
	//vertex[2] = Vertex(0, 100, 0xffff0000);
	//vertex[3] = Vertex(0, 100, 0xffff0000);
	//vertex[4] = Vertex(100, 0, 0xffff0000);
	//vertex[5] = Vertex(100, 100, 0xffff0000);

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
	D3DXMatrixIdentity(&world2);

	//world._41 = worldPos.x;
	//world._42 = worldPos.y;
	//D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);	
	//D3DXMatrixTranslation(&world2, worldPos2.x, worldPos2.y, 0);

	mfAngle = 0.0f;
}


WVPTest::~WVPTest()
{
	delete[] vertex;
}

void WVPTest::Update()
{
	mfAngle += 0.1f;
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

	RECT crc, crc1, crc2;

	crc1 = RectMake(worldPos.x, worldPos.y, 100, 100);
	crc2 = RectMake(worldPos2.x, worldPos2.y, 100, 100);

	if (IntersectRect(&crc, &crc1, &crc2))
	{
		int x = 0;
	}
	D3DXMATRIX SC;
	D3DXMatrixIdentity(&SC);
	D3DXMatrixScaling(&SC, 2, 2, 2);


	D3DXMATRIX RZ;
	D3DXMatrixIdentity(&RZ);
	D3DXMatrixRotationZ(&RZ, mfAngle);

	D3DXMATRIX Tr;
	D3DXMatrixIdentity(&Tr);
	D3DXMatrixTranslation(&Tr, worldPos.x, worldPos.y, 0);
	world = SC * RZ *Tr;

	//D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);
	D3DXMatrixTranslation(&world2, worldPos2.x, worldPos2.y, 0);

	//if (KEYBOARD->KeyDown('1'))
	//{
	//	D3DXMatrixTranslation(&view2, 100, 100, 0);
	//	DEVICE->SetTransform(D3DTS_VIEW, &view2);
	//}
	//else if (KEYBOARD->KeyDown('2'))
	//{
	//}

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

