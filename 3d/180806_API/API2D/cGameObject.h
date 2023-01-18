#pragma once

class cGameObject : public cObject
{
protected:
	GETSET(cVector2, m_vWorldPos, WorldPos);
	GETSET(ST_SIZE, m_stSize, Size);

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void Update() {}
	virtual void Render(HDC hdc, cVector2* pMapPos) {}
};

