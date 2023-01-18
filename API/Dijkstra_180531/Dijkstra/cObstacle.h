#pragma once
#include "cVector2.h"

class cObstacle {
	RECT m_rect;
	bool m_bIsCol;

	bool IsCollision(cVector2 pos1, cVector2 pos2);
	bool BoxColCheck(cVector2 r1_pos1, cVector2 r1_pos2, cVector2 r2_pos1, cVector2 r2_pos2);
	bool EdgeColCheck(cVector2 r1_pos1, cVector2 r1_pos2, cVector2 r2_pos1, cVector2 r2_pos2);
	float CrossProduct(cVector2 v1, cVector2 v2);

public:
	cObstacle();
	~cObstacle();

	void Init(RECT rect);
	void Update(cVector2 pos1, cVector2 pos2);
	void Render(HDC hdc);
	void SetLeftTop(cVector2 pos);
	void SetRightBottom(cVector2 pos);
	bool PathColCheck(cVector2 pos1, cVector2 pos2);
	RECT GetRect();
};

