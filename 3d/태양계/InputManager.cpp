#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	//1 : �ѹ� ������ ����
	//0 : �ٽ� ������ 0����
	//128 : 0�����϶� �ش�Ű�� ������ ����
	//129 : 1�����϶� �ش�Ű�� ������ ����
	GetKeyboardState(keyState);

	for (int i = 0; i < MAXKEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1)
		{
			keyMap[i] = KEY_DOWN;
		}
		else if (oldState == 1 && state == 0)
		{
			keyMap[i] = KEY_UP;
		}
		else if (oldState == 1 && state == 1)
		{
			keyMap[i] = KEY_PRESS;
		}
		else
		{
			keyMap[i] = KEY_NONE;
		}
	}
}
