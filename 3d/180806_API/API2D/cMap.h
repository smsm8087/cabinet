#pragma once
class cMap
{
protected:
	cVector2 m_vMapPos;

	vector<cGameObject*>	m_vecMapObject;
	GETSET_ADDREF(cGameObject*, m_pFocusObject, FocusObject);

	GETSET(ST_SIZE, m_stSize, Size);

public:
	cMap();
	virtual ~cMap();

	void Update();
	void Render(HDC hdc);
	void AddMapObject(cGameObject* pGameObject);
};

