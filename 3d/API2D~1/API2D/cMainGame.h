#pragma once

class cMapImage;
class cCharacterImage;
class cInventory;

class cMainGame
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	vector<cPoint2N>	m_vecPoint;
	vector<cPoint2N>	m_vecOutlinePoint;

	cMapImage*  m_pMapImage;	//�� Ŭ����
	cMapImage*	m_pMapForest;
	cCharacterImage * m_pCharImage; //ĳ����Ŭ����
	cInventory* m_pInventory_item;		//�κ��丮
	cInventory* m_pInventory_book;		//����

	int x = 0;
	int y = 0;

	bool m_inventf;
	int count = 0;
	int CurrMenu; //���� �޴�
	int LastMenu; //�������޴�(�ٲ�� �� �޴��� ��������)
	int BeforeMenu;


public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	///////////////////////////////////////////////////////////////////////
	void CharMove();
	void InvenToryBit();
};

