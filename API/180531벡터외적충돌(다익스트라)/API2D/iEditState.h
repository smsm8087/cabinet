#pragma once
//����Ʈ ����� ������ư������
class cMainGame;
class cNode;
//����Ʈ ��Ÿ�� �θ�
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
//����Ʈ��Ÿ�� <���>
class cNodeEditState : public iEditState
{
public:
	SINGLETON(cNodeEditState);
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
//����Ʈ��Ÿ�� <����(��)>
class cEdgeEditState : public iEditState
{
private:
	cNode * m_pEdgeFrom;//��߳��
	cNode * m_pEdgeTo;//�������
public:
	SINGLETON(cEdgeEditState);
private:
	cNode* PickNode(LPARAM lParam);//���� ���������� �׳�� ��ȯ�ϴ� �Լ�
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
//����Ʈ��Ÿ�� <��ֹ�>
class cObstacleEditState : public iEditState
{
public:
	SINGLETON(cObstacleEditState);

private:
	bool	m_isLButtonDown;//L��ư�� ���ȳ�
	POINT	m_ptLT;			//����Ʈ�� rcleft,rctop���� ����
	POINT	m_ptRB;			//����Ʈ�� rcright,rcbottom���� ����

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};
//����Ʈ��Ÿ�� <�浹�׽�Ʈ>
class cLineCollisionTest : public iEditState
{
public:
	SINGLETON(cLineCollisionTest);

private:
	bool	m_isLButtonDown;  //L��ư�� ���ȳ�
	POINT	m_ptLineFrom;	  //����Ʈ�� ����ó�� ���� ����
	POINT	m_ptLineTo;		  //����Ʈ�� ���� �������� ���� ����

public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual bool WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};