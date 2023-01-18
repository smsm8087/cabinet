#pragma once
//대리자 : delegate
class cRadioButton;

class iRadioButtonDelegate
{
public:
	//순수가상함수 상속받은 클래스에서 이함수를 쓰지않으면 오류가난다. 디버깅할때 모르고넘어가는걸 방지하기위한 것

	//선택된것으로 바꾼다
	virtual void OnSelectedItemChange(cRadioButton* pSender) = 0;
};

class cRadioButton
{
private:
	vector<string>	m_vecText;//버튼의 이름벡터
	RECT			m_rcArea;//버튼의 범위 사각형
	//겟셋매크로 (타입 , 변수명 , 함수이름)
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

