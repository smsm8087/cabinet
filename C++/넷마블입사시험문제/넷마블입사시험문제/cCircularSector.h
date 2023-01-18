#pragma once
class cCircularSector
{
private:
	float       playerx;
	float		playery;
	float		monsterx[4];
	float		monstery[4];
	float		clickx;
	float		clicky;
	bool		isin[4];
	

public:
	cCircularSector();
	~cCircularSector();
	void setplayer(float _x, float _y) { playerx = _x; playery = _y; }
	//void setmonster(float _x, float _y) { monsterx = _x; monstery = _y; }
	void setclick(float _x, float _y) { clickx = _x; clicky = _y; }
	void	isinCircularSector();
};

