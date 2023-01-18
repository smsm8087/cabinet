#pragma once
class cCharacterImage
{
private:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

	int x; //캐릭터 좌표
	int y;



	float m_iPastTime;	//지나간 시간
	float m_iIdleTime;	//대기시간


public:
	cCharacterImage(const char * imageName);
	~cCharacterImage();

	int idir; //캐릭터의 방향
	int	iact; //캐릭터의 현재 행동
	bool IsMove; //현재 이동하느냐 안하느냐 체크
	int m_MapNum; //맵 번호


	void Render(HDC hdc);
	int FrameXPoint(int _num);




	//Get Set
	void SetX(int _x) { x = _x; } //x 좌표
	int GetX() { return x; }

	void SetY(int _y) { y = _y; } //y좌표
	int GetY() { return y; }

	void SetMapNum(int _MapNum) { m_MapNum = _MapNum; } //y좌표
	int GetMapNum() { return m_MapNum; }



};

