#include "stdafx.h"
#include "cMainGame.h"
#include"cCharater.h"
#include"cAddCircle.h"
#include"cAddLine.h"

#include"cObstacle.h"

//#include "cAirplane.h"

cMainGame::cMainGame()
	: m_hMemDC(NULL)										//�ڵ��ʱ�ȭ�� �÷��̾�Ŭ���� �����Ҵ�
	, m_hBitmap(NULL)
	, m_hOldBitmap(NULL)
	,idle(false)
	,m_fScale(0.0f)
	,m_fx(0.0f)
	,m_fy(0.0f)
	,num(0)
	, incircle(false)
	,incircleline(false)
	,iscircleline(false)
	,isShift(false)
	,fp(NULL)
	, isobstacle(false)
	
	
	
{
	ch = new cCharater("mario.bmp");
	ch1 = new cCharater("map1.bmp");
	ch2 = new cCharater("map2.bmp");
	cr = new cAddCircle;
	cal = new cAddLine;
	obstacle = new cObstacle;

	rcbother.left = 0;
	rcbother.top = 0;
	rcbother.right = 0;
	rcbother.bottom= 0;
}

cMainGame::~cMainGame()										//�Ҹ��� : ��ũ���Լ��� ��� ����������Ʈ�� �����Ҵ�� ��ü�� �����.
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(ch);
	SAFE_DELETE(ch1);
	SAFE_DELETE(ch2);
	SAFE_DELETE(cr);
	SAFE_DELETE(cal);
	ClearEnemy();
	//������
	auto iter = v_cr.begin();
	while (iter != v_cr.end())
	{
		SAFE_DELETE(*iter);
		iter = v_cr.erase(iter);
	}
	//������
	auto iter1 = v_cal.begin();
	while (iter1 != v_cal.end())
	{
		SAFE_DELETE(*iter1);
		iter1 = v_cal.erase(iter1);
	}
	//��ֹ� ����
	auto iter2 = v_ob.begin();
	while (iter2 != v_ob.end())
	{
		SAFE_DELETE(*iter2);
		iter2 = v_ob.erase(iter2);
	}
	
	//cTimeManager::GetInstance()->Destroy();
	g_pTimeManager->Destroy();

	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
}
int x, y = 0;

void cMainGame::Init()										//�ʱ�ȭ���ΰ���
{
	srand((unsigned int)time(NULL));						//�̰ž��ϸ� �����Լ� ����������������
	//InitStage(1);											//1���������� �ʱ�ȭ

	//���� ���
	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL)
	{
		iscircle = false;
		iscircleline = false;
		isShift = false;
		
		isobstacle = false;
		for (auto &p : v_ob)
		{
			p->setcollision(false);
		}
		
		return;
	}
	else
	{

		v_cr.clear();
		v_cal.clear();
		v_ob.clear();
		//�� ���� ����
		iscircle = true;
		iscircleline = true;
		isShift = false;
	
		//obstacle->collision = false;
		int listsize;
		int listsize1;
		int listsize2;
		fscanf_s(fp, "%d", &listsize);

		while (!feof(fp))
		{
			for (int i = 0; i < listsize; ++i)
			{
				cAddCircle* fcr = new cAddCircle;
				float x, y;
				int m_num;
				fscanf_s(fp, "%f %f %d", &x, &y, &m_num);
				fcr->setpointx(x);
				fcr->setpointy(y);
				fcr->setnum(m_num);
				num = m_num;
				v_cr.push_back(fcr);
			}
			//������ ����

			fscanf_s(fp, "%d", &listsize1);
			for (int i = 0; i < listsize1; ++i)
			{
				float x, x1, y, y1;
				cAddLine* fcal = new cAddLine;
				fscanf_s(fp, "%f %f %f %f", &x, &x1,
					&y, &y1);
				fcal->setpointx(x);
				fcal->setpointx1(x1);
				fcal->setpointy(y);
				fcal->setpointy1(y1);
				v_cal.push_back(fcal);
			}
			//��ֹ� ����
			fscanf_s(fp, "%d", &listsize2);
			for (int i = 0; i < listsize2; ++i)
			{
				float x, x1, y, y1; BOOL collision;
				cObstacle* loadob = new cObstacle;
				fscanf_s(fp, "%f %f %f %f", &x, &x1,
					&y, &y1);
				loadob->setpointx(x);
				loadob->setpointx1(x1);
				loadob->setpointy(y);
				loadob->setpointy1(y1);
				fscanf_s(fp, "%d", &collision);
				loadob->setcollision(collision);
				v_ob.push_back(loadob);
			}


		}




		//��ư�� ����ٸ� ȭ�鿡 ���콺 �������� ��ġ�� ��� �ִ����̾���
		fclose(fp);

	}

}



void cMainGame::Update()									//������Ʈ
{

	g_pTimeManager->Update();								//�̱���� Ÿ�ӸŴ����� ������Ʈ�Ѵ�.

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//���ߺ�ó��
	
	auto iter1 = v_cr.begin();

	//while (iter1 != v_cr.end())
	//{
	//
	//	
	//	auto iter2 = iter1;
	//	iter2++;
	//	while (iter2 != v_cr.end())
	//	{
	//		
	//	
	//	
	//		++iter2;
	//	}
	//	++iter1;
	//}

	while (iter1 != v_cr.end())
	{

		//���콺 ���浹
		if (pt.x > (*iter1)->getpointx() - (*iter1)->getRadius() * 2 &&
			pt.x <(*iter1)->getpointx() + (*iter1)->getRadius() * 2 &&
			pt.y >(*iter1)->getpointy() - (*iter1)->getRadius() * 2 &&
			pt.y < (*iter1)->getpointy() + (*iter1)->getRadius() * 2)
		{
			incircle = true;
			incircleline = true;
			break;
		}
		
		else
		{
			incircle = false;
			incircleline = false;
		}
		++iter1;

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
	}


	FillRect(m_hMemDC, &rc, GetSysColorBrush(COLOR_GRAYTEXT));

	//�׸��� �ϴ°�
	//��ư�׸���
	//�����ư
	cUtil::DrawRectangleCenter(m_hMemDC, 50, rc.right - 50, rc.top + 100, 255 + r1, 255 + g1, 255 + b1);
	TextOut(m_hMemDC, rc.right - 40, rc.top + 100, "SAVE", strlen("SAVE"));
	//�ҷ������ư
	cUtil::DrawRectangleCenter(m_hMemDC, 50, rc.right - 50, rc.top + 200, 255 + r2, 255 + g2, 255 + b2);
	TextOut(m_hMemDC, rc.right - 40, rc.top + 200, "LOAD", strlen("LOAD"));

	//�ʱ�ȭ ��ư
	cUtil::DrawRectangleCenter(m_hMemDC, 50, rc.right - 50, rc.top + 300, 255 + r3, 255 + g3, 255 + b3);
	TextOut(m_hMemDC, rc.right - 40, rc.top + 300, "RESET", strlen("RESET"));


	//���׸���
	if (iscircleline)
	{
		for (auto &iter : v_cal)
		{
			iter->moveRender(m_hMemDC);
		}
	}
	//���׸���
	if(iscircle)
	{
		//�������ͷ�����
		
		for (auto &iter : v_cr)
		{
			iter->Render(m_hMemDC, iter->getpointx(), iter->getpointy());
		}
		

		
	}

	//��ֹ� �׸���

	//cUtil::DrawRectangle(m_hMemDC, 50, rc.right - 50, rc.top + 300, 255 + r3, 255 + g3, 255 + b3);

		/*Rectangle(m_hMemDC, rcbother.left, rcbother.top, rcbother.right, rcbother.bottom);
		if (iscollision)
		{
			TextOut(m_hMemDC, (rcbother.left+rcbother.right) / 2,
				(rcbother.top + rcbother.bottom) / 2, "�浹", strlen("�浹"));
		}*/
	for (auto &iter2 : v_ob)
	{
		iter2->Render(m_hMemDC, iter2->getpointx(), iter2->getpointy(), iter2->getpointx1(), iter2->getpointy1());

	}
	
	
	
	
	
	
	
	//int	xtemp = cal->getpointx();
	//int	ytemp = cal->getpointy();
	//int	xtemp2 = cal->getpointx1();
	//int	ytemp2 = cal->getpointy1();
	//a = (xtemp2 - xtemp) / (ytemp2 - ytemp);
	//b = 0;
	//x = -b / a;
	//y = b;
	//if (0 == (xtemp2 - xtemp) / (ytemp2 - ytemp)*x + b - y);

	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_hMemDC, 0, 0, SRCCOPY);
}

void cMainGame::OnSize()
{
	DeleteObject(SelectObject(m_hMemDC, m_hOldBitmap));
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)											//Ű�����̺�Ʈó�������� �������Լ��� �����´�. 
	{
	case WM_MOUSEMOVE:
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		//��ư�浹 1. ����
		if (pt.x<rc.right&& pt.x>rc.right - 100 &&
			pt.y<rc.top + 150 && pt.y > rc.top + 50)
		{
			r1 = -125;
			g1 = -125;
			b1 = -125;
		}
		else
		{
			r1 = g1 = b1 = 0;
		}
		//��ư�浹 2. �ҷ�����
		if (pt.x<rc.right&& pt.x>rc.right - 100 &&
			pt.y<rc.top + 250 && pt.y > rc.top + 150)
		{
			r2 = -125;
			g2 = -125;
			b2 = -125;
		}
		else
		{
			r2 = g2 = b2 = 0;
		}

		//��ư�浹 3. �ʱ�ȭ
		if (pt.x<rc.right&& pt.x>rc.right - 100 &&
			pt.y<rc.top + 350 && pt.y > rc.top + 250)
		{
			r3 = -125;
			g3 = -125;
			b3 = -125;
		}
		else
		{
			r3 = g3 = b3 = 0;
		}


	}
	break;
	case WM_RBUTTONDOWN:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		if (incircleline)
		{

			cal->setpointx((float)pt.x);
			cal->setpointy((float)pt.y);



			iscircleline = true;

			//isobstacle = true;
		}

		if (isShift)
		{
			obstacle->setpointx((float)pt.x);
			obstacle->setpointy((float)pt.y);


		}


	}break;
	case WM_RBUTTONUP:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		cObstacle* tempob = new cObstacle;



		if (incircleline)
		{

			cal->setpointx1((float)pt.x);
			cal->setpointy1((float)pt.y);

			iscircleline = true;
			cAddLine* line = new cAddLine;
			line->setpointx(cal->getpointx());
			line->setpointy(cal->getpointy());
			line->setpointx1(cal->getpointx1());
			line->setpointy1(cal->getpointy1());
			v_cal.push_back(line);

			v_iob = v_ob.begin();
			while (v_iob != v_ob.end())
			{
				rcbother.left = obstacle->getpointx();
				rcbother.top = obstacle->getpointy();
				rcbother.right = obstacle->getpointx1();
				rcbother.bottom = obstacle->getpointy1();

				//��ֹ� �Ǵ�
				auto xtemp = cal->getpointx();
				auto ytemp = cal->getpointy();
				auto xtemp2 = cal->getpointx1();
				auto ytemp2 = cal->getpointy1();

				a = (cal->getpointy1() - cal->getpointy()) /
					(cal->getpointx1() - cal->getpointx());//y = ax + b; py = apx+b b= py - a*px
																		 //y-b/a = x
				b = ytemp - a * xtemp;


				if (abs(xtemp2 - xtemp) >= abs(ytemp2 - ytemp))
				{//�Լ����ǿ� ���ѵα�

					for (size_t i = rcbother.left; i <= rcbother.right; i++)
					{
						if ((xtemp2 < rcbother.left&& xtemp < rcbother.left) ||
							(xtemp2 > rcbother.right&& xtemp > rcbother.right))
						{
							(*v_iob)->setcollision(false);

						}
						//auto apple = a * i + b;
						//y��ǥ ��
						else
						{
							if ((rcbother.top <= a * i + b &&
								a * i + b <= rcbother.bottom))
							{

								(*v_iob)->setcollision(true);

							}
						}




					}

				}//�Լ����ǿ� ���ѵα� ��
				else
				{
					for (size_t i = rcbother.top; i < rcbother.bottom; i++)
					{

						if ((ytemp2 < rcbother.top&& ytemp < rcbother.top)

							|| (ytemp2 > rcbother.bottom && ytemp > rcbother.bottom))
						{

							(*v_iob)->setcollision(false);

						}
						//auto banana = (i - b) / a;
						else
						{
							if (rcbother.left <= (i - b) / a && (i - b) / a <= rcbother.right)
							{

								(*v_iob)->setcollision(true);


							}

						}





					}

				}
				++v_iob;
			}





		}

		if (isShift)
		{

			//��ֹ�
			//����1���Լ�
			obstacle->setpointx1((float)pt.x);
			obstacle->setpointy1((float)pt.y);




			tempob->setpointx(obstacle->getpointx());
			tempob->setpointy(obstacle->getpointy());
			tempob->setpointx1(obstacle->getpointx1());
			tempob->setpointy1(obstacle->getpointy1());
			//tempob->setcollision(obstacle->getcollision());
			v_ob.push_back(tempob);



		}











	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		RECT rc;
		GetClientRect(g_hWnd, &rc);
		if (!incircle)
		{

			if (pt.x < rc.right - 120)
			{
				cAddCircle* crt = new cAddCircle;

				crt->setpointx(pt.x);
				crt->setpointy(pt.y);
				num++;
				crt->setnum(num);
				v_cr.push_back(crt);
				iscircle = true;
			}
		}

		//��ư 1. ����
		if (pt.x<rc.right&& pt.x>rc.right - 100 &&
			pt.y<rc.top + 150 && pt.y > rc.top + 50)
		{
			fopen_s(&fp, "data.txt", "w");
			if (fp == NULL)
				return;
			char szBuf[64];
			//�� ����
			sprintf_s(szBuf, "%d\n", v_cr.size());
			fwrite(szBuf, 1, strlen(szBuf), fp);
			auto iter = v_cr.begin();
			while (iter != v_cr.end())
			{

				sprintf_s(szBuf, "%f %f %d\n", (*iter)->getpointx(), (*iter)->getpointy(), (*iter)->getnum());
				fwrite(szBuf, 1, strlen(szBuf), fp);
				++iter;

			}
			//�� ����
			
			sprintf_s(szBuf, "%d\n", v_cal.size());
			fwrite(szBuf, 1, strlen(szBuf), fp);
			auto iter1 = v_cal.begin();
			while (iter1 != v_cal.end())
			{

				sprintf_s(szBuf, "%f %f %f %f\n", (*iter1)->getpointx(), (*iter1)->getpointx1(),
					(*iter1)->getpointy(), (*iter1)->getpointy1());
				fwrite(szBuf, 1, strlen(szBuf), fp);
				iter1++;

			}
			//��ֹ� ����
			sprintf_s(szBuf, "%d\n", v_ob.size());
			fwrite(szBuf, 1, strlen(szBuf), fp);

			auto iter2 = v_ob.begin();
			while (iter2 != v_ob.end())
			{

				sprintf_s(szBuf, "%f %f %f %f\n", (*iter2)->getpointx(), (*iter2)->getpointx1(),
					(*iter2)->getpointy(), (*iter2)->getpointy1());
				fwrite(szBuf, 1, strlen(szBuf), fp);
				sprintf_s(szBuf, "%d\n", (*iter2)->getcollision());
				fwrite(szBuf, 1, strlen(szBuf), fp);
				iter2++;

			}
			
			fclose(fp);
		}
		//��ư�浹 2. �ҷ�����
		if (pt.x<rc.right&& pt.x>rc.right - 100 &&
			pt.y<rc.top + 250 && pt.y > rc.top + 150)
		{
			//���� ���
			fopen_s(&fp, "data.txt", "r");
			if (fp == NULL)
			{
				iscircle = false;
				iscircleline = false;
				return;
			}
			else
			{
				v_cr.clear();
				v_cal.clear();
				v_ob.clear();
				//�� ���� ����
				iscircle = true;
				iscircleline = true;
				int listsize;
				int listsize1;
				int listsize2;
				fscanf_s(fp, "%d", &listsize);

				while (!feof(fp))
				{
					for (int i = 0; i < listsize; ++i)
					{
						cAddCircle* fcr = new cAddCircle;
						float x, y;
						int m_num;
						fscanf_s(fp, "%f %f %d", &x, &y, &m_num);
						fcr->setpointx(x);
						fcr->setpointy(y);
						fcr->setnum(m_num);
						num = m_num;
						v_cr.push_back(fcr);
					}
					//������ ����

					fscanf_s(fp, "%d", &listsize1);
					for (int i = 0; i < listsize1; ++i)
					{
						float x, x1, y, y1;
						cAddLine* fcal = new cAddLine;
						fscanf_s(fp, "%f %f %f %f", &x, &x1,
							&y, &y1);
						fcal->setpointx(x);
						fcal->setpointx1(x1);
						fcal->setpointy(y);
						fcal->setpointy1(y1);
						v_cal.push_back(fcal);
					}
					//��ֹ� ����
					fscanf_s(fp, "%d", &listsize2);
					for (int i = 0; i < listsize2; ++i)
					{
						float x, x1, y, y1; BOOL collision;
						cObstacle* loadob = new cObstacle;
						fscanf_s(fp, "%f %f %f %f", &x, &x1,
							&y, &y1);
						loadob->setpointx(x);
						loadob->setpointx1(x1);
						loadob->setpointy(y);
						loadob->setpointy1(y1);
						fscanf_s(fp, "%d", &collision);

						loadob->setcollision(collision);
						v_ob.push_back(loadob);
					}


				}




				//��ư�� ����ٸ� ȭ�鿡 ���콺 �������� ��ġ�� ��� �ִ����̾���
				fclose(fp);
			}
		}
		//��ư�浹 3. �ʱ�ȭ
		if (pt.x<rc.right&& pt.x>rc.right - 100 &&
			pt.y<rc.top + 350 && pt.y > rc.top + 250)
		{
			//������
			auto iter = v_cr.begin();
			while (iter != v_cr.end())
			{
				SAFE_DELETE(*iter);
				iter = v_cr.erase(iter);
			}
			//������
			auto iter1 = v_cal.begin();
			while (iter1 != v_cal.end())
			{
				SAFE_DELETE(*iter1);
				iter1 = v_cal.erase(iter1);
			}
			//��ֹ� ����
			auto iter2 = v_ob.begin();
			while (iter2 != v_ob.end())
			{
				SAFE_DELETE(*iter2);
				iter2 = v_ob.erase(iter2);
			}
			num = 0;
			//cr->setnum(0);

		}
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{

		case VK_SHIFT:
		{
			isShift = true;
		}
		break;

		case VK_LEFT:
		{			//����

		}
		break;
		case VK_RIGHT:
		{
			//������
		}
		break;


		}
	}
	
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{

		case VK_SHIFT:
		{
			isShift = false;
		}
		break;

		case VK_LEFT:
		{			//����

		}
		break;
		case VK_RIGHT:
		{
			//������
		}
		break;


		}
	}

	break;
	}
  }
	
}


	


void cMainGame::InitStage(int nStage)							//���������ʱ�ȭ
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);


}

void cMainGame::ClearEnemy()									//�������� �����.
{
	for (auto p : m_vecEnemy)
	{
		SAFE_DELETE(p);
	}
	m_vecEnemy.clear();
}

//void cMainGame::CharacterInit(float _x, float _y, float _size)
//{
//	if (m_bitmap == NULL)
//	{
//		m_bitmap = (HBITMAP)LoadImage(NULL, "mario.bmp", IMAGE_BITMAP, _size * 8, _size, LR_LOADFROMFILE);
//	}
//	BITMAP tmpBm;
//	GetObject(m_bitmap, sizeof(BITMAP), &tmpBm);
//	m_fScale = _size > tmpBm.bmHeight ? tmpBm.bmHeight : _size;
//	m_fx = _x;
//	m_fy = _y;
//}

