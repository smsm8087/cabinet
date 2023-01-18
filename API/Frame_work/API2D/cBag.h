#pragma once
#include "cInventory.h"
class cBag : public cInventory
{
protected:
	typedef struct Slot  Bag;

	//i키누를시 내가방입장
	
	bool   isenterbag;
	Bag*  bag;
	vector<Bag*> m_vecBag;

	//
	int		m_row;
	int		m_col;
public:
	cBag();
	virtual~cBag() override;

	virtual void Init(int Width, int Height, itemType itemtype, int nData) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

