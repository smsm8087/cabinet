#pragma once

#include "iAnimation.h"

class cCrt
{
protected:
	map<string, iAnimation*>	m_mapAnimation;
	string						m_sAnimName;

public:
	cCrt();
	virtual ~cCrt();

	void Update();
	void Render(HDC hdc, RECT rcDst);
};

