#pragma once
struct PosXY
{
	float posx;
	float posy;
};

class WormPlayer
{
public:
	WormPlayer();
	virtual ~WormPlayer();
private:
	HWND	mhWnd;
	float mfPosx;
	float mfPosy;
	float mfSpeed;
	float mfDiameter;
	int mIsKeyDown;
	int mProgress;
	bool mIsKeyDownAD;
	bool mIsKeyDownWS;
	FILE *fp;
	
	list<PosXY> mListPosXY;
public:
	void Init(float x, float y, HWND hwnd);
	void Update();
	void Render(HDC hdc);

public:
	void Save();
	void Load();
public:
	void SetPosX(float x) { mfPosx = x; }
	float GetPosX() { return mListPosXY.front().posx; }

	void SetPosY(float y) { mfPosy = y; }
	float GetPosY() { return mListPosXY.front().posy; }

	void SetDiameter(float dia) { mfDiameter = dia; }
	float GetDiameter() { return mfDiameter; }

	void SetKeyDown(int n) { mIsKeyDown = n; }
	int GetKetDown() { return mIsKeyDown; }

	list<PosXY> *GetList() { return &mListPosXY; }
};

