#pragma once
class cImage
{private:
	HDC		m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBitmap;
	int		m_nWidth;
	int		m_nHeight;

	float m_iPastTime;	//지나간 시간
	float m_iIdleTime;	//대기시간
	int   act;			//시간 나누기프레임

public:
	cImage(const char * imageName);
	~cImage();

	int idir;			//지금 캐릭터의 방향
	void Render(HDC hdc, int x, int y, int radius);//rc의 레프트 탑 그리고 그릴곳까지 좌표 
	void Rendermap(HDC hdc, int left, int top,  int right, int bottom);
	/*void Fade(cImage imgPic, float imgOpac)
	{
		BITMAP bmpPic = new BITMAP(imgPic.m_nWidth, imgPic.Height);
		Graphics gfxPic = Graphics.FromImage(bmpPic);
		ColorMatrix cmxPic = new ColorMatrix();
		cmxPic.Matrix33 = imgOpac;
		ImageAttributes iaPic = new ImageAttributes();
		iaPic.SetColorMatrix(cmxPic, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);
		gfxPic.DrawImage(imgPic, new Rectangle(0, 0, bmpPic.Width, bmpPic.Height), 0, 0, imgPic.Width, imgPic.Height, GraphicsUnit.Pixel, iaPic);
		gfxPic.Dispose();

		return bmpPic;
	}*/



};

