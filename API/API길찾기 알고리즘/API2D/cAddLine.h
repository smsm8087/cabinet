#pragma once



class cCheckcost;
class cAddLine
{

private:
	float x;
	float y;
	float x1;
	float y1;
	cCheckcost* check;
public:
	cAddLine();
	~cAddLine();
	void moveRender(HDC hdc);
	
	void setpointx(float _x) { x = _x; }
	float getpointx() { return x; }
	void setpointy(float _y) { y = _y; }
	float getpointy() { return y; }
	void setpointx1(float _x1) { x1 = _x1; }
	float getpointx1() { return x1; }
	void setpointy1(float _y1) { y1 = _y1; }
	float getpointy1() { return y1; }
};

