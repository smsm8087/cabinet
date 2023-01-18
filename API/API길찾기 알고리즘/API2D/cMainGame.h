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
	HDC					m_hMemDC;					//그리기도구들 핸들
	HBITMAP				m_hBitmap;					//더블버퍼링을위한 비트맵핸들
	HBITMAP				m_hOldBitmap;				//같음
	cPlayer*			m_pPlayer;					//플레이어클래스 생성
	vector<cAirplane*>	m_vecEnemy;					//적비행기들의 집합 생성
	RECT				m_rc;						//바닥 rc
	RECT				m_playerrc;					//플레이어rc
	RECT				m_enemyrc;					//충돌할 곳
	POINT				pt;							//플레이어사각형의 위치좌표
	//int					a;							//가속도
	int					radius;						//사각형 지름
	POINT				e_pt;						//발판 위치좌표
	int speed = 0;				//플레이어이동
	BOOL				idle;						//플레이어가 가만히있는상태인가
	int gravity = 1;
	int jump = 0;
	HBITMAP				m_bitmap,m_oldbit;					//이미지불러오기
	float				m_fScale, m_fx, m_fy;
	cCharater*			ch;						//마리오
	cCharater*			ch1;					//배경화면
	cCharater*			ch2;					//배경화면
	cAddCircle*			cr;
	int					num;
	
	vector<cAddCircle*>  v_cr;					//원 벡터
	vector<cAddCircle*>::iterator  v_iter;
	cAddLine*			cal;
	vector <cAddLine*>			v_cal;			//선 벡터
	
	int					r1, g1, b1 = 0;			//rgb값
	int					r2, g2, b2 = 0;			//rgb값
	int					r3, g3, b3 = 0;			//rgb값
	FILE*				fp;
	float					x, y = 0;
	float					a, b = 0;
	RECT				rcbother;

	//장애물
	cObstacle*			obstacle;				
	vector<cObstacle*>  v_ob;	
	vector<cObstacle*>::iterator v_iob;
	BOOL				isobstacle;   //장애물그릴때렌더
	BOOL				iscollision;  //장애물이 선이랑 충돌했냐
	
	BOOL				iscircle;				//원을그리냐
	BOOL				incircle;				//원안에 있냐
	BOOL				incircleline;			//원안에 마우스가있냐
	BOOL				iscircleline;
	
	
	//쉬프트가 눌렸냐
	BOOL				isShift;
public:
	cMainGame();
	~cMainGame();

	void Init();									//초기화
	void Update();									//업데이트
	void Render(HDC hdc);							//렌더링
	void OnSize();									//윈도우크기가바뀌면 따라서 이미지들도 크기가 바뀜
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);//클래스에서도 그릴수있게 윈도우함수 가져옴

	void InitStage(int nStage);						//스테이지를 초기화
	void ClearEnemy();								//모든적군 지우기
	//bool CheckCollision(cAirplane* pAirplane);		//적군생성시 플레이어비행기와의 중복을 방지하기위한 충돌함수
	/*void CharacterInit(float _x, float _y, float _size);*/
	
};

