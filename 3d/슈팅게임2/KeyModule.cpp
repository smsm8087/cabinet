#include "stdafx.h"
#include "KeyModule.h"


KeyModule::KeyModule() : PrevKey(0)
{
	ZeroMemory(keyDown, sizeof(keyDown));
}


KeyModule::~KeyModule()
{
}

bool KeyModule::isKeyDown(int keyCode)
{
	if (GetAsyncKeyState(keyCode) & 0x8000) {
		if (!keyDown[keyCode]) {
			keyDown[keyCode] = 0x01;
			return true;
		}
	}
	else keyDown[keyCode] = 0;

	return false;
}

bool KeyModule::StayKeyDown(int keyCode)
{
	if (GetAsyncKeyState(keyCode) & 0x8000) {
		PrevKey = keyCode;
		return true;
	}

	return false;
}

bool KeyModule::isKeyUp(int keyCode)
{
	if (!StayKeyDown(keyCode)) {
		if (PrevKey == keyCode) {
			PrevKey = 0;
			return true;
		}
	}
	return false;
}

bool KeyModule::ToggleKeyDown(int keyCode)
{
	if (GetKeyState(keyCode) & 0x0001)
		return true;
	return false;
}