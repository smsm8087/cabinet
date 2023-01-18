#pragma once

class cCrt;

class iCrtState
{
public:
	virtual void Update(cCrt* pCrt, const RECT& rcBox) = 0;
};

