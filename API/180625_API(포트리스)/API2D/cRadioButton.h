#pragma once

class cRadioButton;

class iRadioButtonDelegate
{
public:
	virtual void OnSelectedItemChange(cRadioButton* pSender) = 0;
};

class cRadioButton
{
private:
	vector<string>	m_vecText;
	RECT			m_rcArea;

	GETSET(int, m_nSelectedItem, SelectedItem);
	GETSET(iRadioButtonDelegate*, m_pDelegate, Delegate);
public:
	cRadioButton();
	~cRadioButton();

	void Init(RECT rc);
	void Update();
	void Render(HDC hdc);
	void AddItem(string s);

	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

