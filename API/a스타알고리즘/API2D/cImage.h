#pragma once
class cImage
{private:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

	float m_iPastTime;	//������ �ð�
	float m_iIdleTime;	//���ð�
	int   act;			//�ð� ������������

public:
	cImage(const char * imageName);
	~cImage();

	int idir;			//���� ĳ������ ����
	void Render(HDC hdc, int x, int y, int radius);//rc�� ����Ʈ ž �׸��� �׸������� ��ǥ 
	void Rendermap(HDC hdc, int left, int top,  int right, int bottom);
	
};

