#include "stdafx.h"
#include "Sun.h"


Sun::Sun()
{

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	//�¾�
	Sunvertex = new Vertex[6];
	Sunvertex[0] = Vertex(0, 0, 0, 0);
	Sunvertex[1] = Vertex(100, 0, 1, 0);
	Sunvertex[2] = Vertex(100, 100, 1, 1);
	Sunvertex[3] = Vertex(0, 0, 0, 0);
	Sunvertex[4] = Vertex(100, 100, 1, 1);
	Sunvertex[5] = Vertex(0, 100, 0, 1);
	Sunpivot = { 50,50 };
	Sunworldpos = { (float)viewport.Width / 2,(float)viewport.Height / 2 };


	//����
	Earthvertex = new Vertex[6];
	Earthvertex[0] = Vertex(0, 0, 0, 0);
	Earthvertex[1] = Vertex(100, 0, 1, 0);
	Earthvertex[2] = Vertex(100, 100, 1, 1);
	Earthvertex[3] = Vertex(0, 0, 0, 0);
	Earthvertex[4] = Vertex(100, 100, 1, 1);
	Earthvertex[5] = Vertex(0, 100, 0, 1);

	Earthpivot = { 50,50 };
	Earthworldpos = { Sunworldpos.x - 100,Sunworldpos.y - 100 };

	//��
	Moonvertex = new Vertex[6];
	Moonvertex[0] = Vertex(0, 0, 0, 0);
	Moonvertex[1] = Vertex(100, 0, 1, 0);
	Moonvertex[2] = Vertex(100, 100, 1, 1);
	Moonvertex[3] = Vertex(0, 0, 0, 0);
	Moonvertex[4] = Vertex(100, 100, 1, 1);
	Moonvertex[5] = Vertex(0, 100, 0, 1);

	Moonpivot = { 50,50 };


	Moonworldpos = { Earthworldpos.x - 50,Earthworldpos.y - 50 };
	//��(ī�޶�)�� ������ ������ �ִ� ����ü
	D3DXMatrixOrthoOffCenterLH(
		&projection, 0, viewport.Width, viewport.Height, 0,
		-1, 1
	);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);

	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);//���̷�Ʈ�� ������ ������ false�� ��� ���� ���´�.
	D3DXMatrixIdentity(&Sunworld);
	D3DXMatrixTranslation(&view, 0, 0, 0);
	Sunimage = new Texture(L"image/ryong.png", Sunvertex, Suntexture);
	Earthimage = new Texture(L"image/player2.bmp", Earthvertex, Earthtexture);
	Moonimage = new Texture(L"image/Tank.bmp", Moonvertex, Moontexture);

}


Sun::~Sun()
{
	delete[] Sunvertex;
}

void Sun::Update()
{
	//Sun
	//����
	D3DXMATRIX SunRotZ;
	D3DXMatrixRotationZ(&SunRotZ, Sunrotation.z);
	Sunrotation.z += 0.02f;
	//ȭ���߽����� �̵�
	D3DXMATRIX ST;
	D3DXMatrixTranslation(&ST, Sunworldpos.x - 100, Sunworldpos.y - 50, 0);
	//�������� ȸ���ϱ�
	D3DXMATRIX Spivot;
	D3DXMatrixTranslation(&Spivot, Sunpivot.x, Sunpivot.y, 0);

	D3DXMATRIX invSunPivot;
	D3DXMatrixInverse(&invSunPivot, NULL, &Spivot);

	D3DXMATRIX SR;
	SR = invSunPivot * SunRotZ * Spivot;

	//������ ����� ��ȯ
	Sunworld = SR * ST;
	/////////////////////////////////////////////
	//Earth
	D3DXMATRIX EarthRotZ;
	D3DXMatrixRotationZ(&EarthRotZ, Earthrotation.z);
	Earthrotation.z += 0.05f;
	//ȭ���߽����� �̵�
	D3DXMATRIX ET;
	D3DXMatrixTranslation(&ET, Earthworldpos.x - 200, Earthworldpos.y - 150, 0);
	//�������� ȸ���ϱ�
	D3DXMATRIX Epivot;
	D3DXMatrixTranslation(&Epivot, Earthpivot.x, Earthpivot.y, 0);

	D3DXMATRIX invEarthPivot;
	D3DXMatrixInverse(&invEarthPivot, NULL, &Epivot);

	D3DXMATRIX ER;
	ER = invEarthPivot * EarthRotZ * Epivot;

	//������ ����� ��ȯ
	Earthworld = ER * ET *Sunworld;
	////////////////////////////////////////////////
	//Moon
	D3DXMATRIX MoonRotZ;
	D3DXMatrixRotationZ(&MoonRotZ, Moonrotation.z);
	Moonrotation.z += 0.15f;
	//ȭ���߽����� �̵�
	D3DXMATRIX MT;
	D3DXMatrixTranslation(&MT, Moonworldpos.x - 300, Moonworldpos.y - 200, 0);
	//�������� ȸ���ϱ�
	D3DXMATRIX Mpivot;
	D3DXMatrixTranslation(&Mpivot, Moonpivot.x, Moonpivot.y, 0);

	D3DXMATRIX invMoonPivot;
	D3DXMatrixInverse(&invMoonPivot, NULL, &Mpivot);

	D3DXMATRIX MR;
	MR = invMoonPivot * MoonRotZ * Mpivot;

	Moonworld = MR * MT *Earthworld;

	DEVICE->SetTransform(D3DTS_VIEW, &view);

}

void Sun::Render()
{
	DEVICE->SetFVF(Vertex::fvf);



	DEVICE->SetTransform(D3DTS_WORLD, &Earthworld);
	Earthimage->Render();
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, Moonvertex, sizeof(Vertex));
	
	
	DEVICE->SetTransform(D3DTS_WORLD, &Moonworld);
	Moonimage->Render();
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, Earthvertex, sizeof(Vertex));

	DEVICE->SetTransform(D3DTS_WORLD, &Sunworld);
	Sunimage->Render();
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, Sunvertex, sizeof(Vertex));
}
