#pragma once
class cVector2
{
public:
	cVector2(float _x = 0.0f, float _y = 0.0f);
	cVector2(const POINT& pt);
	~cVector2();
	
	float x;
	float y;

	cVector2 operator+(const cVector2& v);
	cVector2 operator-(const cVector2& v);
	cVector2 operator*(float f);
	BOOL operator!=(const cVector2& v);
	BOOL operator==(const cVector2& v);
	//����Ʈ�� ������ xy��ĳ�����Ͽ��������� ����Ʈ�� ��ȯ
	POINT ToPoint();
	float Len();
	float LenSq();
	cVector2 Normalize();
	//������ǥ���� �߾����
	static cVector2 Center(const cVector2& v1, const cVector2& v2);
	//ī����Ŭ�������� ���Ϳ���
	static float CCW(const cVector2& v1, const cVector2& v2);
};

