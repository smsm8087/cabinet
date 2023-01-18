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

	cMapImage*  m_pMapImage;	//맵 클래스
	cMapImage*	m_pMapForest;
	cCharacterImage * m_pCharImage; //캐릭터클래스
	cInventory* m_pInventory_item;		//인벤토리
	cInventory* m_pInventory_book;		//도감

	int x = 0;
	int y = 0;

	bool m_inventf;
	int count = 0;
	int CurrMenu; //현재 메뉴
	int LastMenu; //마지막메뉴(바뀌기 전 메뉴가 무엇인지)
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

