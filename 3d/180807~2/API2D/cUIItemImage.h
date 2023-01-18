#pragma once

#include "cUIObject.h"

class cUIItemImage : public cUIObject
{
protected:
	bool	m_isPicked;
	POINT	m_ptPickPosition;
	POINT	m_ptMouse;
	bool	m_isAttatchToMouse;

public:
	cUIItemImage();
	virtual ~cUIItemImage();

	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

