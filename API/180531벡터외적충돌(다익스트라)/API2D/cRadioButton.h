#pragma once
//�븮�� : delegate
class cRadioButton;

class iRadioButtonDelegate
{
public:
	//���������Լ� ��ӹ��� Ŭ�������� ���Լ��� ���������� ����������. ������Ҷ� �𸣰�Ѿ�°� �����ϱ����� ��

	//���õȰ����� �ٲ۴�
	virtual void OnSelectedItemChange(cRadioButton* pSender) = 0;
};

class cRadioButton
{
private:
	vector<string>	m_vecText;//��ư�� �̸�����
	RECT			m_rcArea;//��ư�� ���� �簢��
	//�ټ¸�ũ�� (Ÿ�� , ������ , �Լ��̸�)
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

