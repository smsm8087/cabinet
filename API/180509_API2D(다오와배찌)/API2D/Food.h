#pragma once
class Food
{
private:
	HWND	mhWnd;
	float mfPosx;
	float mfPosy;
	float mfDiameter;
	bool mVisible;
public:
	Food();
	virtual ~Food();
public:
	void Init(float x, float y, HWND hwnd);
	void Update();
	void Render(HDC hdc);

public:
	void SetVisible(bool vi) { mVisible = vi; }
	bool GetVisible() { return mVisible; }

	void SetPosX(float x) { mfPosx = x; }
	float GetPosX() { return mfPosx; }

	void SetPosY(float y) { mfPosy = y; }
	float GetPosY() { return mfPosy; }

	void SetDiameter(float dia) { mfDiameter = dia; }
	float GetDiameter() { return mfDiameter; }
};

