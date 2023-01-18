#pragma once

#include "iCrtState.h"

class cJumpUpState : public iCrtState
{
protected:
	SINGLETON(cJumpUpState);

public:
	// iCrtState override
	virtual void Update(cCrt* pCrt, const RECT& rcBox) override;
};

