#pragma once

class cButton;

//��ư�� �븮��
class iButtonDelegate
{
public:
	//���������Լ�
	virtual void OnClick(cButton* pSender) = 0;
};

class cButton
{
protected:
	//��ư�� ����
	enum eButtonState
	{
		E_NORMAL,			//�������ճ�
		E_MOUSEOVER,		//���콺����������
		E_CLICKED,			//���콺�� Ŭ���߳�
		E_STATE_COUNT		//����ī��Ʈ
	};

protected:
	
	char			m_szText[64];
	eButtonState	m_eButtonState;//�̳Ѻ���
	RECT			m_aStateRect[E_STATE_COUNT];	//����ī��Ʈ��ŭ�� ��Ʈ
	//�ټ¸�ũ�� (Ÿ�� , ������ , �Լ��̸�)
	GETSET(iButtonDelegate*, m_pDelegate, Delegate);
	GETSET(int, m_nTag, Tag);
	GETSETREF(RECT, m_rcArea, Area);

public:
	cButton();
	virtual ~cButton();

	void Init(RECT rc, const char* szText);
	void Update();
	void Render(HDC hdc);
	bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

