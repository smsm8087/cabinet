#pragma once
class CObj
{
	struct Info
	{ float x, y; };
private:
	Info m_tInfo;
public:
	HRESULT Initialize();
	int Progress();
	void Render();
	void Release();
public:
	CObj(void);
	~CObj(void);
};

