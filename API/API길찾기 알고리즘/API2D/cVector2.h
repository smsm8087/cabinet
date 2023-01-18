#pragma once
class cVector2
{
public:
	cVector2(float _x = 0.0f, float _y = 0.0f);
	~cVector2();
	
	float x;
	float y;

	cVector2 operator+(const cVector2& v);				//�����ڿ����ε� 
	cVector2 operator-(const cVector2& v);
	cVector2 operator*(float f);
	POINT GetPoint();									//��ġ�� �޾ƿ�������
	float Len();										//����
	float LenSq();										//���� ��Ʈ
	cVector2 Normalize();								//�븻������
};

