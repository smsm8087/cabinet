#pragma once
class cCharacterImage
{
private:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

	int x; //ĳ���� ��ǥ
	int y;



	float m_iPastTime;	//������ �ð�
	float m_iIdleTime;	//���ð�


public:
	cCharacterImage(const char * imageName);
	~cCharacterImage();

	int idir; //ĳ������ ����
	int	iact; //ĳ������ ���� �ൿ
	bool IsMove; //���� �̵��ϴ��� ���ϴ��� üũ
	int m_MapNum; //�� ��ȣ


	void Render(HDC hdc);
	int FrameXPoint(int _num);




	//Get Set
	void SetX(int _x) { x = _x; } //x ��ǥ
	int GetX() { return x; }

	void SetY(int _y) { y = _y; } //y��ǥ
	int GetY() { return y; }

	void SetMapNum(int _MapNum) { m_MapNum = _MapNum; } //y��ǥ
	int GetMapNum() { return m_MapNum; }



};

