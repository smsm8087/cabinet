#pragma once
class cAddCircle
{
private:
	int					m_nfRadius;//������
	float					x;
	float					y;
	int					m_num;
	
public:
	
	
	cAddCircle();
	~cAddCircle();
	void Init();									//�ʱ�ȭ
	void Update();									//������Ʈ
	void Render(HDC hdc, float _x, float _y);
	void setpointx(float _x) { x = _x; }
	float getpointx() { return x; }
	void setpointy(float _y) { y = _y; }
	float getpointy() { return y; }
	void setnum(int _num) {m_num = _num; }
	int getnum() { return m_num; }
	float getRadius() { return m_nfRadius; }

};

