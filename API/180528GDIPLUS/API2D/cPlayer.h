#pragma once
#include "cAirplane.h"

class cPlayer : public cAirplane
{
public:
	cPlayer();
	~cPlayer();

	virtual void Update() override;
};

