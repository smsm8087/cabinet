#include "stdafx.h"
#include "CubeTest.h"


CubeTest::CubeTest()
{
	angleX = 0;
	angleY = 0;
	vertex = new Vertex[8];
	vertex[0] = Vertex(-1, 1, -1, 0xffff0000);
	vertex[1] = Vertex(1, 1, -1, 0xff00ff00);
	vertex[2] = Vertex(-1, -1, -1, 0xff0000ff);
	vertex[3] = Vertex(1, -1, -1, 0xffffff00);
	vertex[4] = Vertex(-1, 1, 1, 0xffff00ff);
	vertex[5] = Vertex(1, 1, 1, 0xff00ffff);
	vertex[6] = Vertex(-1, -1, 1, 0xff000000);
	vertex[7] = Vertex(1, -1, 1, 0xfffffffff);

	//Á¤¸é
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);
	cube.push_back(vertex[2]);

	//¿À¸¥ÂÊ ¸é
	cube.push_back(vertex[1]);
	cube.push_back(vertex[5]);
	cube.push_back(vertex[3]);
	cube.push_back(vertex[3]);
	cube.push_back(vertex[5]);
	cube.push_back(vertex[7]);

	//À­¸é ¸é
	cube.push_back(vertex[0]);
	cube.push_back(vertex[4]);
	cube.push_back(vertex[5]);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[5]);
	cube.push_back(vertex[1]);

	//¿ÞÂÊ ¸é
	cube.push_back(vertex[0]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[4]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[6]);
	cube.push_back(vertex[4]);

	//µÞ ¸é
	cube.push_back(vertex[4]);
	cube.push_back(vertex[6]);
	cube.push_back(vertex[5]);
	cube.push_back(vertex[5]);
	cube.push_back(vertex[6]);
	cube.push_back(vertex[7]);

	//¾Æ·§ ¸é
	cube.push_back(vertex[2]);
	cube.push_back(vertex[7]);
	cube.push_back(vertex[6]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[3]);
	cube.push_back(vertex[7]);
}


CubeTest::~CubeTest()
{
}

void CubeTest::Update()
{
	angleX += TIMER->TimerElapsed();
	angleY += TIMER->TimerElapsed();

	//D3DXMatrixRotationY(&world, angle);
	D3DXMatrixRotationYawPitchRoll(&world, angleY, angleX, 0);
}

void CubeTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		cube.size() / 3, cube.begin()._Ptr, sizeof(Vertex));
}
