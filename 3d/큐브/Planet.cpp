#include "stdafx.h"
#include "Planet.h"


Planet::Planet(wstring fileName)
{
	world = new World;
	//texture->GetSize(&world->size);
	//world->pivot = world->size * 0.5f;
	D3DXCreateTextureFromFileEx(
		DEVICE,
		fileName.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1, NULL,
		//D3DFMT_UNKNOWN,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0xffff00ff,
		NULL,
		NULL,
		&texture9
	);

	D3DSURFACE_DESC desc;
	LPDIRECT3DTEXTURE9 temp = texture9;
	temp->GetLevelDesc(0, &desc);
	D3DXVECTOR2 textureSize =
	{ (float)desc.Width, (float)desc.Height };

	vertex = new Vertex[4];
	//정면
	vertex[0] = Vertex(-textureSize.x, textureSize.x, -textureSize.x, 0, 0);
	vertex[1] = Vertex(textureSize.x, textureSize.x, -textureSize.x, 1, 0);
	vertex[2] = Vertex(-textureSize.x, -textureSize.x, -textureSize.x, 0, 1);
	vertex[3] = Vertex(textureSize.x, -textureSize.x, -textureSize.x, 1, 1);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);

	//오른쪽
	vertex[0] = Vertex(textureSize.x, textureSize.x, -textureSize.x, 0, 0);
	vertex[1] = Vertex(textureSize.x, textureSize.x, textureSize.x, 1, 0);
	vertex[2] = Vertex(textureSize.x, -textureSize.x, -textureSize.x, 0, 1);
	vertex[3] = Vertex(textureSize.x, -textureSize.x, textureSize.x, 1, 1);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);

	//윗면
	vertex[0] = Vertex(-textureSize.x, textureSize.x, textureSize.x, 0, 0);
	vertex[1] = Vertex(textureSize.x, textureSize.x, textureSize.x, 1, 0);
	vertex[2] = Vertex(-textureSize.x, textureSize.x, -textureSize.x, 0, 1);
	vertex[3] = Vertex(textureSize.x, textureSize.x, -textureSize.x, 1, 1);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);

	//왼쪽
	vertex[0] = Vertex(-textureSize.x, textureSize.x, textureSize.x, 0, 0);
	vertex[1] = Vertex(-textureSize.x, textureSize.x, -textureSize.x, 1, 0);
	vertex[2] = Vertex(-textureSize.x, -textureSize.x, textureSize.x, 0, 1);
	vertex[3] = Vertex(-textureSize.x, -textureSize.x, -textureSize.x, 1, 1);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);

	//뒷면
	vertex[0] = Vertex(textureSize.x, textureSize.x, textureSize.x, 0, 0);
	vertex[1] = Vertex(-textureSize.x, textureSize.x, textureSize.x, 1, 0);
	vertex[2] = Vertex(textureSize.x, -textureSize.x, textureSize.x, 0, 1);
	vertex[3] = Vertex(-textureSize.x, -textureSize.x, textureSize.x, 1, 1);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);

	//아래쪽
	vertex[0] = Vertex(-textureSize.x, -textureSize.x, -textureSize.x, 0, 0);
	vertex[1] = Vertex(textureSize.x, -textureSize.x, -textureSize.x, 1, 0);
	vertex[2] = Vertex(-textureSize.x, -textureSize.x, textureSize.x, 0, 1);
	vertex[3] = Vertex(textureSize.x, -textureSize.x, textureSize.x, 1, 1);
	cube.push_back(vertex[0]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[2]);
	cube.push_back(vertex[1]);
	cube.push_back(vertex[3]);
}

Planet::~Planet()
{
}

void Planet::Update()
{
	
	world->rot.y -= TIMER->TimerElapsed();
	world->Update();
}

void Planet::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture9);
	world->SetWorld();
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, cube.size() / 3,
		cube.begin()._Ptr, sizeof(Vertex));
	////알파연산을 시작하겠다.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	////알파연산을 하는데 덧셈으로 연산하겠다.
	//DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	////DEST : 뿌려지는 뒷 배경의 색깔
	////SRC : 뿌려지는 색깔
	////SRCALPHA : 뿌릴 색깔의 알파값
	////INVSRCALPHA : 1 - SRCALPHA

	////뒷 배경 색에다가 뿌릴 색깔의 역수를 곱하겠다.
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////뿌릴 색깔에다가 자기자신의 알파값을 곱하겠다.
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	////texture->Render();

	////알파연산 끝났다.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
