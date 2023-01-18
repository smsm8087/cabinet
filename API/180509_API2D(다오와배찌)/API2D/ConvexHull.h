#pragma once
struct Point
{
	int x, y;
	float angle;
};

class ConvexHull
{
public:
	ConvexHull();
	virtual ~ConvexHull();
private:
	float mdao;
	float mbeggi;
	float mDistanceSource;
	float mDistanceConvex;
	float mElapsedTimeSource;
	float mElapsedTimeConvex;
	float mTimeSource;
	float mTimeConvex;
	int mTotalPoint;
	int mCount;
	vector<Point> mPointLocate;
	vector<Point> mPointSource;
	stack<Point> mConvexPoint;
	vector<Point> mConvexVec;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
public:
	void FirstPoint(std::vector <Point> &PointLocate);
	//bool Comp(const Point *angle, const Point *angle2);
	void PointSort(std::vector<Point> &PointLocate, std::stack<Point> &ConvexPoint);
	void PointAngle(std::vector<Point> &PointLocate);
	void PointSearch(std::vector<Point> &PointLocate, std::stack<Point> &ConvexPoint);
	int ccw(Point p1, Point p2, Point p3);
};