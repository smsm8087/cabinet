#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
	: m_hBitmap(NULL), m_vEye(0, 0, -10), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0), m_vBoxPos(0, 0, 0)
	, m_Dir(0,0,1)
	, m_vGroundPos(0,0,0)
	, m_fBoxAngleX(0.0f)
	, m_fBoxAngleY(0.0f)
	, m_fGroundAngleX(0.0f)
	, m_fGroundAngleY(0.0f)
	, m_fBoxHeel(7.0f)
	, m_isRightRotation(false)
	, m_isLeftRotation(false)
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	Mousept.x = 0;
	Mousept.y = 0;
	/*
	cMatrix m_matLocal;		//로컬
	cMatrix m_matWorld;		//월드
	cMatrix m_matCamera;	//카메라
	cMatrix m_matProjection;//프로젝션
	cMatrix m_matViewPort;  //뷰포트
	*/
	//전부 단위행렬벡터로 만들어버림
	//왜냐면 공식에 전부 단위행렬 벡터에 이상한 거 해가지고

	m_matLocal = cMatrix::Identity(4);
	m_matWorld = cMatrix::Identity(4);
	m_matCamera = cMatrix::Identity(4);
	m_matProjection = cMatrix::Identity(4);
	m_matViewPort = cMatrix::Identity(4);

	//정점
	m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
	m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
	m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
	m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));

	m_vecVertexNum.push_back(0);
	m_vecVertexNum.push_back(1);
	m_vecVertexNum.push_back(2);
	
	m_vecVertexNum.push_back(0);
	m_vecVertexNum.push_back(2);
	m_vecVertexNum.push_back(3);
	
	m_vecVertexNum.push_back(5);
	m_vecVertexNum.push_back(4);
	m_vecVertexNum.push_back(7);
	
	m_vecVertexNum.push_back(5);
	m_vecVertexNum.push_back(7);
	m_vecVertexNum.push_back(6);
	
	m_vecVertexNum.push_back(4);
	m_vecVertexNum.push_back(5);
	m_vecVertexNum.push_back(1);
	
	m_vecVertexNum.push_back(4);
	m_vecVertexNum.push_back(1);
	m_vecVertexNum.push_back(0);
	
	m_vecVertexNum.push_back(3);
	m_vecVertexNum.push_back(2);
	m_vecVertexNum.push_back(6);
	
	m_vecVertexNum.push_back(3);
	m_vecVertexNum.push_back(6);
	m_vecVertexNum.push_back(7);
	
	m_vecVertexNum.push_back(1);
	m_vecVertexNum.push_back(5);
	m_vecVertexNum.push_back(6);
	
	m_vecVertexNum.push_back(1);
	m_vecVertexNum.push_back(6);
	m_vecVertexNum.push_back(2);
	
	m_vecVertexNum.push_back(4);
	m_vecVertexNum.push_back(0);
	m_vecVertexNum.push_back(3);
	
	m_vecVertexNum.push_back(4);
	m_vecVertexNum.push_back(3);
	m_vecVertexNum.push_back(7);
	//번호
	/*
	{
		m_vecVertexNum.push_back(0);
		m_vecVertexNum.push_back(1);
		m_vecVertexNum.push_back(2);

		m_vecVertexNum.push_back(0);
		m_vecVertexNum.push_back(2);
		m_vecVertexNum.push_back(3);

		m_vecVertexNum.push_back(4);
		m_vecVertexNum.push_back(5);
		m_vecVertexNum.push_back(7);

		m_vecVertexNum.push_back(5);
		m_vecVertexNum.push_back(6);
		m_vecVertexNum.push_back(7);

	
		m_vecVertexNum.push_back(4);
		m_vecVertexNum.push_back(5);
		m_vecVertexNum.push_back(1);

		m_vecVertexNum.push_back(4);
		m_vecVertexNum.push_back(1);
		m_vecVertexNum.push_back(0);

		m_vecVertexNum.push_back(3);
		m_vecVertexNum.push_back(2);
		m_vecVertexNum.push_back(6);

		m_vecVertexNum.push_back(3);
		m_vecVertexNum.push_back(6);
		m_vecVertexNum.push_back(7);

		m_vecVertexNum.push_back(1);
		m_vecVertexNum.push_back(5);
		m_vecVertexNum.push_back(6);

		m_vecVertexNum.push_back(1);
		m_vecVertexNum.push_back(6);
		m_vecVertexNum.push_back(2);

		m_vecVertexNum.push_back(4);
		m_vecVertexNum.push_back(0);
		m_vecVertexNum.push_back(3);

		m_vecVertexNum.push_back(4);
		m_vecVertexNum.push_back(3);
		m_vecVertexNum.push_back(7); 
		
	}
*/

	//float f = 0.0f;
	//for (size_t i = 0; i < 10; i++)
	//{
	//	m_vecGrid.push_back(cVector3(-3.0f, 2.0f, -3.0f));
	//	m_vecGrid.push_back(cVector3(-3.0f, 2.0f, 3.0f));
	//	m_vecGrid.push_back(cVector3(3.0f, 2.0f, 3.0f));
	//	m_vecGrid.push_back(cVector3(3.0f, 2.0f, -3.0f));
	//}

		/*m_vecGrid.push_back(cVector3(-3.0f, 2.0f, -3.0f));
		m_vecGrid.push_back(cVector3(-3.0f, 2.0f, 3.0f));
		m_vecGrid.push_back(cVector3(3.0f, 2.0f, 3.0f));
		m_vecGrid.push_back(cVector3(3.0f, 2.0f, -3.0f));*/

	for (int i = 0; i < 11; i++)
	{
		m_vPlaneColUp[i] = cVector3(-5 + i, 1.5f, 5);
		m_vPlaneColDown[i] = cVector3(-5 + i, 1.5f, -5);
		m_vPlaneRowRight[i] = cVector3(5, 1.5f, 5 - i);
		m_vPlaneRowLeft[i] = cVector3(-5, 1.5f, 5 - i);
	}
	
		
/*
		m_vecGridPoint.push_back(0);
		m_vecGridPoint.push_back(1);
		m_vecGridPoint.push_back(2);
		m_vecGridPoint.push_back(3);
		*/


		for (size_t i = 0; i < m_vecGrid.size(); i++)
		{
			m_vecGridPoint.push_back(i);

		}

		for (int  i = 0; i < m_vecVertexNum.size(); i++)
		{
			m_vecIndexingCheck.push_back(i);
		}

		m_offset = m_vEye - m_vBoxPos;
}

void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//m_vLookAt = m_vBoxPos;
	//m_vEye = m_vEye + m_vBoxPos;

	//정육면체
	cMatrix matRX = cMatrix::RotationX(m_fBoxAngleX);
	cMatrix matRY = cMatrix::RotationY(m_fBoxAngleY);
	 matR = matRX * matRY;
	m_Dir = m_Dir.TransformNormal(matR);
	m_matWorld = cMatrix::Translation(m_vBoxPos);// * matR;
	//cVector3 Look = (m_vLookAt + m_vBoxPos);

	m_vLookAt = m_vBoxPos;
	m_vEye = m_vBoxPos + m_offset;
	cMatrix matTrans = cMatrix::Translation(0, 0, -m_fBoxHeel);
	cMatrix matCRX = cMatrix::RotationX(m_fCameraAngleX);
	cMatrix matCRY = cMatrix::RotationY(m_fCameraAngleY);
	cVector3 eyetemp = m_vEye - m_vLookAt;
	eyetemp = cVector3(0,0,0) * matTrans * matCRX * matCRY;
	//eyetemp = eyetemp + m_vLookAt;
	m_vEye = eyetemp + m_vLookAt;
	//cVector3 eyetemp = m_vEye - m_vLookAt;
	//eyetemp = eyetemp * matRY * matRX;
	//eyetemp = eyetemp + m_vLookAt;
	cVector3 Eye= (m_vEye );//+ m_vBoxPos
	m_matCamera = cMatrix::LookAtLH(Eye, m_vLookAt, m_vUp);
	//m_matProjection  투영을 관리함  어케보이는지
	m_matProjection = cMatrix::PerspectiveFovLH(PI / 4.0f,//m_fBoxHeel,
		(float)rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	//보이는거 보는 각도 등등을 바꿈
	m_matViewPort = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
	{
		//땅
		cMatrix matRXG = cMatrix::RotationX(m_fGroundAngleX);
		cMatrix matRYG = cMatrix::RotationY(m_fGroundAngleY);
		cMatrix matRG = matRXG * matRYG;

		m_matWorldG = cMatrix::Translation(m_vGroundPos) * matRG;
	}
	m_Dir = cVector3(0, 0, 1);
	cVector3 vv = m_Dir  * 0.05f * matR;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_vBoxPos += vv;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_vBoxPos = m_vBoxPos - vv;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_fBoxAngleY += 0.05f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_fBoxAngleY -= 0.05f;
	}
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;

	GetClientRect(g_hWnd, &rc);

	if (m_hMemDC == NULL)
	{
		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
		SetGraphicsMode(m_hMemDC, GM_ADVANCED);
	}

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_WINDOW));
	///////////////////////////////////////////////////////
	///////////////////↓↓↓↓ 그리기 ↓↓↓↓ ////////////////////
	///////////////////////////////////////////////////////

	//우리가 보기위해서 이 값들을 곱해줌
	//월드 * 카메라(뷰) * 투영 = 완벽한 우리세상
	cMatrix matPerfect = m_matWorld * m_matCamera * m_matProjection;
	cMatrix matPerfectG = m_matWorldG * m_matCamera * m_matProjection * m_matViewPort;
	

	cVector3 vpUp[11];
	cVector3 vpDown[11];
	cVector3 vpRight[11];
	cVector3 vpLeft[11];

	for (int i = 0; i < 11; i++)
	{
		


		vpUp[i] = m_vPlaneColUp[i] * matPerfectG;
		vpDown[i] = m_vPlaneColDown[i] * matPerfectG;
		vpLeft[i] = m_vPlaneRowLeft[i] * matPerfectG;
		vpRight[i] = m_vPlaneRowRight[i] * matPerfectG;


		MoveToEx(m_hMemDC, vpUp[i].x, vpUp[i].y, NULL);
		LineTo(m_hMemDC, vpDown[i].x, vpDown[i].y);
		MoveToEx(m_hMemDC, vpLeft[i].x, vpLeft[i].y, NULL);
		LineTo(m_hMemDC, vpRight[i].x, vpRight[i].y);

		if (i == 5)
		{
			string s = "";
			s = "z";
			TextOutA(m_hMemDC, vpUp[i].x, vpUp[i].y, s.c_str(), s.length());
			string ss = "";
			ss = "x";
			TextOutA(m_hMemDC, vpRight[i].x, vpRight[i].y, ss.c_str(), ss.length());

		}
	}


	//cVector3 v_G1 = m_vecGrid[m_vecGridPoint[0]];
	//cVector3 v_G2 = m_vecGrid[m_vecGridPoint[1]];
	//cVector3 v_G3 = m_vecGrid[m_vecGridPoint[2]];
	//cVector3 v_G4 = m_vecGrid[m_vecGridPoint[3]];

	//cVector3 v_G5 = m_vecGrid[m_vecGridPoint[4]];
	//cVector3 v_G6 = m_vecGrid[m_vecGridPoint[5]];
	//cVector3 v_G7 = m_vecGrid[m_vecGridPoint[6]];
	//cVector3 v_G8 = m_vecGrid[m_vecGridPoint[7]];

	//cVector3 v_G9 = m_vecGrid[m_vecGridPoint[8]];
	//cVector3 v_G10 = m_vecGrid[m_vecGridPoint[9]];
	//cVector3 v_G11 = m_vecGrid[m_vecGridPoint[10]];
	//cVector3 v_G12 = m_vecGrid[m_vecGridPoint[11]];

	//v_G1 = v_G1 * matPerfectG;
	//v_G2 = v_G2 * matPerfectG;
	//v_G3 = v_G3 * matPerfectG;
	//v_G4 = v_G4 * matPerfectG;

	//v_G5 = v_G5 * matPerfectG;
	//v_G6 = v_G6 * matPerfectG;
	//v_G7 = v_G7 * matPerfectG;
	//v_G8 = v_G8 * matPerfectG;

	//v_G9 = v_G9 * matPerfectG;
	//v_G10 = v_G10 * matPerfectG;
	//v_G11 = v_G11 * matPerfectG;
	//v_G12 = v_G12 * matPerfectG;

	//v_G1 = v_G1 * m_matViewPort;
	//v_G2 = v_G2 * m_matViewPort;
	//v_G3 = v_G3 * m_matViewPort;
	//v_G4 = v_G4 * m_matViewPort;


	//v_G5 = v_G5 * m_matViewPort;
	//v_G6 = v_G6 * m_matViewPort;
	//v_G7 = v_G7 * m_matViewPort;
	//v_G8 = v_G8 * m_matViewPort;

	//v_G9 = v_G9 * m_matViewPort;
	//v_G10 = v_G10 * m_matViewPort;
	//v_G11 = v_G11 * m_matViewPort;
	//v_G12 = v_G12 * m_matViewPort;

	//MoveToEx(m_hMemDC, v_G1.x, v_G1.y, NULL);
	//LineTo(m_hMemDC, v_G2.x, v_G2.y);
	//LineTo(m_hMemDC, v_G3.x, v_G3.y);
	//LineTo(m_hMemDC, v_G4.x, v_G4.y);
	//LineTo(m_hMemDC, v_G1.x, v_G1.y);
	


	//MoveToEx(m_hMemDC, v_G1.x, v_G1.y, NULL);
	//LineTo(m_hMemDC, v_G2.x, v_G2.y);
	//LineTo(m_hMemDC, v_G7.x, v_G7.y);
	//LineTo(m_hMemDC, v_G8.x, v_G8.y);
	//LineTo(m_hMemDC, v_G5.x, v_G5.y);

	//float fw = sqrt((v_G2.x - v_G1.x) * (v_G2.x - v_G1.x) 
	//	+ (v_G2.y - v_G1.y) * (v_G2.y - v_G1.y));


	for (size_t i = 0; i < m_vecVertexNum.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecVertexNum[i]];
		cVector3 v2 = m_vecVertex[m_vecVertexNum[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecVertexNum[i + 2]];

		v1 = v1 * matR;
		v2 = v2 * matR;
		v3 = v3 * matR;

		v1 = v1 * matPerfect;
		v2 = v2 * matPerfect;
		v3 = v3 * matPerfect;

		cVector3 vC1 = (v2 - v1).Normalize();
		cVector3 vC2 = (v3 - v1).Normalize();

	//	cVector3 vC2_1 = (m_vLookAt - m_vEye);

		cVector3 vTemp1 = cVector3::Cross(vC1, vC2);
		cVector3 vTemp2 = cVector3(0,0,1);
		float fTemp = cVector3::Dot(vTemp1, vTemp2);

		if (fTemp <= 0)
		{
			continue;
		}

		v1 = v1 * m_matViewPort;
		v2 = v2 * m_matViewPort;
		v3 = v3 * m_matViewPort;
		//2에서 1뺀 벡터 3에서 1뺸 벡터 크로스 
		//카메라가 상자를 바라보는 벡터 상자 - 카메라 위치  
		// 위 두개를 Dot  한다
		//양수가 나오면 contiue 안되면 음수

		



		MoveToEx(m_hMemDC, v1.x, v1.y, NULL);
		LineTo(m_hMemDC, v2.x, v2.y);
		LineTo(m_hMemDC, v3.x, v3.y);
		LineTo(m_hMemDC, v1.x, v1.y);
	}
	int a = 0;
	for (size_t i = 0; i < m_vecVertexNum.size(); i ++)
	{
		
		int iCopy1 = i;
		int iCopy2 = i + 1;
		int iCopy3 = i+ 2;
		if (iCopy3 == m_vecVertexNum.size())
		{
			break;
		}
		cVector3 v1 = m_vecVertex[m_vecVertexNum[i]];
		cVector3 v2 = m_vecVertex[m_vecVertexNum[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecVertexNum[i + 2]];

		v1 = v1 * matPerfect;
		v2 = v2 * matPerfect;
		v3 = v3 * matPerfect;

		v1 = v1 * m_matViewPort;
		v2 = v2 * m_matViewPort;
		v3 = v3 * m_matViewPort;

		/*string s = "";
		s = to_string((int)a);
		TextOutA(m_hMemDC, v1.x, v1.y, s.c_str(), s.length());*/
		
	}




	///////////////////////////////////////////////////////
	////////////////// ↑↑↑↑ 그리기 ↑↑↑↑ ////////////////////
	///////////////////////////////////////////////////////
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}

void cMainGame::OnSize()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLeftRotation = true;
		//왜인지모르겠는데 반대임 개념이
		//Mousept.y = (int)(short)HIWORD(lParam);
		Mousept.x = (int)(short)HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLeftRotation = false;
	}
	break;
	case WM_RBUTTONDOWN:
	{
		m_isRightRotation = true;
		Mousept.y = (int)(short)HIWORD(lParam);

		
	}
		break;
	case WM_RBUTTONUP:
	{
		m_isRightRotation = false;
	}
		break;
	case WM_MOUSEMOVE:
	{
		int x, y;
		/*x = (int)(short)LOWORD(lParam);
		y = (int)(short)HIWORD(lParam);*/
		y = (int)(short)LOWORD(lParam);
		x = (int)(short)HIWORD(lParam);
		if (m_isRightRotation == true)
		{
			if (x > Mousept.x)
			{
				m_fCameraAngleX += 0.05f;
			}
			else if(x < Mousept.x)
			{
				m_fCameraAngleX -= 0.05f;

			}
			//앵글제한
			if (m_fCameraAngleX <= -((PI / 2) - (PI / 90)))
			{
				m_fCameraAngleX = -((PI / 2) - (PI / 90));
			}
			else if (m_fCameraAngleX >= ((PI / 2) - (PI / 90)))
			{
				m_fCameraAngleX = ((PI / 2) - (PI / 90));
			}
			Mousept.x = x;

		}
		if (m_isLeftRotation == true)
		{
			if (y > Mousept.y)
			{
				m_fCameraAngleY += 0.05f;
			}
			else if (y < Mousept.y)
			{
				m_fCameraAngleY -= 0.05f;

			}
			Mousept.y = y;
		}
	}
		break;
	case WM_MOUSEWHEEL:
	{
		if ((SHORT)HIWORD(wParam) > 0)
			// 하고 싶은 동작 위로올릴때
		{
			if (m_fBoxHeel <= 6.0f)
			{
				break;
			}
			m_fBoxHeel -= 0.5f;
			

		}
		else
			// 하고 싶은 동작밑으로 내릴때
		{
			if (m_fBoxHeel >= 15.0f)
			{
				break;
			}
			m_fBoxHeel += 0.5f;
		}
	
	}
		break;
	case WM_KEYDOWN:
	{
		//switch (wParam)
		//{
		//case 'A':
		//{
		//	m_fBoxAngleY += 0.05f;
		//}
		//break;
		//case 'D':
		//{
		//	m_fBoxAngleY -= 0.05f;
		//}
		//break;
		//default:
		//	break;
		//}
		
	}
		break;
	}
}