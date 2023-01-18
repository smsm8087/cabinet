#pragma once

#include "cImage.h"

class cUIObject
{
protected:
	cUIObject*	m_pParent;
	cUIObject*	m_pFirstChild;
	cUIObject*	m_pSibling;
	
	POINT		m_ptScreen;
	bool		m_isDebugMode;
	
	GETSET(int, m_nDepth, Depth);
	GETSET(ST_SIZE, m_stSize, Size);
	GETSET(bool, m_isShow, Show);
	GETSET(int, m_nTag, Tag);
	GETSET(POINT, m_ptPosition, Position); // 부모로 부터 상대적인 위치
	GETSET_ADDREF(cImage*, m_pImage, Image);

public:
	cUIObject();
	virtual ~cUIObject();

	virtual void Init(ST_SIZE stSize);
	virtual void AddChild(cUIObject* pChild);
	virtual void Update(POINT* pParent);
	virtual void Render(HDC hdc);
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual ST_SIZE GetImageSize();
	virtual void ToggleShow();
	virtual void SetDebugMode(bool isDebugMode);
	virtual cUIObject* GetUIObject(int nTag);
	virtual cUIObject* GetRootUIObject();
	virtual void UIAtPoint(list<cUIObject*>& lst, POINT pt);
	virtual cUIObject* RemoveFirstChild();
	virtual cUIObject* RemoveChild(cUIObject* pChild, cUIObject** ppThis);

private:
	virtual void Destroy();
	virtual void AddSibling(cUIObject* pSibling, cUIObject** ppThis);
};

