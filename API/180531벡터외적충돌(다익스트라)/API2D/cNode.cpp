#include "stdafx.h"
#include "cNode.h"

cNode::cNode()
{
}

cNode::cNode(const cVector2& pt, int n)
	: m_vPos(pt)
	, m_nNodeNum(n)
{
}
cNode::~cNode()
{
}
//
//cNode::cNode()
//{
//}
//
//cNode::~cNode()
//{
//}

void cNode::Update()
{
}

void cNode::Render(HDC hdc)
{
	//����
	cUtil::DrawCircle(hdc, 30, m_vPos);

	//����Ʈ������ ��Ƽ���� �����ϱ����� ĳ����
	int x = m_vPos.x;
	int y = m_vPos.y;

	//����� ��ȣ ���� rc�����ؼ�
	RECT rc;
	SetRect(&rc, x - 10, y - 10, x + 10, y + 10);
	char szBuf[4];
	wsprintf(szBuf, "%d", m_nNodeNum);
	DrawText(hdc, szBuf, strlen(szBuf), &rc, DT_CENTER | DT_VCENTER | DT_NOCLIP | DT_SINGLELINE);
}

void cNode::SaveToFile(FILE * fp)
{
	POINT pt = m_vPos.ToPoint();
	fprintf_s(fp, "%d %d\n", pt.x, pt.y);
}

bool cNode::IsPicked(const POINT & pt)
{
	cVector2 v(pt);
	//���콺Ŀ���� ���ȿ� ���������� ���� ��ȯ �ߺ���������
	return (v - m_vPos).LenSq() < 30 * 30;
}


