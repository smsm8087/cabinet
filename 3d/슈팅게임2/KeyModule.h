#pragma once
#include "SingletonBase.h"

class KeyModule : public SingletonBase<KeyModule>
{
public:
	byte keyDown[256];
	byte PrevKey;

public:
	KeyModule();
	~KeyModule();

	bool isKeyDown(int keyCode);
	bool StayKeyDown(int keyCode);
	bool isKeyUp(int keyCode);
	bool ToggleKeyDown(int keyCode);
};

