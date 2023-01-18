#pragma once
class cButton;
class cImage;
class cInventory
{
protected:

	//인벤토리창
	RECT rcInven;
	int invenwidth;
	int invenheight;

	//메뉴창
	RECT rcMenubar;
	//메뉴와 인벤토리사이를드래그했을때 인벤토리가 움직인다.
	RECT moveinven;
	//슬롯의 가로,세로길이
	int     m_width;
	int		m_height;
	//닫기버튼
	RECT rcExitbtn;
	cButton* m_exitbutton;
	//창드래그시 불변수  참
	bool	isInvenmove;
	//슬롯구조체
	struct  Slot
	{
		RECT    rcSlot;
		int		m_nType;
		int     m_nDataNum;
		bool	isselected;
		bool	isdrawing;
	};
	//이미지
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

