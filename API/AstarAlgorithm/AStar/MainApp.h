#pragma once

#include "Defines.h"

class CMainApp
{
private:
	HDC m_hdc;
	vector<TILE*> m_vecTile;
	POINT unit;
	POINT mouseDest;
	int m_Direct;
	float Speed;
	bool isMove;
public:
	bool PathTrace(POINT start, POINT dest);
	void _resultH(POINT dest);
	void _initialize();
public:
	HRESULT Initialize();
	int Progress();
	void Render();
	void Release();
public:
	CMainApp(void);
	~CMainApp(void);
};

