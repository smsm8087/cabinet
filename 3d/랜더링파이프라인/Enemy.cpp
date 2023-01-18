#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	isActive = true;
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);
	
	upNum = 0;
	downNum = 0;
	vertex = new Vertex[6];
	vertex[0] = Vertex(0, 0, 0xff00ff00);
	vertex[1] = Vertex(0,-100 , 0xff00ff00);
	vertex[2] = Vertex(100,0, 0xff00ff00);
	vertex[3] = Vertex(100, 0, 0xff00ff00);
	vertex[4] = Vertex(0, -100, 0xff00ff00);
	vertex[5] = Vertex(100,-100, 0xff00ff00);

	float randomX = rand() % viewport.Width;
	float randomY = rand() % viewport.Height;
	worldPos = { randomX,randomY };
	//뷰(카메라)의 정보를 가지고 있는 구조체
	D3DXMatrixOrthoOffCenterLH(
		&projection, 0, viewport.Width, viewport.Height, 0,
		-1, 1
	);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);//다이렉트의 조명은 검정색 false로 줘야 색이 나온다.
	D3DXMatrixIdentity(&world);

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);

	D3DXMatrixTranslation(&view, 0, 0, 0);

}


Enemy::~Enemy()
{
	delete[] vertex;
}

void Enemy::Update()
{
	srand(time(NULL));

	D3DXMATRIX S;
	D3DXMatrixScaling(&S, 1, 1, 1);
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, Angle);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, worldPos.x, worldPos.y, 0);

	if (upNum > 50)
	{
		isUpMoving = true;
		upNum = 0;
	}
	if (downNum > 50)
	{
		isUpMoving = false;
		downNum = 0;
	}
	if (isUpMoving)
	{
		worldPos.y -= 3;
		downNum++;
	}
	else
	{
		worldPos.y += 3;
		upNum++;
	}
	world = S * T;
	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Enemy::Render()
{
	if (!isActive)return;

	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));
}
