#pragma once
#include "cTimeManager.h"
#include "cNode.h"
#include <time.h>
#include <vector>
#include "cButton.h"
#include "cInfo.h"
#include "cObstacle.h"


class cMain : public iButtonDelegate
{
private:
	HDC					m_hMemDC;
	HBITMAP				m_hBitmap;
	HBITMAP				m_hOldBitmap;

	float				m_temptime;
	int					m_tempNodeNum;

	ULONG_PTR			m_ulGdiplusToken;

	cVector2			m_vMousePos;
	cVector2			m_vDrawStartPos;
	cVector2			m_vPlayerStartPos;
	cVector2			m_vPlayerDestPos;

	cNode*				m_nodeSelected;
	cNode*				m_nodeDest;
	cNode*				m_nodeStart;
	vector<cNode*>		m_vecNodes;
	vector<cNode*>		m_vecNodePath;

	cButton*			m_pButton1;
	cButton*			m_pButton2;

	vector<cObstacle*>	m_vecObstacles;
	cObstacle*			m_pTempObstacle;

	bool				m_bIsDrawingEdge;
	bool				m_bIsDrawingRect;
	bool				m_bIsSetPath;
	bool				m_bIsPathPossible;

	void ResetNodes();
	void ResetObstacles();
	void CreateNode(int x, int y);
	cNode* CheckIsSamePos(cVector2 pos);
	void SelectNode(int x, int y);
	void SetDestNode(int x, int y);
	void SetStartNode(int x, int y);
	void ConnectNode(int x, int y);
	void SetMousePos(int x, int y);
	void CreateObstacle(RECT rc);
	void SaveData();
	void LoadData();
	void Dijkstra();
	bool CheckFinish(vector<cInfo*> infos);
	cNode* FindNearestNode(cVector2 pos);
	void TrimPath();
	bool CheckObstacleCol(cVector2 pos1, cVector2 pos2);

public:
	cMain();
	~cMain();

	void Init();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void OnClick(int type);
};

