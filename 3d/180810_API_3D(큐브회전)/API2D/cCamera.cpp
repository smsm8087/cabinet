#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye(0, 10.0f, 0.0f)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 0, 1)
	, m_pvTarget(NULL)
	, m_isLButtonDown(false)
	, m_fAngleY(0.0f)
	, m_fAngleX(0.0f)
	, m_fDist(10.0f)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


cCamera::~cCamera()
{
}

void cCamera::SetTarget(cVector3 * pvTarget)
{
	m_pvTarget = pvTarget;
}

void cCamera::Update()
{
	m_vEye = cVector3(0, 5, 0);
	m_vLookAt = cVector3(0, 0, 0);
	
	cMatrix matRX = cMatrix::RotationX(m_fAngleX);
	cMatrix matRY = cMatrix::RotationY(m_fAngleY);
	cMatrix matR = matRX * matRY;
	m_vEye = m_vEye.TransformCoord(matR);

	if (m_pvTarget)
	{
		m_vEye += *m_pvTarget;
		m_vLookAt += *m_pvTarget;
	}

	g_matView = cMatrix::LookAtLH(m_vEye, m_vLookAt, m_vUp);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (!m_isLButtonDown) return;
		POINT ptMouse;
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		
		POINT ptDelta;
		ptDelta.x = ptMouse.x - m_ptPrevMouse.x;
		ptDelta.y = ptMouse.y - m_ptPrevMouse.y;

		m_fAngleX += ptDelta.y / 100.0f;
		m_fAngleY += ptDelta.x / 100.0f;

		if (m_fAngleX >= PI / 2.0f)
			m_fAngleX = PI / 2.0f - EPSILON;
		if (m_fAngleX <= -PI / 2.0f)
			m_fAngleX = -PI / 2.0f + EPSILON;
		m_ptPrevMouse = ptMouse;
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLButtonDown = false;
	}
	break;
	case WM_MOUSEWHEEL:
	{
		int nDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		m_fDist -= nDelta / 120.0f;
		if (m_fDist < 1.414)
			m_fDist = 1.414;
	}
	break;
	}
}

