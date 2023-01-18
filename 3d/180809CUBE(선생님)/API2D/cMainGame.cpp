#include "stdafx.h"
#include "cMainGame.h"
#include "cMatrix.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_eyecameraAngle(0.0f)
	, m_fPlaneAngle(0.0f)
	, m_vEye(0, 2, -7)
{
}

cMainGame::~cMainGame()
{
	g_pTimeManager->Destroy();

	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	
	assert(g_setObjectPool.empty() && "지워지지 않은 객체가 있음.");
}

void cMainGame::Init()
{
	Mousept.x = 0;
	Mousept.y = 0;
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);
	
	m_vecVertex.push_back(cVector3(-1, -1, -1));
	m_vecVertex.push_back(cVector3(-1,  1, -1));
	m_vecVertex.push_back(cVector3( 1,  1, -1));
	m_vecVertex.push_back(cVector3( 1, -1, -1));
	m_vecVertex.push_back(cVector3(-1, -1,  1));
	m_vecVertex.push_back(cVector3(-1,  1,  1));
	m_vecVertex.push_back(cVector3( 1,  1,  1));
	m_vecVertex.push_back(cVector3( 1, -1,  1));

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_fAngle = 0.0f;
	
	m_fSee = 4.0f;
	m_vCubePosition = cVector3(0, 0, 0);
	mDir = cVector3(0, 0, 1);
	m_vLook = cVector3(0, 0, 0);
	m_eyecameraAngleSujik = 0.f;

	for (int i = 0; i < 11; i++)
	{
		m_vPlaneColUp[i] = cVector3(-5 + i, -2, 5);
		m_vPlaneColDown[i] = cVector3(-5 + i, -2, -5);
		m_vPlaneRowRight[i] = cVector3(5, -2, 5-i);
		m_vPlaneRowLeft[i] = cVector3(-5 , -2, 5-i);
	}
	
	//m = cMatrix::Identity(4);
}


void cMainGame::Update()
{
	g_pTimeManager->Update();

	g_pAutoReleasePool->Drain();

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.05f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_fAngle += 0.05f;
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

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_BACKGROUND));

	mDir = cVector3(0, 0,1);
	cMatrix matS = cMatrix::Scaling(1, 1, 1);
	cMatrix	matR = cMatrix::RotationY(m_fAngle);
	mDir = mDir.TransformNormal(matR);
	//cMatrix matRPlane = cMatrix::RotationY(m_fAngle);

	cMatrix matT = cMatrix::Translation(m_vCubePosition.x, m_vCubePosition.y, m_vCubePosition.z);

	m_vLook = m_vCubePosition;
	cMatrix matWorld = matS * matR*matT;
	cMatrix a = cMatrix::RotationY(m_fCameraAngleY);
	cMatrix b = cMatrix::RotationX(m_fCameraAngleX);
	cMatrix  mm = b*a;
	tempeye = m_vEye;
	tempeye = tempeye.TransformCoord(mm);
	tempeye = tempeye + m_vCubePosition;
	cMatrix matView = cMatrix::LookAtLH(tempeye, m_vCubePosition, cVector3(0, 1, 0));


	cMatrix matProj = cMatrix::PerspectiveFovLH(PI / m_fSee, rc.right / (float)rc.bottom, 1, 1000);


	cMatrix matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);


	cMatrix m = matWorld * matView * matProj * matViewport;
	cMatrix mPlane = matView*matProj* matViewport;

	SetBkMode(m_hMemDC, TRANSPARENT);   //글씨 배경 없애기.
	SetTextColor(m_hMemDC, RGB(0, 255, 0));
	HPEN myPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(m_hMemDC, myPen);
	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v0 = m_vecVertex[m_vecIndex[i]];
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 2]];
		
		v0 = v0.TransformCoord(m);
		v1 = v1.TransformCoord(m);
		v2 = v2.TransformCoord(m);

		//후면추려내기
		cVector3 vC1 = (v1 - v0).Normalize();
		cVector3 vC2 = (v2 - v0).Normalize();


		cVector3 vTemp1 = cVector3::Cross(vC1, vC2);
		cVector3 vTemp2 = cVector3(0, 0, 1);
		float fTemp = cVector3::Dot(vTemp1, vTemp2);

		if (fTemp <= 0)
		{
			continue;
		}

		

		MoveToEx(m_hMemDC, v0.x, v0.y, NULL);
		LineTo(m_hMemDC, v1.x, v1.y);
		LineTo(m_hMemDC, v2.x, v2.y);
		LineTo(m_hMemDC, v0.x, v0.y);
	}
	cVector3 vpUp[11];
	cVector3 vpDown[11];
	cVector3 vpRight[11];
	cVector3 vpLeft[11];

	

	for (int i = 0; i < 11; i++)
	{
		vpUp[i] = m_vPlaneColUp[i].TransformCoord(mPlane);
		vpDown[i] = m_vPlaneColDown[i].TransformCoord(mPlane);
		vpLeft[i] = m_vPlaneRowLeft[i].TransformCoord(mPlane);
		vpRight[i] = m_vPlaneRowRight[i].TransformCoord(mPlane);

		MoveToEx(m_hMemDC, vpUp[i].x , vpUp[i].y , NULL);
		LineTo(m_hMemDC, vpDown[i].x , vpDown[i].y );
		MoveToEx(m_hMemDC, vpLeft[i].x, vpLeft[i].y, NULL);
		LineTo(m_hMemDC, vpRight[i].x, vpRight[i].y);
	}
	TextOut(m_hMemDC, vpUp[5].x, vpUp[5].y, "Z", strlen("Z"));
	TextOut(m_hMemDC, vpRight[5].x, vpRight[5].y, "X", strlen("X"));
	SelectObject(m_hMemDC, oldPen);
	DeleteObject(myPen);
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_vCubePosition += mDir * 10 * g_pTimeManager->GetElapsedTime();
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_vCubePosition -= mDir * 10 * g_pTimeManager->GetElapsedTime();
	}
	
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
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
			
		default:
			break;
		}
	}
		break;
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
			else if (x < Mousept.x)
			{
				m_fCameraAngleX -= 0.05f;

			}
			//앵글제한
			if (m_fCameraAngleX <=-PI/3)
			{
				m_fCameraAngleX = -PI / 3;
			}
			else if (m_fCameraAngleX >= PI / 3 )
			{
				m_fCameraAngleX = PI /3;
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
			if (m_fSee > 6.0f)
			{
				m_fSee = 6.0f;
			}
			m_fSee += 0.1f;
		}
		else
			// 하고 싶은 동작밑으로 내릴때
		{
			if (m_fSee < 2.f)
			{
				m_fSee = 2.f;
			}
			m_fSee -= 0.1f;
		}
	}break;
	
	break;
	}
}


