#pragma once
class cClock
{
private:
	tm		m_stTime;
	float	m_fRadius;
	float	m_fTextRadRatio;
	POINT	m_ptCenter;

public:
	cClock();
	~cClock();

	void Setup();
	void Update();
	void Render(HDC hdc);
	void OnSize();

	void RenderNeedle(HDC hdc, float fAngle, float fRadRatio);
};

