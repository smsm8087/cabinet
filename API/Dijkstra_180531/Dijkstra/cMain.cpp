#include "stdafx.h"
#include "cMain.h"
#define Radius 20

void cMain::ResetNodes() {
	m_vecNodePath.clear();

	m_nodeSelected = NULL;
	m_nodeStart = NULL;
	m_nodeDest = NULL;

	for(auto& nd : m_vecNodes){
		delete nd;
	}

	m_vecNodes.clear();

	m_tempNodeNum = 1;
}

void cMain::ResetObstacles()
{
	m_pTempObstacle = NULL;

	for (auto& o : m_vecObstacles) {
		delete o;
	}

	m_vecObstacles.clear();
}

void cMain::CreateNode(int x, int y) {
	cVector2 pos = cVector2(x, y);

	if (CheckIsSamePos(pos) != NULL)
		return;

	cNode* newNode = new cNode();
	newNode->Init(m_tempNodeNum++, pos, Radius);

	m_vecNodes.push_back(newNode);
}

cNode* cMain::CheckIsSamePos(cVector2 pos)
{
	float radiusEx2 = (Radius + Radius) * (Radius + Radius);

	for (auto& nd : m_vecNodes) {
		if (radiusEx2 > pos.DistanceEx(nd->GetNodePos()))
			return nd;
	}

	return NULL;
}

void cMain::SelectNode(int x, int y)
{
	cVector2 pos = cVector2(x, y);
	cNode* tempNode;

	if ((tempNode = CheckIsSamePos(pos)) == NULL && m_nodeSelected != NULL)
		return;

	m_nodeSelected = tempNode;
}

void cMain::SetDestNode(int x, int y) {
	cVector2 pos = cVector2(x, y);
	m_vPlayerDestPos = pos;

	cNode* tempNode;

	if ((tempNode = FindNearestNode(pos)) == NULL)
		return;

	m_nodeDest = tempNode;
	m_bIsSetPath = false;
	Dijkstra();
}

void cMain::SetStartNode(int x, int y) {
	cVector2 pos = cVector2(x, y);
	m_vPlayerStartPos = pos;
	cNode* tempNode;

	if ((tempNode = FindNearestNode(pos)) == NULL)
		return;

	m_nodeStart = tempNode;
	m_bIsSetPath = false;
	Dijkstra();
}

void cMain::ConnectNode(int x, int y)
{
	cVector2 pos = cVector2(x, y);
	cNode* tempNode;

	if ((tempNode = CheckIsSamePos(pos)) == NULL) {
		m_nodeSelected = NULL;
		return;
	}

	m_nodeSelected->AddEdge(tempNode);
	tempNode->AddEdge(m_nodeSelected);

	m_nodeSelected = NULL;
}

void cMain::SetMousePos(int x, int y)
{
	cVector2 pos = cVector2(x, y);
	m_vMousePos = pos;
}

void cMain::CreateObstacle(RECT rc)
{
	cObstacle* tempObstacle = new cObstacle();
	tempObstacle->Init(rc);

	m_pTempObstacle = tempObstacle;

	m_vecObstacles.push_back(tempObstacle);
}

void cMain::SaveData()
{
	FILE* fp;
	char str[17];

	fopen_s(&fp, "Node_Date.txt", "w");

	int size = m_vecObstacles.size();

	fprintf(fp, "%d\n", size);

	RECT rc;

	for (auto o : m_vecObstacles) {
		rc = o->GetRect();
		fprintf(fp, "%d %d %d %d\n", rc.left, rc.top, rc.right, rc.bottom);
	}

	size = m_vecNodes.size();
		
	fprintf(fp, "%d\n", size);

	int x, y;

	for (auto nd : m_vecNodes) {
		x = (int)nd->GetNodePos().x;
		y = (int)nd->GetNodePos().y;
		fprintf(fp, "%d %d\n", x, y);
	}

	int edgesSize = 0;
	for (int i = 0; i < size; i++) {
		edgesSize = m_vecNodes[i]->GetEdgesSize();
		if (edgesSize > 0) {
			fprintf(fp, "%d %d\n", m_vecNodes[i]->GetNodeNum(), edgesSize);
			for (int j = 0; j < edgesSize; j++) {
				fprintf(fp, "%d\n", m_vecNodes[i]->m_vecEdges[j]->GetNodeNum());
			}
		}
	}

	fclose(fp);
}

void cMain::LoadData()
{
	FILE* fp = NULL;

	fopen_s(&fp, "Node_Date.txt", "r");

	int size;

	fscanf_s(fp, "%d\n", &size);

	m_vecObstacles.resize(size);

	RECT rc;

	cObstacle* newObstacle;

	for (int i = 0; i < size; i++) {
		fscanf_s(fp, "%d %d %d %d\n", &rc.left, &rc.top, &rc.right, &rc.bottom);
		newObstacle = new cObstacle();
		newObstacle->Init(rc);
		m_vecObstacles[i] = newObstacle;
	}

	fscanf_s(fp, "%d\n", &size);

	m_vecNodes.resize(size);

	int x, y;

	cVector2 pos;

	cNode* newNode;

	for (int i = 0; i < size; i++) {
		fscanf_s(fp, "%d %d\n", &x, &y);
		pos = cVector2(x, y);
		newNode = new cNode();
		newNode->Init(m_tempNodeNum++, pos, Radius);
		m_vecNodes[i] = newNode;
	}

	int num, edgesSize;
	int targetNode;

	while (!feof(fp)) {
		num = 0; edgesSize = 0;
		fscanf_s(fp, "%d %d\n", &num, &edgesSize);
		
		for (int i = 0; i < edgesSize; i++) {
			fscanf_s(fp, "%d\n", &targetNode);
			m_vecNodes[num - 1]->AddEdge(m_vecNodes[targetNode - 1]);
		}
	}

	fclose(fp);
}

void cMain::Dijkstra() {
	if (m_nodeStart == NULL || m_nodeDest == NULL || m_bIsSetPath)
		return;

	m_bIsPathPossible = true;

	vector<cInfo*> infos;
	int size = m_vecNodes.size();
	infos.resize(size);

	for(int i = 0; i < size; i++){
		infos[i] = new cInfo();
	}

	int startNum = m_nodeStart->GetNodeNum();

	infos[startNum - 1]->m_fCost = 0;

	int tempNum;

	while(!CheckFinish(infos)){

		// 검사 안한 노드 번호 가져오기
		for(int i = 0; i < size; i++){
			if (infos[i]->m_fCost == 99999999)
				continue;
			if (!infos[i]->m_bIsCheck){
				tempNum = i + 1;
				break;
			}
		}

		int edgeSize = m_vecNodes[tempNum - 1]->GetEdgesSize();

		cNode* targetNode;

		// 엣지 체크
		for(int i = 0; i < edgeSize; i++){
			targetNode = m_vecNodes[tempNum - 1]->m_vecEdges[i];

			// 연결된 길이 통해온 길과 같거나 이미 체크된 노드이면 통과
			if (targetNode->GetNodeNum() == infos[tempNum - 1]->m_nVia)
				continue;

			// 타겟 노드까지의 코스트가 현재 노드에서 이어졌을 때의 코스트보다 크면 갱신
			float tempEdgeDist = m_vecNodes[tempNum - 1]->GetNodePos().Distance(targetNode->GetNodePos());
			float totalDist = infos[tempNum - 1]->m_fCost + tempEdgeDist;

			if (totalDist < infos[targetNode->GetNodeNum() -1]->m_fCost){
				infos[targetNode->GetNodeNum() - 1]->m_fCost = totalDist;
				infos[targetNode->GetNodeNum() - 1]->m_nVia = tempNum;
				infos[targetNode->GetNodeNum() - 1]->m_bIsCheck = false;
			}
		}

		// 현재 노드 체크 완료
		infos[tempNum - 1]->m_bIsCheck = true;
	}

	// 결과가 나온 상태
	// 도착 노드에서부터 통해온 길을 통해 경로 완성
	int destNum = m_nodeDest->GetNodeNum();
	bool isFind = true;

	tempNum = destNum;

	m_vecNodePath.clear();

	while(tempNum != startNum){
		if (infos[tempNum - 1]->m_nVia == 0){
			isFind = false;
			m_bIsPathPossible = false;
			break;
		}

		m_vecNodePath.push_back(m_vecNodes[tempNum - 1]);
		tempNum = infos[tempNum - 1]->m_nVia;
	}

	if(isFind)
		m_vecNodePath.push_back(m_vecNodes[tempNum - 1]);

	// 완성
	m_bIsSetPath = true;
	TrimPath();
}

bool cMain::CheckFinish(vector<cInfo*> infos) {
	int size = infos.size();

	for(int i = 0; i < size; i++){
		if (infos[i]->m_fCost == 99999999)
			continue;
		if (!infos[i]->m_bIsCheck)
			return false;
	}

	return true;
}

cNode * cMain::FindNearestNode(cVector2 pos) {
	float shortestDist = 99999999;
	cNode* nearestNode = NULL;

	for(auto& nd : m_vecNodes){
		float tempDist = pos.Distance(nd->GetNodePos());
		if (shortestDist > tempDist){
			shortestDist = tempDist;
			nearestNode = nd;
		}
	}
	return nearestNode;
}

void cMain::TrimPath()
{
	if (!m_bIsPathPossible)
		return;

	// 시작 지점과 도착 지점이 바로 연결 가능
	if (!CheckObstacleCol(m_vPlayerStartPos, m_vPlayerDestPos)) {
		m_bIsPathPossible = true;
		m_vecNodePath.clear();
		return;
	}

	vector<cNode*> tempPath;

	int tempPathNum = 0;
	int pathSize = m_vecNodePath.size();
	for (int i = 0; i < pathSize; i++) {
		if (!CheckObstacleCol(m_vPlayerStartPos, m_vecNodePath[i]->GetNodePos())) {
			tempPathNum = i;
			tempPath.push_back(m_vecNodePath[i]);
			break;
		}
	}

	while (CheckObstacleCol(m_vecNodePath[tempPathNum]->GetNodePos(), m_vPlayerDestPos)) {
		for (int i = 0; i < tempPathNum; i++) {
			if (!CheckObstacleCol(m_vecNodePath[tempPathNum]->GetNodePos(), m_vecNodePath[i]->GetNodePos())) {
				tempPathNum = i;
				tempPath.push_back(m_vecNodePath[i]);
				break;
			}
		}
	}

	m_bIsPathPossible = true;
	m_vecNodePath = tempPath;
}

bool cMain::CheckObstacleCol(cVector2 pos1, cVector2 pos2)
{
	bool isCol = false;

	for (auto o : m_vecObstacles) {
		if (o->PathColCheck(pos1, pos2)) {
			isCol = true;
			break;
		}
	}

	return isCol;
}

cMain::cMain()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_nodeSelected(NULL)
	, m_nodeDest(NULL)
	, m_nodeStart(NULL)
	, m_pButton1(new cButton)
	, m_pButton2(new cButton)
	, m_tempNodeNum(1)
	, m_pTempObstacle(NULL)
	, m_bIsDrawingEdge(false)
	, m_bIsDrawingRect(false)
	, m_bIsSetPath(false)
	, m_bIsPathPossible(false)
{ }


cMain::~cMain() {
	ResetNodes();

	SAFE_DELETE(m_pButton1);
	SAFE_DELETE(m_pButton2);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMain::Init() {
	ResetObstacles();
	ResetNodes();

	LoadData();

	m_pButton1->SetDelegate(this);
	m_pButton2->SetDelegate(this);

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	m_vDrawStartPos = cVector2(0, 0);

	char str[32];

	POINT startPos;

	startPos.x = rc.right - 75;
	startPos.y = rc.bottom / 2 - 200;
	wsprintf(str, "SAVE");
	m_pButton1->Init(startPos, str, 0);

	startPos.x = rc.right - 75;
	startPos.y = rc.bottom / 2 - 100;
	wsprintf(str, "RESET");
	m_pButton2->Init(startPos, str, 1);

}

void cMain::Update() {
	g_pTimeManager->Update();

	if(m_bIsDrawingEdge){
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		SetMousePos(pt.x, pt.y);
		for (auto& o : m_vecObstacles) {
			o->Update(m_vDrawStartPos, m_vMousePos);
		}
	}

	if (m_bIsDrawingRect) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		SetMousePos(pt.x, pt.y);
	}

	if (m_pButton1)
		m_pButton1->Update();
	if (m_pButton2)
		m_pButton2->Update();
}

void cMain::Render(HDC hdc) {
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (m_hMemDC == NULL)
	{
		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	}

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_WINDOW));

	HPEN Pen, oPen;

	Pen = CreatePen(PS_SOLID, 6, RGB(100, 100, 255));
	oPen = (HPEN)SelectObject(m_hMemDC, Pen);

	if(m_bIsPathPossible){
		MoveToEx(m_hMemDC, m_vPlayerStartPos.x, m_vPlayerStartPos.y, NULL);
		int pathSize = m_vecNodePath.size();
		for(int i = 0; i < pathSize; i++){
			LineTo(m_hMemDC, m_vecNodePath[i]->GetNodePos().x, m_vecNodePath[i]->GetNodePos().y);
		}
		LineTo(m_hMemDC, m_vPlayerDestPos.x, m_vPlayerDestPos.y);
	}

	SelectObject(m_hMemDC, oPen);
	DeleteObject(Pen);
	DeleteObject(oPen);

	if (m_nodeSelected != NULL) {
		MoveToEx(m_hMemDC, m_nodeSelected->GetNodePos().x, m_nodeSelected->GetNodePos().y, NULL);
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		SetMousePos(pt.x, pt.y);
		LineTo(m_hMemDC, m_vMousePos.x, m_vMousePos.y);
	}

	for(auto nd : m_vecNodes){
		nd->Render(m_hMemDC);
	}

	
	TCHAR szBuf[32];
	HFONT myFont = CreateFont(Radius, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("궁서체"));
	HFONT oldFont = (HFONT)SelectObject(m_hMemDC, myFont);
	SetTextAlign(m_hMemDC, TA_CENTER);
	if(m_nodeStart != NULL){
		SetTextColor(m_hMemDC, RGB(0, 255, 0));
		wsprintf(szBuf, TEXT("START"));
		TextOut(m_hMemDC, m_nodeStart->GetNodePos().x, m_nodeStart->GetNodePos().y - Radius/2, szBuf, strlen(szBuf));
	}

	if(m_nodeDest != NULL){
		SetTextColor(m_hMemDC, RGB(255, 0, 0));
		wsprintf(szBuf, TEXT("DEST"));
		TextOut(m_hMemDC, m_nodeDest->GetNodePos().x, m_nodeDest->GetNodePos().y - Radius/2, szBuf, strlen(szBuf));
	}

	SetTextColor(m_hMemDC, RGB(0, 0, 0));
	SelectObject(m_hMemDC, oldFont);
	DeleteObject(myFont);

	if (m_pButton1)
		m_pButton1->Render(m_hMemDC);
	if (m_pButton2)
		m_pButton2->Render(m_hMemDC);

	for (auto o : m_vecObstacles) {
		o->Render(m_hMemDC);
	}

	if(m_bIsDrawingEdge){
		MoveToEx(m_hMemDC, m_vDrawStartPos.x, m_vDrawStartPos.y, NULL);
		LineTo(m_hMemDC, m_vMousePos.x, m_vMousePos.y);
	}

	if (m_bIsDrawingRect) {
		Rectangle(m_hMemDC, m_vDrawStartPos.x, m_vDrawStartPos.y, m_vMousePos.x, m_vMousePos.y);
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}

void cMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
				m_bIsDrawingRect = true;
				
			}
			else {
				CreateNode(x, y);
				m_bIsDrawingEdge = true;
			}

			m_vDrawStartPos = cVector2(x, y);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			SetMousePos(pt.x, pt.y);

			if (m_bIsDrawingRect) {
				RECT rc;
				rc.left = m_vDrawStartPos.x < m_vMousePos.x ? m_vDrawStartPos.x : m_vMousePos.x;
				rc.right = m_vDrawStartPos.x >= m_vMousePos.x ? m_vDrawStartPos.x : m_vMousePos.x;
				rc.top = m_vDrawStartPos.y < m_vMousePos.y ? m_vDrawStartPos.y : m_vMousePos.y;
				rc.bottom = m_vDrawStartPos.y >= m_vMousePos.y ? m_vDrawStartPos.y : m_vMousePos.y;
				CreateObstacle(rc);
			}

			m_pTempObstacle = NULL;

			m_bIsDrawingRect = false;
			m_bIsDrawingEdge = false;

			m_vDrawStartPos = cVector2(-10, -10);
			SetMousePos(-10, -10);

			for (auto& o : m_vecObstacles) {
				o->Update(m_vDrawStartPos, m_vMousePos);
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			SelectNode(x, y);

			x = 0;
		}
		break;
	case WM_RBUTTONUP:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			ConnectNode(x, y);
		}
		break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 'S':
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			SetStartNode(pt.x, pt.y);
		
		}
		break;
		case 'D':
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_hWnd, &pt);
			SetDestNode(pt.x, pt.y);
		}
		break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
	}
	break;
	}
}

void cMain::OnClick(int type)
{
	switch (type) {
	case 0:
		SaveData();
		break;
	case 1:
		ResetNodes();
		ResetObstacles();
		break;
	default:
		break;
	}
}
