#pragma once

class cAirplane;
class cPlayer;
class cImage;

class cMainGame
{
private:
	HDC					m_hMemDC;					//�׸��⵵���� �ڵ�
	HBITMAP				m_hBitmap;					//������۸������� ��Ʈ���ڵ�
	HBITMAP				m_hOldBitmap;				//����
	cPlayer*			m_pPlayer;					//�÷��̾�Ŭ���� ����
	vector<cAirplane*>	m_vecEnemy;					//���������� ���� ����
	cImage*				m_bg;
	FILE*				fp;							
	//////////////////////////Astar

	int					m_nRow;						//��
	int					m_nCol;						//��
	int					tilesize;					//Ÿ�ϻ�����
	RECT				rcMap;						//�ʻ簢��
	RECT				rcWall;						//���� �簢��
	RECT				rcStart;					//��ŸƮ����
	RECT				rcDest;						//��������
	bool				isDrawStart;				//��ŸƮ�������׷��ߵǳ�
	bool				isleftbtn;					//���ʹ�ư�� ���ȳ�
	POINT				ptStart;					//�����ǥ
	POINT				ptDest;						//������ǥ
	vector<POINT>		m_vecptWall;				//������
	POINT				ptWall;
	///////////////////////////

	vector<TILE*> m_vecTile;
	POINT unit;
	POINT mouseDest;
	int m_Direct;
	float Speed;
	bool isMove;
public:
	bool PathTrace(POINT start, POINT dest);
	void _resultH(POINT dest);
	void _initialize();
public:
	HRESULT Initialize();
	void Render();
	
	

	//////////////////////

public:
	cMainGame();
	~cMainGame();

	void Init();									//�ʱ�ȭ
	void Update();									//������Ʈ
	void Render(HDC hdc);							//������
	void OnSize();									//������ũ�Ⱑ�ٲ�� ���� �̹����鵵 ũ�Ⱑ �ٲ�
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//Ŭ���������� �׸����ְ� �������Լ� ������

	void InitStage(int nStage);						//���������� �ʱ�ȭ
	void ClearEnemy();								//������� �����
	bool CheckCollision(cAirplane* pAirplane);		//���������� �÷��̾�������� �ߺ��� �����ϱ����� �浹�Լ�
	
};

