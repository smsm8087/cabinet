#include "stdafx.h"
#include "ConvexHull.h"

bool Comp(const Point &angle, const Point &angle2)
{
	return angle.angle < angle2.angle;
}

ConvexHull::ConvexHull()
	:mdao(0),
	mbeggi(0),
	mTotalPoint(0),
	mCount(1)
{

}


ConvexHull::~ConvexHull()
{
}

void ConvexHull::Init()
{
	//	1.8
	//	2.3
	//	4
	//	- 40, -51
	//	60, -50
	//	5, 5
	//	- 5, 60

	FILE *fp;
	fopen_s(&fp, "p3_2.txt", "r");
	
	if (fp == NULL)
		return;
	fscanf_s(fp, "%f", &mdao);
	fscanf_s(fp, "%f", &mbeggi);
	fscanf_s(fp, "%d", &mTotalPoint);
	mPointLocate.resize(mTotalPoint);
	mPointSource.resize(mTotalPoint);
	for (int i = 0; i < mTotalPoint; ++i)
	{
		fscanf_s(fp, "%d, %d", &mPointLocate[i].x, &mPointLocate[i].y);
		mPointLocate[i].x += 100;
		mPointLocate[i].y += 100;
	}
	fclose(fp);

	fopen_s(&fp, "p3_1.txt", "r");
	if (fp == NULL)
		return;
	fscanf_s(fp, "%f", &mdao);
	fscanf_s(fp, "%f", &mbeggi);
	fscanf_s(fp, "%d", &mTotalPoint);
	mPointLocate.resize(mTotalPoint);
	mPointSource.resize(mTotalPoint);
	for (int i = 0; i < mTotalPoint; ++i)
	{
		fscanf_s(fp, "%d, %d", &mPointSource[i].x, &mPointSource[i].y);
		mPointSource[i].x += 100;
		mPointSource[i].y += 100;
	}
	fclose(fp);

	FirstPoint(mPointLocate);
	PointAngle(mPointLocate);
	PointSort(mPointLocate, mConvexPoint);
	PointSearch(mPointLocate, mConvexPoint);
	
	//vectorcon에 값넣기
	if (!mConvexPoint.empty())
	{
		mConvexVec.resize(mConvexPoint.size());
		float convexsize = mConvexPoint.size();
		for (int i = 0; i < convexsize; ++i)
		{
			mConvexVec[i] = mConvexPoint.top();
			mConvexPoint.pop();
		}
	}

	//다오의 1바퀴 이동 거리 구하기
	for (int i = 0; i < mTotalPoint - 1; ++i)
	{
		float x =mPointSource[i + 1].x - mPointSource[i].x;
		float y = mPointSource[i + 1].y - mPointSource[i].y;
		mDistanceSource += sqrt(x*x + y * y);
	}
	float px = mPointSource[0].x - mPointSource[mPointSource.size()-1].x;
	float py = mPointSource[0].y - mPointSource[mPointSource.size() - 1].y;
	mDistanceSource += sqrt(px*px + py * py);

	mElapsedTimeSource = mDistanceSource / mdao;

	//배찌의 1바퀴 이동 거리 구하기
	for (int i = 0; i < mConvexVec.size() - 1; ++i)
	{
		float x = mConvexVec[i + 1].x - mConvexVec[i].x;
		float y = mConvexVec[i + 1].y - mConvexVec[i].y;
		mDistanceConvex += sqrt(x*x + y * y);
	}
	float cx = mConvexVec[0].x - mConvexVec[mConvexVec.size() - 1].x;
	float cy = mConvexVec[0].y - mConvexVec[mConvexVec.size() - 1].y;
	mDistanceConvex += sqrt(cx*cx + cy * cy);

	mElapsedTimeConvex = mDistanceConvex / mbeggi;
	//mElapsedTimeConvex += 60;

	mTimeSource = mElapsedTimeSource;
	mTimeConvex = mElapsedTimeConvex + 60;

	int x = 0;
}

void ConvexHull::Update()
{
	//
	if (mTimeSource < mTimeConvex)
	{
		mTimeSource += mElapsedTimeSource;
		mTimeConvex += mElapsedTimeConvex;
		mCount++;
	}
	else
	{

	}
}

void ConvexHull::Render(HDC hdc)
{
	HPEN MyPen, OldPen;
	MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	OldPen = (HPEN)SelectObject(hdc, MyPen);
	

	for (int i = 0; i < mTotalPoint-1; ++i)
	{
		MoveToEx(hdc, mPointSource[i].x, mPointSource[i].y,NULL);
		LineTo(hdc, mPointSource[i+1].x, mPointSource[i+1].y);
	}
	MoveToEx(hdc, mPointSource[0].x, mPointSource[0].y, NULL);
	LineTo(hdc, mPointSource[mTotalPoint-1].x, mPointSource[mTotalPoint - 1].y);
	
	SelectObject(hdc, OldPen);
	DeleteObject(MyPen);

	for (int i = 0; i < mConvexVec.size() - 1; ++i)//
	{
		MoveToEx(hdc, mConvexVec[i].x, mConvexVec[i].y, NULL);
		LineTo(hdc, mConvexVec[i + 1].x, mConvexVec[i + 1].y);
	}
	MoveToEx(hdc, mConvexVec[0].x, mConvexVec[0].y, NULL);
	LineTo(hdc, mConvexVec[mConvexVec.size() - 1].x, mConvexVec[mConvexVec.size() - 1].y);

	char szBuf[256];
	sprintf_s(szBuf, "다오가 1바퀴 걸리는 시간은 %f초",mElapsedTimeSource);
	//RECT rct;
	//SetRect(&rct, mfPosx - 10, mfPosy - 10, mfPosx + 10, mfPosy + 10);
	//DrawText(hdc, szBuf, strlen(szBuf), &rc, DT_CENTER | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);
	TextOut(hdc, 10, 10, szBuf, strlen(szBuf));

	sprintf_s(szBuf, "배찌가 1바퀴 걸리는 시간은 %f초", mElapsedTimeConvex);
	TextOut(hdc, 10, 50, szBuf, strlen(szBuf));

	sprintf_s(szBuf, "배찌가 이기려면 %d바퀴만큼 경기를 해야한다.", mCount);
	TextOut(hdc, 10, 90, szBuf, strlen(szBuf));

}

void ConvexHull::FirstPoint(std::vector <Point> &PointLocate)
{
	for (unsigned int i = 1; i < PointLocate.size(); i++)
	{
		if (PointLocate[0].y < PointLocate[i].y)
		{
			std::swap(PointLocate[0], PointLocate[i]);
		}
		else if (PointLocate[0].y == PointLocate[i].y)
		{
			if (PointLocate[0].x > PointLocate[i].x)
			{
				std::swap(PointLocate[0], PointLocate[i]);
			}
		}
	}
}

void ConvexHull::PointSort(std::vector<Point> &PointLocate, std::stack<Point> &ConvexPoint)
{
	int nSize = PointLocate.size();
	std::sort(PointLocate.begin(), PointLocate.end(), Comp);

	ConvexPoint.push(PointLocate[0]);
	ConvexPoint.push(PointLocate[1]);
	ConvexPoint.push(PointLocate[2]);
}

void ConvexHull::PointAngle(std::vector<Point> &PointLocate)
{
	float cx, cy, angle;

	for (unsigned int i = 1; i < PointLocate.size(); i++)
	{
		cx = (float)PointLocate[i].x - (float)PointLocate[0].x;
		cy = (float)PointLocate[i].y - (float)PointLocate[0].y;

		angle = atan2(cy, cx);
		angle = angle * 180 / (float)PI;
		PointLocate[i].angle = fabs(angle);
	}
	PointLocate[0].angle = 0;
}

void ConvexHull::PointSearch(std::vector<Point> &PointLocate, std::stack<Point> &ConvexPoint)
{
	Point P1 = PointLocate[1];
	Point P2 = PointLocate[2];

	for (unsigned int i = 3; i < PointLocate.size(); i++)
	{
		while (ccw(P1, P2, PointLocate[i]) <= 0 && PointLocate[i].angle > 0)
		{
			ConvexPoint.pop();

			P2 = ConvexPoint.top();
			ConvexPoint.pop();
			P1 = ConvexPoint.top();
			ConvexPoint.push(P2);
		}
		if (PointLocate[i].angle != 0)
		{
			ConvexPoint.push(PointLocate[i]);
		}

		P2 = ConvexPoint.top();
		ConvexPoint.pop();
		P1 = ConvexPoint.top();
		ConvexPoint.push(P2);
	}

}

int ConvexHull::ccw(Point p1, Point p2, Point p3)
{
	return (p2.x - p1.x)*((1000 - p3.y) - (1000 - p1.y)) - ((1000 - p2.y) - (1000 - p1.y))*(p3.x - p1.x);

}
