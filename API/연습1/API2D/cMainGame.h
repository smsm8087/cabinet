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
	HDC					m_hMemDC;					//그리기도구들 핸들
	HBITMAP				m_hBitmap;					//더블버퍼링을위한 비트맵핸들
	HBITMAP				m_hOldBitmap;				//같음
	cPlayer*			m_pPlayer;					//플레이어클래스 생성
	vector<cAirplane*>	m_vecEnemy;					//적비행기들의 집합 생성
	cImage*				m_bg;
	cAstar*				m_astar;

	///////에이스타
	
	

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
	bool CheckCollision(cAirplane* pAirplane);		//적군생성시 플레이어비행기와의 중복을 방지하기위한 충돌함수
	void OutMap(HDC hDest);
};

