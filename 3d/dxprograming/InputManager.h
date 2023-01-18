#pragma once

#define	MAXKEY 255
class InputManager
{
private:
	byte keyState[MAXKEY];
	byte keyOldState[MAXKEY];
	byte keyMap[MAXKEY];

	enum
	{
		KEY_NONE,
		KEY_DOWN,
		KEY_UP,
		KEY_PRESS
	};

	InputManager();
	~InputManager();
public:
	static	InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}

	void Update();
	
	bool KeyDown(DWORD key)
	{
		return keyMap[key] == KEY_DOWN;
	}
	bool KeyUp(DWORD key)
	{
		return keyMap[key] == KEY_UP;
	}
	bool KeyPress(DWORD key)
	{
		return keyMap[key] == KEY_PRESS;
	}
};

