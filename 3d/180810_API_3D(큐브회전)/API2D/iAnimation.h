#pragma once
class iAnimation
{
public:
	virtual void SetInterval(float fDeltaTime) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc, RECT& rcDst) = 0;
};

