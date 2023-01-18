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
	//노드원
	cUtil::DrawCircle(hdc, 30, m_vPos);

	//포인트변수를 인티저로 저장하기위해 캐스팅
	int x = m_vPos.x;
	int y = m_vPos.y;

	//노드의 번호 생성 rc를통해서
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
	//마우스커서가 원안에 들어와있으면 거짓 반환 중복생성금지
	return (v - m_vPos).LenSq() < 30 * 30;
}


