#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
	: m_vPos(0, 0, 0)
	, m_vDir(0, 0, 1)
	, m_fSpeed(3.0f)
	, m_fAngle(0.0f)
{
	m_vecVertex.push_back(cVector3(-1, -1, -1));
	m_vecVertex.push_back(cVector3(-1, 1, -1));
	m_vecVertex.push_back(cVector3(1, 1, -1));
	m_vecVertex.push_back(cVector3(1, -1, -1));
	m_vecVertex.push_back(cVector3(-1, -1, 1));
	m_vecVertex.push_back(cVector3(-1, 1, 1));
	m_vecVertex.push_back(cVector3(1, 1, 1));
	m_vecVertex.push_back(cVector3(1, -1, 1));

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
}

cCube::~cCube()
{
}

void cCube::Update()
{
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_vPos += m_vDir * m_fSpeed * g_pTimeManager->GetElapsedTime();
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		m_vPos -= m_vDir * m_fSpeed * g_pTimeManager->GetElapsedTime();
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.05f;
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		m_fAngle += 0.05f;
	}

	cMatrix matR = cMatrix::RotationY(m_fAngle);
	m_vDir = cVector3(0, 0, 1).TransformCoord(matR);
}

void cCube::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cMatrix matS = cMatrix::Scaling(0.167f, 0.167f , 0.167f);
	cMatrix matT = cMatrix::Translation(m_vPos.x, m_vPos.y, m_vPos.z);
	cMatrix matR = cMatrix::RotationY(m_fAngle);
	cMatrix matWorld = matS*matR * matT;
	cMatrix m = matWorld * g_matView * g_matProj;

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v0 = m_vecVertex[m_vecIndex[i]];
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 2]];

		v0 = v0.TransformCoord(m);
		v1 = v1.TransformCoord(m);
		v2 = v2.TransformCoord(m);

		cVector3 v01 = v1 - v0;
		cVector3 v02 = v2 - v0;
		cVector3 n = cVector3::Cross(v01, v02);
		if (cVector3::Dot(n, cVector3(0, 0, 1)) > 0)
			continue;

		
		v0 = v0.TransformCoord(g_matViewport);
		v1 = v1.TransformCoord(g_matViewport);
		v2 = v2.TransformCoord(g_matViewport);
		Point aTri[] = { 
			Point(v0.x, v0.y), 
			Point(v1.x, v1.y), 
			Point(v2.x, v2.y) 
		};
		Graphics g(hdc);
		SolidBrush b(Color::Yellow);
		g.FillPolygon(&b, aTri, 3);
		
		MoveToEx(hdc, v0.x, v0.y, NULL);
		LineTo(hdc, v1.x, v1.y);
		LineTo(hdc, v2.x, v2.y);
		LineTo(hdc, v0.x, v0.y);
		
	}
}

cVector3 * cCube::GetPosition()
{
	return &m_vPos;
}
