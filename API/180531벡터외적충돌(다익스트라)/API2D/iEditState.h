#pragma once
//에디트 만들기 라디오버튼을위한
class cMainGame;
class cNode;
//에디트 스타일 부모
class iEditState
{
protected:
	cMainGame * m_pMainGame;
public:
	iEditState();
	~iEditState();
	virtual void Init(cMainGame* pMainGame);
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};
//에디트스타일 <노드>
class cNodeEditState : public iEditState
{
public:
	SINGLETON(cNodeEditState);
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
//에디트스타일 <엣지(선)>
class cEdgeEditState : public iEditState
{
private:
	cNode * m_pEdgeFrom;//출발노드
	cNode * m_pEdgeTo;//도착노드
public:
	SINGLETON(cEdgeEditState);
private:
	cNode* PickNode(LPARAM lParam);//원을 선택했을때 그노드 반환하는 함수
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
//에디트스타일 <장애물>
class cObstacleEditState : public iEditState
{
public:
	SINGLETON(cObstacleEditState);

private:
	bool	m_isLButtonDown;//L버튼이 눌렸냐
	POINT	m_ptLT;			//포인트를 rcleft,rctop으로 저장
	POINT	m_ptRB;			//포인트를 rcright,rcbottom으로 저장

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
//에디트스타일 <충돌테스트>
class cLineCollisionTest : public iEditState
{
public:
	SINGLETON(cLineCollisionTest);

private:
	bool	m_isLButtonDown;  //L버튼이 눌렸냐
	POINT	m_ptLineFrom;	  //포인트를 선의처음 으로 저장
	POINT	m_ptLineTo;		  //포인트를 선의 도착지점 으로 저장

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};