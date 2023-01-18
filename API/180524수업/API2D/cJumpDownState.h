#pragma once

#include "iCrtState.h"

class cJumpDownState : public iCrtState
{
protected:
	SINGLETON(cJumpDownState);
public:
	// iCrtState override
	virtual void Update(cCrt* pCrt, const RECT& rcBox) override;
};

