#pragma once

#include "cVector3.h"
#include "cMatrix.h"

class cMainGame
{
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;

	//���� �����̽� -> ���� �����̽� -> ī�޶����̽� -> �������ǽ����̽� -> ����Ʈ

	cMatrix m_matLocal;		//����
	cMatrix m_matWorld;		//����
	cMatrix m_matCamera;	//ī�޶�
	cMatrix m_matProjection;//��������
	cMatrix m_matViewPort;  //����Ʈ
	cMatrix matR;

	cMatrix m_matLocalG;		//�������
	cMatrix m_matWorldG;		//�������
	cMatrix m_matCameraG;	//����ī�޶�
	cMatrix m_matProjectionG;//������������
	cMatrix m_matViewPortG;  //�������Ʈ

							//����
	vector<cVector3> m_vecVertex;
	//������ ��ȣ 
	vector<int> m_vecVertexNum;
	int m_nVertexNum;
	vector<int> m_vecIndexingCheck;

	//���ڿ� 
	vector<cVector3> m_vecGrid;
	vector<int>	m_vecGridPoint;
	

	cVector3 m_vEye;	//����ġ
	cVector3 m_vLookAt; //���¹���
	cVector3 m_vUp;		//����
	cVector3 m_vBoxPos; //�׸���ġ
	cVector3 m_Dir;	//����

	cVector3 m_vGroundPos; //��


	cVector3         m_vPlaneRowRight[11];
	cVector3         m_vPlaneColUp[11];
	cVector3         m_vPlaneRowLeft[11];
	cVector3         m_vPlaneColDown[11];

	cVector3		m_offset;

	float	 m_fBoxAngleX;	//x������ �����̱�
	float	 m_fBoxAngleY;	//y������ �����̱�

	float	 m_fGroundAngleX;	//��x������ �����̱�
	float	 m_fGroundAngleY;	//��y������ �����̱�

	float	 m_fCameraAngleX;	
	float	 m_fCameraAngleY;	

	float	 m_fBoxHeel;
	
	cVector3 m_vBoxDirection;

	POINT Mousept;

	bool m_isRightRotation;
	bool m_isLeftRotation;

public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

