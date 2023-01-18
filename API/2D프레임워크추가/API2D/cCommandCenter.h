#pragma once
class cCommandCenter
{
private:
	
	POINT m_pt;
public:
	int m_nRadius;
	RECT    rc;
	bool	isSelected;
	cCommandCenter();
	~cCommandCenter();
	void Init();
	void Update();
	void Render(HDC hdc);

	POINT getm_pt() { return m_pt; }
	void  setm_pt(POINT pt) { m_pt = pt; }
};

