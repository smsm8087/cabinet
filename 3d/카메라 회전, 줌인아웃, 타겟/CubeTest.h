#pragma once

//FVF���� ���� �ɼ�
//FVF(Flexible Vertex Format : ��� �� ������ �پ��� ������ 
//����ڰ� ���� �ʿ��� �κи� ��� �����Ͽ� �� �� �ִ� ���

//1. Position ������ ��ǥ(x, y, z) : D3DFVF_XYZ - ���� ������ ��ȯ���� ���� ������ ��ġ ��ǥ
//2. RHW : D3DFVF_XYZRHW - ���� ������ ��ȯ �� ������ ��ġ ��ǥ
//3. Blending Weight Data ���� ����ġ(float) : D3DFVF_XYZB1 ~ B5
//4. Vertex Normal ������ ���� ���� x, y, z : D3DFVF_NORMAL
//5. Vertex Point Size ������ �� ũ�� : D3DFVF_PSIZE
//6. Diffuse Color : D3DFVF_DIFFUSE
//7. Specular Color : D3DFVF_SPECULAR
//8. Texture Coordinate Set1 : D3DFVF_TEX0~8
//����ü�� ��� ���� ������ �� ��ȣ ������ ����� ���� �Ѵ�.
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

