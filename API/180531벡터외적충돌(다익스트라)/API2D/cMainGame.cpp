#include "stdafx.h"
#include "cMainGame.h"
#include "cNode.h"
#include "cCharacter.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	, m_pEdgeFrom(NULL)
	, m_pEdgeTo(NULL)
	, m_pRadioButton(NULL)
	, m_ulGdiplusToken(0)
{
	
}

cMainGame::~cMainGame()
{
	for (auto p : m_vecNode)
	{
		SAFE_DELETE(p);
	}

	m_vecNode.clear();

	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		SAFE_DELETE(m_pButton[i]);
	}

	g_pTimeManager->Destroy();

	GdiplusShutdown(m_ulGdiplusToken);

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}

void cMainGame::Init()
{
	srand((unsigned int)time(NULL));

	GdiplusStartupInput gsi;
	GdiplusStartup(&m_ulGdiplusToken, &gsi, NULL);

	Load();
	m_pEditState = cNodeEditState::GetInstance();
	m_pEditState->Init(this);

	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	//===================================================================//
	//��ư�簢������
	RECT rcBtn;
	SetRect(&rcBtn, rc.right - 120, 20, rc.right - 20, 60);
	//����簢��
	m_pButton[eButton::E_BTN_SAVE] = new cButton();
	m_pButton[eButton::E_BTN_SAVE]->Init(rcBtn, "Save");//�̸�����
	m_pButton[eButton::E_BTN_SAVE]->SetDelegate(this);
	m_pButton[eButton::E_BTN_SAVE]->SetTag(eButton::E_BTN_SAVE);

	//���»簢��
	SetRect(&rcBtn, rc.right - 120, 70, rc.right - 20, 110);
	m_pButton[eButton::E_BTN_RESET] = new cButton();
	m_pButton[eButton::E_BTN_RESET]->Init(rcBtn, "Reset");
	m_pButton[eButton::E_BTN_RESET]->SetDelegate(this);
	m_pButton[eButton::E_BTN_RESET]->SetTag(eButton::E_BTN_RESET);


	//==================================================================//
	//������ư ����
	m_pRadioButton = new cRadioButton;
	RECT rcRadio;
	SetRect(&rcRadio, 10, 10, 120, 121);
	m_pRadioButton->Init(rcRadio);
	m_pRadioButton->AddItem("Node");
	m_pRadioButton->AddItem("Edge");
	m_pRadioButton->AddItem("Obstacle");
	m_pRadioButton->AddItem("LineCol");
	m_pRadioButton->SetDelegate(this);

	
	


	/*
	cVector2 v1(1, 0);
	cVector2 v2(0, 1);
	bool b = cVector2::CCW(v1, v2);
	b = b;
	*/
}

void cMainGame::Update()
{
	g_pTimeManager->Update();

	m_pEditState->Update();

	/*for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		if (m_pButton[i])
			m_pButton[i]->Update();
	}
	if (m_pRadioButton)
		m_pRadioButton->Update();*/
		//ĳ���� �̵� 
	if (ischargo)//ĳ���Ͱ� ���ߵǴ� ��Ȳ?
	{
		cVector2 v_ownstart(startx, starty);
		cVector2 v_owndesti(destinationx, destinationy);
		cVector2  v_start;
		cVector2  v_dest;
		POINT ptstart, ptdestination, ptstartnode, ptdestinationnode;
		ptstart.x = v_ownstart.x; ptstart.y = v_ownstart.y; ptdestination.x = v_owndesti.x; ptdestination.y = v_owndesti.y;
		ptstartnode.x = v_start.x; ptstartnode.y = v_start.y;
		//if (dijcollision(ptstart, ptdestination))//��ŸƮ�� ���������̰� ��ֹ��� �浹���ֳ�
		//{
		if (stardescollision)
		{
			
			if (!isarrived)
			{

				dijkstra(ptstart, ptdestination);
				for (auto nearnode : m_vecNode)
				{
					if (nearnode->GetNodeNum() == nStart)
					{
						v_start = nearnode->GetPos();//��������� �������� ���� ��ŸƮ�� �־���
						break;
					}
				}

				float distance = (v_start - v_ownstart).Len();
				m_fvDirx = ((v_start.x - v_ownstart.x) / distance);
				m_fvDiry = ((v_start.y - v_ownstart.y) / distance);
				startx = startx + m_fvDirx * 2;
				starty = starty + m_fvDiry * 2;

				if ((int)startx >= v_start.x - 1 && (int)starty >= v_start.y - 1)
				{
					isarrived = true;
				}
			}
			else{
				if (!isarrived2)
				{
					//ù��° ��忡 ������������ ���� ���������� �浹�� �˻��Ѵ�.
					if (dijcollision(ptstartnode, ptdestination))
					{
						dijkstra(ptstartnode, ptdestination);
						for (auto nearnode : m_vecNode)
						{
							if (nearnode->GetNodeNum() == nDest)
							{
								v_dest = nearnode->GetPos();//��������� �������� ���� ��ŸƮ�� �־���
								break;
							}
						}

						float distance = (v_dest - v_ownstart).Len();
						m_fvDirx = ((v_dest.x - v_ownstart.x) / distance);
						m_fvDiry = ((v_dest.y - v_ownstart.y) / distance);
						startx = startx + m_fvDirx * 2;
						starty = starty + m_fvDiry * 2;
						if ((int)startx >= v_dest.x - 1 && (int)starty >= v_dest.y - 1)
						{
							isarrived2 = true;
						}
						
					}
					else
					{
						isarrived2 = true;
					}

				}
				
				//ù��°��忡�� ���������� �׳ɰ���������׳ɰ���.
				else
				{
					float distance = (v_owndesti - v_ownstart).Len();
					m_fvDirx = ((destinationx - startx) / distance);
					m_fvDiry = ((destinationy - starty) / distance);
					startx = startx + m_fvDirx * 2;
					starty = starty + m_fvDiry * 2;
					
				}
			}
		}
	}
}


void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	if (m_hMemDC == NULL)
	{
		m_hMemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
		SetGraphicsMode(m_hMemDC, GM_ADVANCED);
	}

	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT));
	
	//���ͷ����;Ⱦ��� ���͵�ٷ����ϱ�
	for (size_t i = 0; i < m_vecObstacle.size(); i++)
	{
		//��ֹ�����
		cUtil::DrawRect(m_hMemDC, m_vecObstacle[i]);
	}

	for (size_t i = 0; i < m_vecEdge.size(); i += 2)
	{
		//��������
		cVector2 v1 = m_vecEdge[i]->GetPos();
		cVector2 v2 = m_vecEdge[i + 1]->GetPos();
		POINT pt1 = v1.ToPoint();
		POINT pt2 = v2.ToPoint();
		MoveToEx(m_hMemDC, pt1.x, pt1.y, NULL);
		LineTo(m_hMemDC, pt2.x, pt2.y);
		//����
		string s = to_string((v2 - v1).Len());//��Ʈ������ ĳ��Ʈ�ϴ¹� to_string
		//����
		cVector2 v = cVector2::Center(v2, v1);
		TextOut(m_hMemDC, v.x, v.y, s.c_str(), s.length());
	}

	for (auto p : m_vecNode)
	{
		//��������
		p->Render(m_hMemDC);
	}

	//����Ʈ��Ÿ�� ����
	m_pEditState->Render(m_hMemDC);

	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		//��ư����
		if (m_pButton[i])
			m_pButton[i]->Render(m_hMemDC);
	}

	//������ư ����
	if (m_pRadioButton)
		m_pRadioButton->Render(m_hMemDC);
	Ellipse(m_hMemDC, startx - 20, starty - 20, startx + 20, starty + 20);//��������ġ ���׸���
	TextOut(m_hMemDC, startx - 30, starty - 30, "start", strlen("start"));
	
	Ellipse(m_hMemDC, destinationx - 20, destinationy - 20, destinationx + 20, destinationy + 20);//��������ġ ���׸���
	TextOut(m_hMemDC, destinationx - 30, destinationy - 30, "destination", strlen("destination"));
	
	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}





//BOOL cMainGame::compare(cNode a, cNode b)
//{
//	float x, y = 0.0f;
//	float x1, y1 = 0.0f;
//	x = a.GetPos().x;
//	y = a.GetPos().y;
//	x1 = b.GetPos().x;
//	y1 = b.GetPos().y;
//	return a.GetPos() < b.GetPos();
//}


void cMainGame::dijkstra(POINT start,POINT destination)
{
	for (RECT rc : m_vecObstacle)
	{
		//SetRect(&rc, rc.left - 50, rc.top - 70, rc.right + 50, rc.bottom + 70);
		//���ͽ�Ʈ�� ���� ���ο� ���ã�� 
		vector<vector<float>> vecAdjMatrix;

		int nNUmNode = (int)m_vecNode.size();//����� �� ����
		vecAdjMatrix.resize(nNUmNode);
		for (size_t i = 0; i < vecAdjMatrix.size(); i++)
		{
			vecAdjMatrix[i].resize(m_vecNode.size());
			for (size_t j = 0; j < vecAdjMatrix.size(); j++)
			{
				vecAdjMatrix[i][j] = (i == j) ? 0 : FLT_MAX;
			}
		}
		//������ĸ���� ��

		for (size_t i = 0; i < m_vecEdge.size(); i += 2)
		{
			int n1 = m_vecEdge[i]->GetNodeNum();
			int n2 = m_vecEdge[i + 1]->GetNodeNum();
			cVector2 v1 = m_vecEdge[i]->GetPos();
			cVector2 v2 = m_vecEdge[i + 1]->GetPos();
			vecAdjMatrix[n1][n2] = (v2 - v1).Len();
			vecAdjMatrix[n2][n1] = vecAdjMatrix[n1][n2];
		}

		vector<bool> vecClose(nNUmNode);
		vector<int> vecVia(nNUmNode);
		vector<float> vecCost(nNUmNode);
		for (size_t i = 0; i < nNUmNode; i++)
		{
			vecClose[i] = false;
			vecVia[i] = -1;
			vecCost[i] = FLT_MAX;

		}
		//���⼭���� ��ŸƮ��带 ���ϱ����� ������������ �Ÿ����ϴ°����� �̿�

		float startdis, destdis;
		float max = FLT_MAX;
		//ó�� ���۳��ã��
		for (size_t i = 0; i < m_vecNode.size(); i++)
		{

			cVector2 v_node = m_vecNode[i]->GetPos();
			cVector2 v_start(start.x, start.y);
			cVector2 v_destination(destination.x, destination.y);
			POINT ptnode;
			ptnode.x= m_vecNode[i]->GetPos().x;
			ptnode.y= m_vecNode[i]->GetPos().y;
			//��������̶� ��尣�� ���̰Ÿ��� �浹�������� �н��Ѵ�
			if (cUtil::IsCollision(start, ptnode, rc))
			{
				continue;
			}
			if (cUtil::IsCollision(ptnode, destination, rc))
			{
				continue;
			}
			
			startdis = (v_destination - v_node).Len() + (v_node - v_start).Len();
			if (startdis < max)
			{
				max = startdis;
				nStart = m_vecNode[i]->GetNodeNum();
			}

		}vecCost[nStart] = 0;
		//�������� ���ã��
		for (size_t i = 0; i < m_vecNode.size(); i++)
		{

			cVector2 v_node = m_vecNode[i]->GetPos();
			cVector2 v_start(start.x, start.y);
			cVector2 v_destination(destination.x, destination.y);
			POINT ptnode;
			ptnode.x = m_vecNode[i]->GetPos().x;
			ptnode.y = m_vecNode[i]->GetPos().y;
			//��������̶� ��尣�� ���̰Ÿ��� �浹�������� �н��Ѵ�
			if (cUtil::IsCollision(destination, ptnode, rc))
			{
				continue;
			}
			if (cUtil::IsCollision(ptnode, start, rc))
			{
				continue;
			}

			destdis = (v_destination - v_node).Len() + (v_node - v_start).Len();
			if (destdis < max)
			{
				max = destdis;
				nDest = m_vecNode[i]->GetNodeNum();
			}

		}
		//������� ���ĳ�
		for (size_t i = 0; i < nNUmNode; i++)
		{
			int nMinCostNode = -1; //���� ���
			float fMinCost = FLT_MAX;

			for (size_t j = 0; j < nNUmNode; j++)
			{
				if (vecClose[j]) continue;

				if (vecCost[j] < fMinCost)
				{
					fMinCost = vecCost[j];
					nMinCostNode = j;

				}

			}


			assert(nMinCostNode >= 0);
			vecClose[nMinCostNode] = true;

			for (size_t j = 0; j < nNUmNode; j++)
			{
				if (vecClose[j]) continue;
				if (vecCost[j] > vecCost[nMinCostNode] + vecAdjMatrix[nMinCostNode][j])
				{
					vecCost[j] = vecCost[nMinCostNode] + vecAdjMatrix[nMinCostNode][j];
					vecVia[j] = nMinCostNode;
				}
			}

		}
		int a = 0;
	}
}


BOOL cMainGame::dijcollision(POINT start,POINT destination)
{
	for (RECT rc : m_vecObstacle)
	{
		if (rc.left == 0 && rc.right == 0 && rc.top == 0 && rc.bottom == 0)
			continue;
		SetRect(&rc, rc.left - 50, rc.top -70, rc.right + 50, rc.bottom + 70);
		if (cUtil::IsCollision(start, destination, rc))//���̶� �簢���̶� �浹�ߴ��� ���к��Ϳ���
		{
			return true;
		}
	}

	return false;
}

void cMainGame::charmoving(cVector2 destination ,int n)
{
	
	//ó�� ��ŸƮ���� �̵�
	
	
	//
	/*cVector2 v1(destinationx, destinationy);
	cVector2 v2(startx, starty);
	float distance = (v2 - v1).Len();
	m_fvDirx = ((destinationx - startx) / distance);
	m_fvDiry = ((destinationy - starty) / distance);
	startx = startx + m_fvDirx * 2;
	starty = starty + m_fvDiry * 2;*/
}

void cMainGame::OnSize()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pRadioButton->WndProc(hWnd, message, wParam, lParam))
		return;
	for (int i = 0; i < eButton::E_BTN_COUNT; i++)
	{
		if (m_pButton[i]->WndProc(hWnd, message, wParam, lParam))
			return;
	}
	if (m_pEditState->WndProc(hWnd, message, wParam, lParam))
		return;
	switch (message)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'S':
		{
			POINT ptmouse;
			GetCursorPos(&ptmouse);
			ScreenToClient(g_hWnd, &ptmouse);
			
			startx = ptmouse.x;
			starty = ptmouse.y;
			stardescollision = false;
			ischargo = false;
		}
		break;
		case 'D':
		{
			stardescollision = false;
			ischargo = false;
			
			POINT ptmouse;
			GetCursorPos(&ptmouse);
			ScreenToClient(g_hWnd, &ptmouse);
			destinationx = ptmouse.x;
			destinationy = ptmouse.y;
			
			POINT pt1, pt2;
			pt1.x = startx;
			pt1.y = starty;
			pt2.x = destinationx;
			pt2.y = destinationy;
			
			//��ŸƮ���� ���������� ���� ��ֹ��� �ɷ����� �浹�ߴ������� ���ͽ�Ʈ��˰��� ����
			
			if (dijcollision(pt1, pt2))
			{
				
				stardescollision = true;
				ischargo = true;

			}
			//�ƴϸ� �׳� ��ŸƮ���� ���������� ĳ���� �̵�
			else
			{
				stardescollision = false;
				ischargo = true;
			}
		}

		
		break;
		case VK_SPACE:
		{
			
		}
		break;
		
		default:
			break;
		}
	}
	break;
	
	}

	
}

void cMainGame::Reset()
{
	for (auto p : m_vecNode)
	{
		SAFE_DELETE(p);
	}
	m_vecNode.clear();
	m_vecEdge.clear();
	m_pEdgeFrom = NULL;
	m_pEdgeTo = NULL;
}

void cMainGame::Save()
{
	FILE* fp = NULL;
	fopen_s(&fp, "save.txt", "w");

	if (m_vecNode.empty())
	{
		fprintf_s(fp, "%d\n", 0);
		fclose(fp);
		return;
	}

	fprintf_s(fp, "%d\n", m_vecNode.size());
	for (auto p : m_vecNode)
	{
		p->SaveToFile(fp);
	}

	fprintf_s(fp, "%d\n", m_vecEdge.size() / 2);
	
	for (size_t i = 0; i < m_vecEdge.size(); i += 2)
	{
		fprintf_s(fp, "%d %d\n", m_vecEdge[i]->GetNodeNum(), m_vecEdge[i + 1]->GetNodeNum());
	}

	fprintf_s(fp, "%d\n", m_vecObstacle.size());

	for (size_t i = 0; i < m_vecObstacle.size(); i++)
	{
		fprintf_s(fp, "%d %d %d %d\n", 
			m_vecObstacle[i].left,
			m_vecObstacle[i].top, 
			m_vecObstacle[i].right, 
			m_vecObstacle[i].bottom);
	}


	fclose(fp);
}

void cMainGame::Load()
{
	FILE* fp = NULL;
	fopen_s(&fp, "save.txt", "r");

	int nNumNode = 0;
	fscanf_s(fp, "%d\n", &nNumNode);
	if (nNumNode == 0)
	{
		fclose(fp); 
		return;
	}

	for (size_t i = 0; i < nNumNode; i++)
	{
		POINT pt;
		fscanf_s(fp, "%d %d\n", &pt.x, &pt.y);
		cVector2 v(pt);
		cNode* pNode = new cNode(v, m_vecNode.size());
		m_vecNode.push_back(pNode);
	}

	int nNumEdge = 0;
	fscanf_s(fp, "%d\n", &nNumEdge);
	for (size_t i = 0; i < nNumEdge; i++)
	{
		int e1, e2;
		fscanf_s(fp, "%d %d\n", &e1, &e2);
		m_vecEdge.push_back(m_vecNode[e1]);
		m_vecEdge.push_back(m_vecNode[e2]);
	}

	int nNumObstacle = 0;
	fscanf_s(fp, "%d\n", &nNumObstacle);
	for (size_t i = 0; i < nNumObstacle; i++)
	{
		RECT rc;
		fscanf_s(fp, "%d %d %d %d\n", &rc.left, &rc.top, &rc.right, &rc.bottom);
		m_vecObstacle.push_back(rc);
	}

	fclose(fp);
}

void cMainGame::AddNode(const cVector2 v)
{
	cNode* pNode = new cNode(v, m_vecNode.size());
	m_vecNode.push_back(pNode);
}

void cMainGame::AddEdge(cNode * pNodeFrom, cNode * pNodeTo)
{
	m_vecEdge.push_back(pNodeFrom);
	m_vecEdge.push_back(pNodeTo);
}

void cMainGame::AddObstacle(const RECT rc)
{
	m_vecObstacle.push_back(rc);
}

const vector<cNode*>& cMainGame::GetNode()
{
	return m_vecNode;
}

const vector<RECT>& cMainGame::GetObstacle()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_vecObstacle;
}

void cMainGame::OnClick(cButton * pSender)
{
	if (pSender->GetTag() == eButton::E_BTN_SAVE)
	{
		Save();
	}
	else if (pSender->GetTag() == eButton::E_BTN_RESET)
	{
		Reset();
	}
}

void cMainGame::OnSelectedItemChange(cRadioButton * pSender)
{
	switch (pSender->GetSelectedItem())
	{
	case 0:
	{
		m_pEditState = cNodeEditState::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 1:
	{
		m_pEditState = cEdgeEditState::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 2:
	{
		m_pEditState = cObstacleEditState::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	case 3:
	{
		m_pEditState = cLineCollisionTest::GetInstance();
		m_pEditState->Init(this);
	}
	break;
	default:
		break;
	}
}

