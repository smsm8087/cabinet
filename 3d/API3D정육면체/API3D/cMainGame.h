#pragma once

#include "cVector3.h"
#include "cMatrix.h"

class cMainGame
{
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;

	//로컬 스페이스 -> 월드 스페이스 -> 카메라스페이스 -> 프로젝션스페이스 -> 뷰포트

	cMatrix m_matLocal;		//로컬
	cMatrix m_matWorld;		//월드
	cMatrix m_matCamera;	//카메라
	cMatrix m_matProjection;//프로젝션
	cMatrix m_matViewPort;  //뷰포트
	cMatrix matR;

	cMatrix m_matLocalG;		//지면로컬
	cMatrix m_matWorldG;		//지면월드
	cMatrix m_matCameraG;	//지면카메라
	cMatrix m_matProjectionG;//지면프로젝션
	cMatrix m_matViewPortG;  //지면뷰포트

							//정점
	vector<cVector3> m_vecVertex;
	//정점의 번호 
	vector<int> m_vecVertexNum;
	int m_nVertexNum;
	vector<int> m_vecIndexingCheck;

	//격자용 
	vector<cVector3> m_vecGrid;
	vector<int>	m_vecGridPoint;
	

	cVector3 m_vEye;	//눈위치
	cVector3 m_vLookAt; //보는방향
	cVector3 m_vUp;		//수직
	cVector3 m_vBoxPos; //네모위치
	cVector3 m_Dir;	//방향

	cVector3 m_vGroundPos; //땅


	cVector3         m_vPlaneRowRight[11];
	cVector3         m_vPlaneColUp[11];
	cVector3         m_vPlaneRowLeft[11];
	cVector3         m_vPlaneColDown[11];

	cVector3		m_offset;

	float	 m_fBoxAngleX;	//x축으로 움직이기
	float	 m_fBoxAngleY;	//y축으로 움직이기

	float	 m_fGroundAngleX;	//땅x축으로 움직이기
	float	 m_fGroundAngleY;	//땅y축으로 움직이기

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

