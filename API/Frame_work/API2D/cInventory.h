#pragma once
class cButton;
class cImage;
class cInventory
{
protected:

	//�κ��丮â
	RECT rcInven;
	int invenwidth;
	int invenheight;

	//�޴�â
	RECT rcMenubar;
	//�޴��� �κ��丮���̸��巡�������� �κ��丮�� �����δ�.
	RECT moveinven;
	//������ ����,���α���
	int     m_width;
	int		m_height;
	//�ݱ��ư
	RECT rcExitbtn;
	cButton* m_exitbutton;
	//â�巡�׽� �Һ���  ��
	bool	isInvenmove;
	//���Ա���ü
	struct  Slot
	{
		RECT    rcSlot;
		int		m_nType;
		int     m_nDataNum;
		bool	isselected;
		bool	isdrawing;
	};
	//�̹���
	cImage*  m_pImage[5];
	RECT	 rcImage[5];
	RECT     rcTemp;
	bool	 ismoving;
	
public:
	cInventory();
	virtual ~cInventory();
	int   m_nCount[3];
	

	virtual void Init(int Width,int Height,itemType itemtype, int nData)=0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

