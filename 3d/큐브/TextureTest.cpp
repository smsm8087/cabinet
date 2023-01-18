#include "stdafx.h"
#include "TextureTest.h"

//버텍스 버퍼(VertexBuffer)
//-사용자 정의 버텍스 정보를 담고 있는 버퍼
//-버텍스 데이터를 보관하는 연속적인 메모리 저장 공간
//비디오 메모리에 버퍼를 저장하는데 시스템 메모리 데이터를
//랜더링 하는 것 보다 비디오 메모리를 랜더링 하는 것이
//훨씬 빠르므로 배열 대신 버퍼를 사용한다.

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
	//버텍스 버퍼 메모리에 접근하기 위해서는 내부 메모리 컨텐츠로의
	//포인터가 필요하다. 포인터를 얻기 위해서
	//Lock메서드를 이용하며, 이용이 끝난 뒤에는 반드시
	//Unlock메서드를 이용해 버퍼의 잠금을 해제한다.
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
