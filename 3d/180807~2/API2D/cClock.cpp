#include "stdafx.h"
#include "cClock.h"


cClock::cClock()
	: m_fRadius(0.0f)
	, m_fTextRadRatio(0.9f)
{
}


cClock::~cClock()
{
}

void cClock::Setup()
{
	system_clock::time_point now = system_clock::now();
	time_t tnow = system_clock::to_time_t(now);
	localtime_s(&m_stTime, &tnow);
	
	m_ptCenter.x = 0;
	m_ptCenter.y = 0;
}

void cClock::Update()
{
	system_clock::time_point now = system_clock::now();
	time_t tnow = system_clock::to_time_t(now);
	localtime_s(&m_stTime, &tnow);
}

void cClock::Render(HDC hdc)
{
	Rectangle(hdc, 110, 110, 190, 190);
	
	// 원 그리기
	Ellipse(hdc, 
		m_ptCenter.x - (int)m_fRadius,
		m_ptCenter.y - (int)m_fRadius,
		m_ptCenter.x + (int)m_fRadius,
		m_ptCenter.y + (int)m_fRadius);

	// 글자 그리기
	char szBuf[256];
	float fTextRadius = m_fRadius * m_fTextRadRatio;
	for (int i = 1; i <= 12; i++)
	{
		float fAngle = i * PI / 6.0f + PI * 3.0f / 2.0f;
		float x = fTextRadius * cosf(fAngle) + m_ptCenter.x;
		float y = fTextRadius * sinf(fAngle) + m_ptCenter.y;
		RECT rc;
		SetRect(&rc, (int)x - 10, (int)y - 10, (int)x + 10, (int)y + 10);
		wsprintf(szBuf, "%d", i);
		DrawText(hdc, szBuf, (int)strlen(szBuf), &rc, DT_CENTER | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);
	}

	// 초침
	float fAngle = m_stTime.tm_sec * PI / 30.0f + PI * 3.0f / 2.0f;
	RenderNeedle(hdc, fAngle, 0.9f);

	// 분침
	fAngle = m_stTime.tm_min * PI / 30.0f + 
		m_stTime.tm_sec * PI / 1800.0f +
		PI * 3.0f / 2.0f;
	RenderNeedle(hdc, fAngle, 0.8f);

	// 시침
	fAngle = m_stTime.tm_hour * PI / 6.0f + 
		m_stTime.tm_min * PI / 360.0f +
		PI * 3.0f / 2.0f;
	RenderNeedle(hdc, fAngle, 0.6f);
}

void cClock::OnSize()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (rc.right > rc.bottom)
	{
		m_fRadius = rc.bottom / 2.0f;
	}
	else
	{
		m_fRadius = rc.right / 2.0f;
	}
	m_ptCenter.x = rc.right / 2;
	m_ptCenter.y = rc.bottom / 2;
}

void cClock::RenderNeedle(HDC hdc, float fAngle, float fRadRatio)
{
	float fRadius = m_fRadius * fRadRatio;
	float x = fRadius * cosf(fAngle) + m_ptCenter.x;
	float y = fRadius * sinf(fAngle) + m_ptCenter.y;
	MoveToEx(hdc, m_ptCenter.x, m_ptCenter.y, NULL);
	LineTo(hdc, (int)x, (int)y);
}
