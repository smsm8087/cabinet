#pragma once
class cScv
{
private:
	
	cVector2 v_pt;

public:
	int		m_nRadius;
	RECT	rc;
	int		m_nmineral;
	bool	isSelected;
	cScv();
	~cScv();
	void Init();
	void Update();
	void Render(HDC hdc);
	int   getm_Radius() { return m_nRadius; }
	cVector2 getm_pt() { return v_pt; }
	void  setm_pt(cVector2 pt) { v_pt = pt; }
	
	
};

