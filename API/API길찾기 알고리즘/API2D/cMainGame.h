#pragma once

class cAirplane;
class cPlayer;
class cCharater;
class cAddCircle;
class cAddLine;
class cObstacle;
class cMainGame
{
private:
	HDC					m_hMemDC;					//�׸��⵵���� �ڵ�
	HBITMAP				m_hBitmap;					//������۸������� ��Ʈ���ڵ�
	HBITMAP				m_hOldBitmap;				//����
	cPlayer*			m_pPlayer;					//�÷��̾�Ŭ���� ����
	vector<cAirplane*>	m_vecEnemy;					//���������� ���� ����
	RECT				m_rc;						//�ٴ� rc
	RECT				m_playerrc;					//�÷��̾�rc
	RECT				m_enemyrc;					//�浹�� ��
	POINT				pt;							//�÷��̾�簢���� ��ġ��ǥ
	//int					a;							//���ӵ�
	int					radius;						//�簢�� ����
	POINT				e_pt;						//���� ��ġ��ǥ
	int speed = 0;				//�÷��̾��̵�
	BOOL				idle;						//�÷��̾ �������ִ»����ΰ�
	int gravity = 1;
	int jump = 0;
	HBITMAP				m_bitmap,m_oldbit;					//�̹����ҷ�����
	float				m_fScale, m_fx, m_fy;
	cCharater*			ch;						//������
	cCharater*			ch1;					//���ȭ��
	cCharater*			ch2;					//���ȭ��
	cAddCircle*			cr;
	int					num;
	
	vector<cAddCircle*>  v_cr;					//�� ����
	vector<cAddCircle*>::iterator  v_iter;
	cAddLine*			cal;
	vector <cAddLine*>			v_cal;			//�� ����
	
	int					r1, g1, b1 = 0;			//rgb��
	int					r2, g2, b2 = 0;			//rgb��
	int					r3, g3, b3 = 0;			//rgb��
	FILE*				fp;
	float					x, y = 0;
	float					a, b = 0;
	RECT				rcbother;

	//��ֹ�
	cObstacle*			obstacle;				
	vector<cObstacle*>  v_ob;	
	vector<cObstacle*>::iterator v_iob;
	BOOL				isobstacle;   //��ֹ��׸�������
	BOOL				iscollision;  //��ֹ��� ���̶� �浹�߳�
	
	BOOL				iscircle;				//�����׸���
	BOOL				incircle;				//���ȿ� �ֳ�
	BOOL				incircleline;			//���ȿ� ���콺���ֳ�
	BOOL				iscircleline;
	
	
	//����Ʈ�� ���ȳ�
	BOOL				isShift;
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
	//bool CheckCollision(cAirplane* pAirplane);		//���������� �÷��̾�������� �ߺ��� �����ϱ����� �浹�Լ�
	/*void CharacterInit(float _x, float _y, float _size);*/
	
};

