#pragma once
#define		TILE_SQUARE	50
class cAirplane;
class cPlayer;
class cImage;
class cAstar;
class cMainGame
{
private:
	
private:
	HDC					m_hMemDC;					//�׸��⵵���� �ڵ�
	HBITMAP				m_hBitmap;					//������۸������� ��Ʈ���ڵ�
	HBITMAP				m_hOldBitmap;				//����
	cPlayer*			m_pPlayer;					//�÷��̾�Ŭ���� ����
	vector<cAirplane*>	m_vecEnemy;					//���������� ���� ����
	cImage*				m_bg;
	cAstar*				m_astar;

	///////���̽�Ÿ
	
	

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
	void OutMap(HDC hDest);
};

