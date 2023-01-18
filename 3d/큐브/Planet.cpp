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
	//����
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

	//������
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

	//����
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

	//����
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

	//�޸�
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

	//�Ʒ���
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
	////���Ŀ����� �����ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	////���Ŀ����� �ϴµ� �������� �����ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	////DEST : �ѷ����� �� ����� ����
	////SRC : �ѷ����� ����
	////SRCALPHA : �Ѹ� ������ ���İ�
	////INVSRCALPHA : 1 - SRCALPHA

	////�� ��� �����ٰ� �Ѹ� ������ ������ ���ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	////�Ѹ� ���򿡴ٰ� �ڱ��ڽ��� ���İ��� ���ϰڴ�.
	//DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	////texture->Render();

	////���Ŀ��� ������.
	//DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
