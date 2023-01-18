#pragma once

class cCrt : public cGameObject
{
protected:
	GETSET(ST_SIZE, m_stMapSize, MapSize);

public:
	cCrt();
	virtual ~cCrt();

	virtual void Update() override;
	virtual void Render(HDC hdc, cVector2* pMapPos) override;
};

