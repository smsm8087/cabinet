#include "stdafx.h"
#include "TextureTest.h"

//���ؽ� ����(VertexBuffer)
//-����� ���� ���ؽ� ������ ��� �ִ� ����
//-���ؽ� �����͸� �����ϴ� �������� �޸� ���� ����
//���� �޸𸮿� ���۸� �����ϴµ� �ý��� �޸� �����͸�
//������ �ϴ� �� ���� ���� �޸𸮸� ������ �ϴ� ����
//�ξ� �����Ƿ� �迭 ��� ���۸� ����Ѵ�.

TextureTest::TextureTest()
{
	//D3DXCreateTextureFromFile(DEVICE, L"image/test.png", &texture);
	D3DXCreateTextureFromFileEx(
		DEVICE,
		L"image/test.png",
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
		&texture
	);

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	D3DXVECTOR2 textureSize = 
	{ (float)desc.Width, (float)desc.Height };


	UINT vertexCount = 6;
	vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(0, 0, 0, 0);
	vertex[1] = Vertex(textureSize.x, 0, 1, 0);
	vertex[2] = Vertex(0, textureSize.y, 0, 1);
	vertex[3] = Vertex(0, textureSize.y, 0, 1);
	vertex[4] = Vertex(textureSize.x, 0, 1, 0);
	vertex[5] = Vertex(textureSize.x, textureSize.y, 1, 1);

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf, D3DPOOL_DEFAULT,
		&vertexBuffer, NULL);

	void* vertexData = NULL;
	//���ؽ� ���� �޸𸮿� �����ϱ� ���ؼ��� ���� �޸� ����������
	//�����Ͱ� �ʿ��ϴ�. �����͸� ��� ���ؼ�
	//Lock�޼��带 �̿��ϸ�, �̿��� ���� �ڿ��� �ݵ��
	//Unlock�޼��带 �̿��� ������ ����� �����Ѵ�.
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();

	delete[] vertex;
}


TextureTest::~TextureTest()
{
}

void TextureTest::Update()
{
}

void TextureTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetTexture(0, texture);
	
	//DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2,
		//vertex, sizeof(Vertex));

	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
