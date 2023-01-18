#pragma once
#include"cInventory.h"
class cMyAccount : public cInventory
{
protected:
	typedef struct Slot  Account;

	//PŰ������ ��â������
	
	bool   isenteraccount;
	Account* account;
	vector<Account*> m_vecAccount;
public:
	cMyAccount();
	
	virtual ~cMyAccount() override;

	virtual void Init(int Width, int Height, itemType itemtype, int nData) override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

