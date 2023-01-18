#pragma once

//FVF정보 셋팅 옵션
//FVF(Flexible Vertex Format : 사용 할 정점의 다양한 정보를 
//사용자가 직접 필요한 부분만 골라서 정의하여 쓸 수 있는 방법

//1. Position 정점의 좌표(x, y, z) : D3DFVF_XYZ - 정점 포맷이 변환되지 않은 정점의 위치 좌표
//2. RHW : D3DFVF_XYZRHW - 정점 포맷이 변환 된 정점의 위치 좌표
//3. Blending Weight Data 결합 가중치(float) : D3DFVF_XYZB1 ~ B5
//4. Vertex Normal 정점의 법선 벡터 x, y, z : D3DFVF_NORMAL
//5. Vertex Point Size 정점의 점 크기 : D3DFVF_PSIZE
//6. Diffuse Color : D3DFVF_DIFFUSE
//7. Specular Color : D3DFVF_SPECULAR
//8. Texture Coordinate Set1 : D3DFVF_TEX0~8
//구조체의 멤버 변수 순서는 위 번호 순으로 만들어 져야 한다.
class CubeTest : public Test
{
private:
	struct Vertex
	{
		D3DXVECTOR3 position;
		DWORD color;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vertex() {}
		Vertex(float x, float y, float z, DWORD color)
		{
			position = { x, y, z };
			this->color = color;
		}
	};

	Vertex* vertex;

	vector<Vertex> cube;

	D3DXMATRIX world;
	float angleX, angleY;
public:
	CubeTest();
	~CubeTest();

	void Update();
	void Render();
};

