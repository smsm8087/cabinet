#include "stdafx.h"
#include "WormPlayer.h"


WormPlayer::WormPlayer()
	:mfPosx(0),
	mfPosy(0),
	mfSpeed(10.0f),
	mfDiameter(10.0f),
	mIsKeyDown(0),
	mProgress(0),
	mIsKeyDownAD(NULL),
	mIsKeyDownWS(NULL)
{
}


WormPlayer::~WormPlayer()
{
}

void WormPlayer::Init(float x, float y,HWND hwnd)
{
	mfPosx = x;
	mfPosy = y;
	mhWnd = hwnd;
	PosXY posxy;
	posxy.posx = mfPosx;
	posxy.posy = mfPosy;
	mListPosXY.push_back(posxy);
	//PosXY posxy2;
	//posxy2.posx = mListPosXY.front().posx + mfDiameter;
	//posxy2.posy = mListPosXY.front().posy;
	//mListPosXY.push_back(posxy2);
	//PosXY posxy3;
	//auto iter = mListPosXY.begin();
	//iter++;
	//posxy3.posx = (*iter).posx + mfDiameter;
	//posxy3.posy = (*iter).posy;
	//mListPosXY.push_back(posxy3);
	//iter++;
	//PosXY posxy4;
	//posxy4.posx = (*iter).posx + mfDiameter;
	//posxy4.posy = (*iter).posy;
	//mListPosXY.push_back(posxy4);


}

void WormPlayer::Update()
{
	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (mIsKeyDown != 2 && mListPosXY.size() > 1)
		{
			mIsKeyDown = 1;
			mProgress = 1;
		}
		else if(mListPosXY.size() == 1)
		{
			mIsKeyDown = 1;
			mProgress = 1;
		}
		
			
	}
	else if (GetAsyncKeyState('D') & 0x8000)
	{
		if (mIsKeyDown != 1 && mListPosXY.size() > 1)
		{
			mIsKeyDown = 2;
			mProgress = 2;
		}
		else if (mListPosXY.size() == 1)
		{
			mIsKeyDown = 2;
			mProgress = 2;
		}
			
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		if (mIsKeyDown != 4 && mListPosXY.size() > 1)
		{
			mIsKeyDown = 3;
			mProgress = 3;
		}
		else if(mListPosXY.size() == 1)
		{
			mIsKeyDown = 3;
			mProgress = 3;
		}
			
	}
	else if (GetAsyncKeyState('S') & 0x8000)
	{
		if (mIsKeyDown != 3 && mListPosXY.size() > 1)
		{
			mIsKeyDown = 4;
			mProgress = 4;
		}
		else if (mListPosXY.size() == 1)
		{
			mIsKeyDown = 4;
			mProgress = 4;
		}
	}

	if (GetAsyncKeyState('P') & 0x8000)
	{
		mIsKeyDown = 9;
	}
	else if (GetAsyncKeyState('5') & 0x8000)
	{
		mIsKeyDown = 5;
	}
	else if (GetAsyncKeyState('6') & 0x8000)
	{
		mIsKeyDown = 6;
	}
	else if (GetAsyncKeyState('7') & 0x8000)
	{
		mIsKeyDown = 7;
	}

	float tempx, tempy,tempvx,tempvy;

	//윈도우의 크기 측정
	RECT rcWin;
	GetClientRect(mhWnd, &rcWin);

	switch (mIsKeyDown)
	{
	case 1:
	{
		if (mListPosXY.size() > 1)
		{
			PosXY poxXY = mListPosXY.back();
			mListPosXY.pop_back();

			poxXY.posx = mListPosXY.front().posx - (mfDiameter + 5);
			poxXY.posy = mListPosXY.front().posy;

			mListPosXY.push_front(poxXY);


			//윈도우의 크기가 0보다 작아지면 윈도우의 오른쪽으로 머리를 옮겨줌
			if (mListPosXY.front().posx < 0)
			{
				mListPosXY.front().posx = rcWin.right - mfDiameter;
			}

		}
		else
		{
			if (mListPosXY.front().posx < 0)
			{
				mListPosXY.front().posx = rcWin.right - mfDiameter;
			}
			mListPosXY.front().posx -= mfSpeed;
		}
	}
		
		
		break;
	case 2:
	{
		if (mListPosXY.size() > 1)
		{
			PosXY poxXY = mListPosXY.back();
			mListPosXY.pop_back();

			poxXY.posx = mListPosXY.front().posx + (mfDiameter + 5);
			poxXY.posy = mListPosXY.front().posy;

			mListPosXY.push_front(poxXY);

			if (mListPosXY.front().posx > rcWin.right)
			{
				mListPosXY.front().posx = 0 + mfDiameter;
			}
		}
		else
		{
			mListPosXY.front().posx += mfSpeed;

			if (mListPosXY.front().posx > rcWin.right)
			{
				mListPosXY.front().posx = 0 + mfDiameter;
			}
		}
	}
		
		
		break;
	case 3:
	{
		if (mListPosXY.size() > 1)
		{
			PosXY poxXY = mListPosXY.back();
			mListPosXY.pop_back();

			poxXY.posx = mListPosXY.front().posx;
			poxXY.posy = mListPosXY.front().posy - (mfDiameter + 5);

			mListPosXY.push_front(poxXY);

			if (mListPosXY.front().posy < 0)
			{
				mListPosXY.front().posy = rcWin.bottom - mfDiameter;
			}
		}
		else
		{
			mListPosXY.front().posy -= mfSpeed;
			if (mListPosXY.front().posy < 0)
			{
				mListPosXY.front().posy = rcWin.bottom - mfDiameter;
			}
		}


	}
		break;
	case 4:
	{
		if (mListPosXY.size() > 1)
		{
			PosXY poxXY = mListPosXY.back();
			mListPosXY.pop_back();

			poxXY.posx = mListPosXY.front().posx;
			poxXY.posy = mListPosXY.front().posy + (mfDiameter + 5);

			mListPosXY.push_front(poxXY);
			if (mListPosXY.front().posy > rcWin.bottom)
			{
				mListPosXY.front().posy = 0 + mfDiameter;
			}
		}
		else
		{
			if (mListPosXY.front().posy > rcWin.bottom)
			{
				mListPosXY.front().posy = 0 + mfDiameter;
			}
			mListPosXY.front().posy += mfSpeed;
		}
	}
		
		break;
	//save
	case 5:
	{
		Save();
	}

		break;
	//load
	case 6:
	{
		Load();		
	}
	break;
	//New game
	case 7:
	{
		RECT rci;
		GetClientRect(mhWnd, &rci);
		//리스트 초기화 해주고
		mListPosXY.clear();
		PosXY posi;
		posi.posx = rci.right/2;
		posi.posy = rci.bottom/2;
		mListPosXY.push_front(posi);
		mIsKeyDown = 0;


	}
	break;
	default:
		break;
	}	
}

void WormPlayer::Render(HDC hdc)
{

	RECT rc;
	//rc = RectMake(mfPosx, mfPosy, 10, 10);

	//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	if (!mListPosXY.empty())
	{
		//list<PosXY>::iterator iter;
		auto iter = mListPosXY.begin();
		while (iter != mListPosXY.end())
		{
			HBRUSH hBrush, hOldBrush;

			hBrush = CreateSolidBrush(RGB(0, 0, 255));

			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			rc = RectMake((*iter).posx, (*iter).posy, mfDiameter, mfDiameter);
			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush);


			++iter;
		}

	}

	//char szBuf[16];
	//wsprintf(szBuf, "1");
	//RECT rct;
	//SetRect(&rct, mfPosx - 10, mfPosy - 10, mfPosx + 10, mfPosy + 10);
	//DrawText(hdc, szBuf, strlen(szBuf), &rc, DT_CENTER | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);


}

void WormPlayer::Save()
{
	fopen_s(&fp, "data.txt", "w");
	if (fp == NULL)
		return;
	char szBuf[64];
	sprintf_s(szBuf, "%d\n", mListPosXY.size());
	fwrite(szBuf, 1, strlen(szBuf), fp);
	auto iter = mListPosXY.begin();
	while (iter != mListPosXY.end())
	{

		sprintf_s(szBuf, "%f %f\n", (*iter).posx, (*iter).posy);
		fwrite(szBuf, 1, strlen(szBuf), fp);
		++iter;

	}
	sprintf_s(szBuf, "%d", mProgress);
	fwrite(szBuf, 1, strlen(szBuf), fp);
	fclose(fp);

	mIsKeyDown = 0;
}

void WormPlayer::Load()
{
	fopen_s(&fp, "data.txt", "r");
	if (fp == NULL)
		return;
	mListPosXY.clear();
	int listsize;
	fscanf_s(fp, "%d", &listsize);
	while (!feof(fp))
	{
		for (int i = 0; i < listsize; ++i)
		{
			PosXY posxy;
			fscanf_s(fp, "%f %f", &posxy.posx, &posxy.posy);
			mListPosXY.push_back(posxy);
		}
		fscanf_s(fp, "%d", &mIsKeyDown);
	}

	//버튼을 만든다면 화면에 마우스 포인터의 위치가 어디에 있는지뽑아줌
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(mhWnd, &ptMouse);
	fclose(fp);
}
