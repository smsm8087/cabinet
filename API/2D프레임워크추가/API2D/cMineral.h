#pragma once
class cMineral
{
private:
	
	POINT		m_pt;
	
public:
	int			m_nRadius;
	RECT		rc;
	bool		isSelected;
	bool		isImpossible;
	int			m_num;
	cMineral();
	~cMineral();
	void Init();
	void Update();
	void Render(HDC hdc);
	int   getm_Radius() { return m_nRadius; }
	POINT getm_pt() { return m_pt; }
	void  setm_pt(POINT pt) { m_pt = pt; }
};

