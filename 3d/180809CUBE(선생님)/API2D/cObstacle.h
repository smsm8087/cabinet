#pragma once

class cObstacle : public cGameObject
{
public:
	cObstacle();
	virtual ~cObstacle();

	virtual void Render(HDC hdc, cVector2* pMapPos) override;
};

