#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	delete[] vertex;
}

void Enemy::Init()
{
	mPos = { 200, 200 };
	mbDestroy = false;

	vertex = new Vertex[6];
	vertex[0] = Vertex(-50, -50, 0xffff00ff);
	vertex[1] = Vertex(50, -50, 0xffff00ff);
	vertex[2] = Vertex(-50, 50, 0xffff00ff);
	vertex[3] = Vertex(-50, 50, 0xffff00ff);
	vertex[4] = Vertex(50, -50, 0xffff00ff);
	vertex[5] = Vertex(50, 50, 0xffff00ff);

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);
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



	//world._41 = worldPos.x;
	//world._42 = worldPos.y;
	//D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0);	
	//D3DXMatrixTranslation(&world2, worldPos2.x, worldPos2.y, 0);

	mfAngle = 0.0f;
	mfSpeed = 5.0f;
	mHp = 2;
}

void Enemy::Update()
{
	D3DXMatrixTranslation(&world, mPos.x, mPos.y, 0);

	if (mHp <= 0)
	{
		mbDestroy = true;
		Enemy*temp = ActorMgr::Instance().Create<Enemy>(CTYPE_ENEMY);
		temp->Init();

		RECT rc;
		GetClientRect(hWnd, &rc);
		D3DXVECTOR2 pos;
		pos.x = rand() & (rc.right-100);
		pos.y = rand() & (rc.bottom-100);

		temp->SetPos(pos);
		//return;
	}
	//if (KEYBOARD->KeyDown('1'))
	//{
	//	D3DXMatrixTranslation(&view2, 100, 100, 0);
	//	DEVICE->SetTransform(D3DTS_VIEW, &view2);
	//}
	//else if (KEYBOARD->KeyDown('2'))
	//{
	//}

	D3DXMatrixTranslation(&view, Camera::Instance().GetCameraPos().x, Camera::Instance().GetCameraPos().y, 0);
	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Enemy::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));

}
