#pragma once

class cMainGame;
class cNode;

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

class cNodeEditState : public iEditState
{
public:
	SINGLETON(cNodeEditState);
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

class cEdgeEditState : public iEditState
{
private:
	cNode * m_pEdgeFrom;
	cNode * m_pEdgeTo;
public:
	SINGLETON(cEdgeEditState);
private:
	cNode* PickNode(LPARAM lParam);
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

class cObstacleEditState : public iEditState
{
public:
	SINGLETON(cObstacleEditState);

private:
	bool	m_isLButtonDown;
	POINT	m_ptLT;
	POINT	m_ptRB;

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

class cLineCollisionTest : public iEditState
{
public:
	SINGLETON(cLineCollisionTest);

private:
	bool	m_isLButtonDown;
	POINT	m_ptLineFrom;
	POINT	m_ptLineTo;

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};