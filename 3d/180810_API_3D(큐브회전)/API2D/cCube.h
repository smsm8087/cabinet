#pragma once
class cCube
{
private:
	vector<cVector3>	m_vecVertex;
	vector<DWORD>		m_vecIndex;
	cVector3			m_vPos; 
	cVector3			m_vDir;
	float				m_fSpeed;
	float				m_fAngle;

public:
	cCube();
	~cCube();

	void Update();
	void Render(HDC hdc);
	cVector3* GetPosition();
};

