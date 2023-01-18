#pragma once
class cObstacle
{
	float x;
	float y;
	float x1;
	float y1;
	BOOL  collision;		//장애물이랑 선이랑충돌했을때 충돌을 렌더
public:
	cObstacle();
	~cObstacle();
	void Render(HDC hdc, float _x, float _y, float _x1, float _y1);
	void setpointx(float _x) { x = _x; }
	float getpointx() { return x; }
	void setpointy(float _y) { y = _y; }
	float getpointy() { return y; }
	void setpointx1(float _x1) { x1 = _x1; }
	float getpointx1() { return x1; }
	void setpointy1(float _y1) { y1 = _y1; }
	float getpointy1() { return y1; }
	void setcollision(BOOL _collision) { collision = _collision; }
	BOOL getcollision() { return collision; }
	
	
};

