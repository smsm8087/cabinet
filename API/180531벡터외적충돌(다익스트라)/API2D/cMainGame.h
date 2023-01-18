#pragma once

#include "cButton.h"
#include "cRadioButton.h"
#include "iEditState.h"

class cNode;
class cCharacter;
//��ư�� ����
enum eButton
{
	E_BTN_SAVE,
	E_BTN_RESET,
	E_BTN_COUNT
};

class cMainGame
	: public iButtonDelegate
	, public iRadioButtonDelegate
{
private:
	HDC				m_hMemDC;
	HBITMAP			m_hBitmap;
	HBITMAP			m_hOldBitmap;
	//GDI�׷��Ƚ� �������� ��ū����������
	ULONG_PTR		m_ulGdiplusToken;

	vector<cNode*>	m_vecNode;							//����Ǻ��ͻ���
	vector<cNode*>	m_vecEdge;							//����ǿ�������
	cNode*			m_pEdgeFrom;						//�����ó�����������ͻ���
	cNode*			m_pEdgeTo;							//����� ������������������ ����
	cButton*		m_pButton[E_BTN_COUNT];				//��ư�� ��ư�迭������ ����
	cRadioButton*	m_pRadioButton;						//������ư�� ������ư����
	iEditState*		m_pEditState;						//����Ʈ��Ÿ�� ����
	vector<RECT>	m_vecObstacle;						//�簢���Ǻ��� ��ֹ�����
	float				startx;								//���콺�������� ��ǥ�� ��Ƽ��������
	float				starty;								//���콺�������� ��ǥ�� ��Ƽ��������
	float				destinationx;						//���콺�������� ��ǥ�� ��Ƽ��������
	float				destinationy;						//���콺�������� ��ǥ�� ��Ƽ��������
	vector<cNode*>::iterator m_ivecNode;//������ͷ�����
	vector<cNode*>	m_vecTemp;	//����Ǻ��ͻ���
	cNode*			m_pStart;
	cNode*			m_pBridge;
	cNode*			m_pDestination;
	BOOL			ischargo;							//ĳ���Ͱ� ���ߵǴ»�Ȳ�̳�
	BOOL			stardescollision;					//������� �������� �浹�߳���ֹ���
	float			m_fvDirx;							//x��ĳ���Ͱ����������� ����
	float			m_fvDiry;							//x��ĳ���Ͱ����������� ����
	int nStart;											//������������ȣ
	int nDest;											//������������ȣ
	bool			isarrived;							//��忡 �������߳�
	bool			isarrived2;							//2��忡 �������߳�

public:
	cMainGame();
	~cMainGame();


	void Init();
	void Update();
	void Render(HDC hdc);
	
	//BOOL compare(cNode a, cNode b);
	void dijkstra(POINT start, POINT destination);
	BOOL dijcollision(POINT start, POINT destination);
	void charmoving(cVector2 destination, int n);
	void OnSize();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Reset();
	void Save();
	void Load();
	//��带 �߰���
	void AddNode(const cVector2 v);
	//������ �߰���
	void AddEdge(cNode* pNodeFrom, cNode* pNodeTo);
	//��ֹ��� �߰���
	void AddObstacle(const RECT rc);

	//��带�ޱ����� ��
	const vector<cNode*>& GetNode();
	//�������ޱ����� ��
	const vector<RECT>& GetObstacle();


	//�븮�ڵ��� ��ӹ޾��� ��ư,������ư : ���ΰ��ӿ��� ó����
	// iButtonDelegate override
	virtual void OnClick(cButton* pSender) override;

	// iRadioButtonDelegate override
	virtual void OnSelectedItemChange(cRadioButton* pSender) override;
};

