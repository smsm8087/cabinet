#pragma once
class Actor
{
public:
	Actor();
	virtual ~Actor();
protected:
	bool mbDestroy; //삭제 되었는가
	D3DXVECTOR2 mPos;	//위치

public:
	virtual void Update();
	virtual void Render();

public:
	void SetDestroy(bool dest) { mbDestroy = dest; }
	bool GetDestroy() { return mbDestroy; }

	void SetPos(D3DXVECTOR2 pos) { mPos = pos; }
	D3DXVECTOR2 GetPos() { return mPos; }
};

