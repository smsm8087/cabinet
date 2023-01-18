#pragma once

class cAirplane;
class cPlayer;
class cCharater;


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
	int					a;							//���ӵ�
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
	BOOL				isjumping;				//�������ΰ� �����߿� ���������ϰ��� �Һ���
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

