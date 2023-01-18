#pragma once

#include "iAnimation.h"

class cSpriteSheet;

class cSpriteSheetAnimation : public iAnimation
{
protected:
	cSpriteSheet *	m_pSpriteSheet;
	float			m_fAnimInterval;
	float			m_fPassedAnimTime;
	int				m_nCurrFrame;
	GETSET(bool, m_isDoneReady, isdoneReady);
	GETSET(ST_SIZE, m_size, size);

public:
	cSpriteSheetAnimation(const char* szSheetPath);
	virtual ~cSpriteSheetAnimation();

	virtual void SetAnimationNumFrame(int nNumFrame);
	virtual void SetAnimationFrame(int nFrame, RECT rcSrc);
	virtual void SetAnimationFrame(int nNumFrame, int nNumAnimAtLine, POINT ptStart, ST_SIZE stFrameSize);
	virtual void SetAnimationFrameReverse(int nNumFrame, int nNumAnimAtLine, POINT ptStart, ST_SIZE stFrameSize);

	// iAnimation override
	virtual void SetInterval(float fDeltaTime) override;
	virtual void Update() override;
	virtual void Render(HDC hdc, RECT& rcDst) override;
};

