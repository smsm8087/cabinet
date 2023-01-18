#pragma once

#include "cButton.h"
#include "cRadioButton.h"
#include "iEditState.h"

class cNode;
class cCharacter;
//버튼의 종류
enum eButton
{
	E_BTN_SAVE,
	E_BTN_RESET,
	E_BTN_COUNT
};

class cMainGame
	: public iButtonDelegate
	, public iRadioButtonDelegate
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	//GDI그래픽스 쓰기위해 토큰을만들어야함
	ULONG_PTR		m_ulGdiplusToken;

	vector<cNode*>	m_vecNode;							//노드의벡터생성
	vector<cNode*>	m_vecEdge;							//노드의엣지생성
	cNode*			m_pEdgeFrom;						//노드의처음엣지포인터생성
	cNode*			m_pEdgeTo;							//노드의 도착지점엣지포인터 생성
	cButton*		m_pButton[E_BTN_COUNT];				//버튼의 버튼배열포인터 생성
	cRadioButton*	m_pRadioButton;						//라디오버튼의 라디오버튼생성
	iEditState*		m_pEditState;						//에디트스타일 생성
	vector<RECT>	m_vecObstacle;						//사각형의벡터 장애물생성
	float				startx;								//마우스포인터의 좌표를 인티저에저장
	float				starty;								//마우스포인터의 좌표를 인티저에저장
	float				destinationx;						//마우스포인터의 좌표를 인티저에저장
	float				destinationy;						//마우스포인터의 좌표를 인티저에저장
	vector<cNode*>::iterator m_ivecNode;//노드이터레이터
	vector<cNode*>	m_vecTemp;	//노드의벡터생성
	cNode*			m_pStart;
	cNode*			m_pBridge;
	cNode*			m_pDestination;
	BOOL			ischargo;							//캐릭터가 가야되는상황이냐
	BOOL			stardescollision;					//출발점과 목적지가 충돌했냐장애물에
	float			m_fvDirx;							//x축캐릭터가움직여야할 방향
	float			m_fvDiry;							//x축캐릭터가움직여야할 방향
	int nStart;											//시작지점노드번호
	int nDest;											//도착지점노드번호
	bool			isarrived;							//노드에 도착을했냐
	bool			isarrived2;							//2노드에 도착을했냐

public:
	cMainGame();
	~cMainGame();


	void Init();
	void Update();
	void Render(HDC hdc);
	
	//BOOL compare(cNode a, cNode b);
	void dijkstra(POINT start, POINT destination);
	BOOL dijcollision(POINT start, POINT destination);
	void charmoving(cVector2 destination, int n);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Reset();
	void Save();
	void Load();
	//노드를 추가함
	void AddNode(const cVector2 v);
	//엣지를 추가함
	void AddEdge(cNode* pNodeFrom, cNode* pNodeTo);
	//장애물을 추가함
	void AddObstacle(const RECT rc);

	//노드를받기위한 겟
	const vector<cNode*>& GetNode();
	//엣지를받기위한 겟
	const vector<RECT>& GetObstacle();


	//대리자들을 상속받앗음 버튼,라디오버튼 : 메인게임에서 처리함
	// iButtonDelegate override
	virtual void OnClick(cButton* pSender) override;

	// iRadioButtonDelegate override
	virtual void OnSelectedItemChange(cRadioButton* pSender) override;
};

