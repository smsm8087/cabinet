#include "stdafx.h"
#include "cSpriteSheetAnimation.h"
#include "cSpriteSheet.h"

cSpriteSheetAnimation::cSpriteSheetAnimation(const char* szSheetPath)
	: m_fAnimInterval(0.0f)
	, m_fPassedAnimTime(0.0f)
	, m_nCurrFrame(0)
{
	m_pSpriteSheet = new cSpriteSheet(szSheetPath);
	//겟레디 보이게하는거
	m_isDoneReady = true;
}


cSpriteSheetAnimation::~cSpriteSheetAnimation()
{
	SAFE_DELETE(m_pSpriteSheet);
}

void cSpriteSheetAnimation::SetAnimationNumFrame(int nNumFrame)
{
	//auto it = m_mapAnimation.find(sAnimName);
	/*it->first
	it->second*/
	//m_mapAnimation[sAnimName].resize(nNumFrame);
	m_pSpriteSheet->SetNumResion(nNumFrame);
}

void cSpriteSheetAnimation::SetAnimationFrame(int nFrame, RECT rcSrc)
{
	/*
	assert(m_mapAnimation.find(sAnimName) != m_mapAnimation.end() &&
	"이 함수를 호출하기 전에 SetAnimationNumFrame로 애니매이션 개수를 조정하세요!");
	*/
	//vector<RECT> vec = m_mapAnimation[sAnimName];
	//vec[nFrame] = rcSrc;
	//m_mapAnimation[sAnimName][nFrame] = rcSrc;
	m_pSpriteSheet->SetResion(nFrame, rcSrc);
}

void cSpriteSheetAnimation::SetAnimationFrame(int nNumFrame, int nNumAnimAtLine, POINT ptStart, ST_SIZE stFrameSize)
{
	SetAnimationNumFrame(nNumFrame);
	for (int i = 0; i < nNumFrame; i++)
	{
		int nRow = i / nNumAnimAtLine;
		int nCol = i % nNumAnimAtLine;
		RECT rc;
		rc.left = ptStart.x + stFrameSize.nWidth * nCol;
		rc.top = ptStart.y + stFrameSize.nHeight * nRow;
		rc.right = rc.left + stFrameSize.nWidth;
		rc.bottom = rc.top + stFrameSize.nHeight;
		//SetAnimationFrame(sAnimName, i, rc);
		m_pSpriteSheet->SetResion(i, rc);
	}
	m_size = stFrameSize;
}
void cSpriteSheetAnimation::SetAnimationFrameReverse(int nNumFrame, int nNumAnimAtLine, POINT ptStart, ST_SIZE stFrameSize)
{
	SetAnimationNumFrame(nNumFrame);
	for (int i = 0; i < nNumFrame; i++)
	{
		int nRow = i / nNumAnimAtLine;
		int nCol = i % nNumAnimAtLine;
		RECT rc;
		rc.left = ptStart.x - stFrameSize.nWidth * nCol;
		rc.top = ptStart.y +stFrameSize.nHeight * nRow;
		rc.right = rc.left + stFrameSize.nWidth;
		rc.bottom = rc.top + stFrameSize.nHeight;
		//SetAnimationFrame(sAnimName, i, rc);
		m_pSpriteSheet->SetResion(i, rc);
	}
	m_size = stFrameSize;
}
void cSpriteSheetAnimation::SetInterval(float fDeltaTime)
{
	m_fAnimInterval = fDeltaTime;
}

void cSpriteSheetAnimation::Update()
{
	m_fPassedAnimTime += g_pTimeManager->GetElapsedTime();
	
		while (m_fPassedAnimTime > m_fAnimInterval)
		{
			m_nCurrFrame = ++m_nCurrFrame % m_pSpriteSheet->GetNumResion();
			m_fPassedAnimTime -= m_fAnimInterval;
			if (m_isDoneReady == false)
			{
				if (m_nCurrFrame >= m_pSpriteSheet->GetNumResion() - 10)
				{
					m_isDoneReady = true;
				}
			}
		}
}

void cSpriteSheetAnimation::Render(HDC hdc, RECT& rcDst)
{
	m_pSpriteSheet->Render(hdc, m_nCurrFrame, rcDst, true);
}
