#pragma once

class cImage;

class cSpriteSheet
{
protected:
	cImage *			m_pSpriteSheet;
	vector<RECT>		m_vecResion;
	map<string, int>	m_mapResion;

public:
	cSpriteSheet(const char* szSheetPath);
	virtual ~cSpriteSheet();

	void SetNumResion(int nNumRsn);
	size_t GetNumResion();
	void SetResion(int nRsnNo, RECT rcSrc);
	void SetResionName(int nRsnNo, string sRsnName);
	void Render(HDC hdc, int nRsnNo, RECT rcDst, bool isTransparent = false);
};

