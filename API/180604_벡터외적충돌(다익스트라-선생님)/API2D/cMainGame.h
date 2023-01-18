#pragma once

#include "cButton.h"
#include "cRadioButton.h"
#include "iEditState.h"

class cNode;

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
	ULONG_PTR		m_ulGdiplusToken;

	vector<cNode*>	m_vecNode;
	vector<cNode*>	m_vecEdge;
	cNode*			m_pEdgeFrom;
	cNode*			m_pEdgeTo;
	cButton*		m_pButton[E_BTN_COUNT];
	cRadioButton*	m_pRadioButton;
	iEditState*		m_pEditState;
	vector<RECT>	m_vecObstacle;
	list<POINT>		m_lstPath;
	POINT			m_ptStart;
	POINT			m_ptDest;
public:
	cMainGame();
	~cMainGame();

	void Init();
	void Update();
	void Render(HDC hdc);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Reset();
	void Save();
	void Load();
	void AddNode(const cVector2 v);
	void AddEdge(cNode* pNodeFrom, cNode* pNodeTo);
	void AddObstacle(const RECT rc);

	list<POINT> Dijkstra(POINT p1, POINT p2);

	const vector<cNode*>& GetNode();
	const vector<RECT>& GetObstacle();

	// iButtonDelegate override
	virtual void OnClick(cButton* pSender) override;

	// iRadioButtonDelegate override
	virtual void OnSelectedItemChange(cRadioButton* pSender) override;
};

