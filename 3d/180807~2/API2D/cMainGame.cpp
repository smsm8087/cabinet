#include "stdafx.h"
#include "cMainGame.h"
#include "cImage.h"
#include "cTile.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_ulGdiplusToken(0)
	, m_isLShift(false)
	, m_pImage(NULL)
	, m_vPlayer(500, 400)
	, m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	, mfAngle(0.0f)
{
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}

cMainGame::~cMainGame()
{
	for (auto p : m_vecTile)
	{
		SAFE_DELETE(p);
	}
	m_vecTile.clear();
	SAFE_RELEASE(m_pImage);

	g_pTimeManager->Destroy();

	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	
	assert(g_setObjectPool.empty() && "지워지지 않은 객체가 있음.");
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);
	
	for (size_t i = 0; i < TILE_V; i++)
	{
		for (size_t j = 0; j < TILE_H; j++)
		{
			cTile* pTile = new cTile(i, j, rand() % NUM_TILE_TYPE);
			m_vecTile.push_back(pTile);
		}
	}
	

	// 848 x 431
	cImage* pImage = cImage::Create("back.bmp");
	m_pImage = new cImage(ST_SIZE(300, 300));
	m_pImage->Render(pImage, ST_SIZE(300, 300));
	SAFE_RELEASE(pImage);

	for (auto p : m_vecTile)
	{
		p->m_nCheckDepth = 0;
		p->m_nTileType = rand() % NUM_TILE_TYPE;
	}
	for (auto p : m_vecTile)
	{
		p->CheckDelete(m_vecTile);
	}

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_vVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
	m_vVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
	m_vVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
	m_vVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));
	m_vVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
	m_vVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
	m_vVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
	m_vVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));

	m_vVertexIndex.push_back(0);
	m_vVertexIndex.push_back(1);
	m_vVertexIndex.push_back(2);
	
	m_vVertexIndex.push_back(0);
	m_vVertexIndex.push_back(2);
	m_vVertexIndex.push_back(3);
	
	m_vVertexIndex.push_back(4);
	m_vVertexIndex.push_back(6);
	m_vVertexIndex.push_back(5);
	
	m_vVertexIndex.push_back(4);
	m_vVertexIndex.push_back(7);
	m_vVertexIndex.push_back(6);
	
	m_vVertexIndex.push_back(4);
	m_vVertexIndex.push_back(5);
	m_vVertexIndex.push_back(1);
	
	m_vVertexIndex.push_back(4);
	m_vVertexIndex.push_back(1);
	m_vVertexIndex.push_back(0);
	
	m_vVertexIndex.push_back(3);
	m_vVertexIndex.push_back(2);
	m_vVertexIndex.push_back(6);
	
	m_vVertexIndex.push_back(3);
	m_vVertexIndex.push_back(6);
	m_vVertexIndex.push_back(7);
	
	m_vVertexIndex.push_back(1);
	m_vVertexIndex.push_back(5);
	m_vVertexIndex.push_back(6);
	
	m_vVertexIndex.push_back(1);
	m_vVertexIndex.push_back(6);
	m_vVertexIndex.push_back(2);
	
	m_vVertexIndex.push_back(4);
	m_vVertexIndex.push_back(0);
	m_vVertexIndex.push_back(3);

	m_vVertexIndex.push_back(4);
	m_vVertexIndex.push_back(3);
	m_vVertexIndex.push_back(7);

	//월드, 뷰, 프로젝션 셋팅
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);

}


void cMainGame::Update()
{
	g_pTimeManager->Update();

	for (auto p : m_vecTile)
	{
		p->Update();
	}

	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		m_isLShift = true;
	}
	else if (m_isLShift)
	{
		m_isLShift = false;
		MessageBoxA(g_hWnd,
			"A",
			0,
			0);
	}
	g_pAutoReleasePool->Drain();

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//cMatrix matRX = cMatrix::RotationX(m_vCamRotAngle.x);
	//cMatrix matRY = cMatrix::RotationY(m_vCamRotAngle.y);
	//cMatrix matR = matRX * matRY;
	//m_vEye = cVector3(0, 0, -m_fCameraDistance);
	//m_vEye = cVector3::TransformCoord(m_vEye, matR);
	mfAngle += g_pTimeManager->GetElapsedTime();


	m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition;


	cMatrix matRX = cMatrix::RotationY(mfAngle);
	cMatrix matR = matRX;
	cMatrix matT = cMatrix::Translation(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
	m_matView = cMatrix::LookAtLH(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::PerspectiveFovLH(PI / 4.0f,
		rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
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

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT/*COLOR_WINDOW*/));
	
	//POINT pt = cUtil::MakePoint(0, 0);
	//m_pImage->Render(m_hMemDC, pt, true);

	//cUtil::DrawCircle(m_hMemDC, 30, m_vPlayer.ToPoint());
	//
	//for (size_t i = 0; i < 3; i++)
	//{
	//	m_vBullet[i] = m_vBullet[i] + m_vBulletVel[i] * g_pTimeManager->GetElapsedTime();
	//	cUtil::DrawCircle(m_hMemDC, 5, m_vBullet[i].ToPoint());
	//}

	//스케일 로에티션 프로젝션 과정이 끝나면 월드가 됨
	//거기에 뷰와 프로젝션을 결합 (지금)
	cMatrix matWVP = m_matWorld * m_matView * m_matProj;

	//그뒤 투영함 (원근감이 있는 형태로 월드에 구현)
	for (size_t i = 0; i < m_vVertexIndex.size(); i += 3)
	{
		cVector3 v1 = m_vVertex[m_vVertexIndex[i]];
		cVector3 v2 = m_vVertex[m_vVertexIndex[i + 1]];
		cVector3 v3 = m_vVertex[m_vVertexIndex[i + 2]];

		//3개의 점을 공간으로 이동시킴, TransformCoord 이용
		//v1 = cVector3::TransformCoord(v1, matWVP);
		//v2 = cVector3::TransformCoord(v2, matWVP);
		//v3 = cVector3::TransformCoord(v3, matWVP);
		v1 = v1 * matWVP;
		v2 = v2 * matWVP;
		v3 = v3 * matWVP;
		//화면상에 출력할 좌표로 변환
		//v1 = cVector3::TransformCoord(v1, m_matViewport);
		//v2 = cVector3::TransformCoord(v2, m_matViewport);
		//v3 = cVector3::TransformCoord(v3, m_matViewport);
		v1 = v1 * m_matViewport;
		v2 = v2 * m_matViewport;
		v3 = v3 * m_matViewport;

		// :
		MoveToEx(m_hMemDC, v1.x, v1.y, NULL);
		LineTo(m_hMemDC, v2.x, v2.y);
		LineTo(m_hMemDC, v3.x, v3.y);
		LineTo(m_hMemDC, v1.x, v1.y);
	}

	/*
	for (auto p : m_vecTile)
	{
		p->Render(m_hMemDC);
	}
	*/

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
		UINT_PTR temp = wParam;
		temp = temp;
	}
		break;
	case WM_LBUTTONDOWN:
	{
		cVector2 vMouse(LOWORD(lParam), HIWORD(lParam));
		m_vBulletVel[0] = (vMouse - m_vPlayer).Normalize();
		float fAngle = atan2(m_vBulletVel[0].y, m_vBulletVel[0].x);
		m_vBulletVel[1].x = cosf(fAngle + PI / 6);
		m_vBulletVel[1].y = sinf(fAngle + PI / 6);
		m_vBulletVel[2].x = cosf(fAngle - PI / 6);
		m_vBulletVel[2].y = sinf(fAngle - PI / 6);
		for (size_t i = 0; i < 3; i++)
		{
			m_vBullet[i] = m_vPlayer;
			m_vBulletVel[i] = m_vBulletVel[i] * 300;
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
	}
	break;
	case WM_RBUTTONDOWN:
	{
		for (auto p : m_vecTile)
		{
			p->m_nCheckDepth = 0;
			p->m_nTileType = rand() % NUM_TILE_TYPE;
		}
		for (auto p : m_vecTile)
		{
			p->CheckDelete(m_vecTile);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
	}
	break;
	}
}


