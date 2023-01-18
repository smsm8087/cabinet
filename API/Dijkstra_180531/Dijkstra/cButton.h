#pragma once
#include "iButtonDelegate.h"

enum ButtonState {
	IDLE,
	MOUSEON,
	CLICKED,
	STATE_SIZE
};

class cButton
{
private:
	ButtonState m_eState;
	int m_iType;
	char m_cStr[64];
	int m_iXSize;
	int m_iYSize;
	POINT m_PPos;
	RECT m_RButton[STATE_SIZE];
	iButtonDelegate* m_iDelegate;

public:
	cButton();
	~cButton();

	void Init(POINT pos, char* str, int type);
	void Update();
	void Render(HDC hdc);
	void SetDelegate(iButtonDelegate* delegate);
	iButtonDelegate* GetDelegate();
};

