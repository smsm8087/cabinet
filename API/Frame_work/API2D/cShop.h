#pragma once
#include "cInventory.h"


class cShop : public cInventory
{
protected :
	typedef struct Slot  Shop;
	//S키누를시 상점입장
	Shop *shp;
	vector<Shop*> m_vecShop;
	GET(bool, isentershop, entershop);
public:
	cShop();
	virtual~cShop() override;
	
	
	virtual void Init(int Width, int Height, itemType itemtype, int nData) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

