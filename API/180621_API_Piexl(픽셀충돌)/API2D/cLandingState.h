#pragma once

#include "iCrtState.h"

class cLandingState : public iCrtState
{
protected:
	SINGLETON(cLandingState);

public:
	// iCrtState override
	virtual void Update(cCrt* pCrt, const RECT& rcBox) override;
};

