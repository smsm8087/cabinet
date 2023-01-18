#include "stdafx.h"
#include "cNode.h"


cNode::cNode() { }


cNode::~cNode() { }

void cNode::Init(int num, cVector2 pos, float radius) {
	m_nNum = num;
	m_vPos = pos;
	m_fRadius = radius;
}

void cNode::Render(HDC hdc) {

	for(auto e : m_vecEdges){
		if (e->GetNodeNum() < m_nNum)
			continue;

		MoveToEx(hdc, m_vPos.x, m_vPos.y, NULL);
		LineTo(hdc, e->GetNodePos().x, e->GetNodePos().y);
	}

	Ellipse(hdc,
		m_vPos.x - m_fRadius,
		m_vPos.y - m_fRadius,
		m_vPos.x + m_fRadius,
		m_vPos.y + m_fRadius);

	TCHAR szBuf[32];
	HFONT myFont = CreateFont(m_fRadius, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("±Ã¼­Ã¼"));
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetTextAlign(hdc, TA_CENTER);
	SetTextColor(hdc, RGB(0, 0, 0));

	cVector2 tempPos;
	int dec, sign;
	char *pbuffer;
	for (auto e : m_vecEdges) {
		tempPos = (e->GetNodePos() + m_vPos) / 2.0f;
		sprintf_s(szBuf, "%.0f", m_vPos.Distance(e->GetNodePos()));
		TextOut(hdc, tempPos.x, tempPos.y - m_fRadius / 2, szBuf, strlen(szBuf));
	}
	
	wsprintf(szBuf, TEXT("%d"), m_nNum);
	TextOut(hdc, m_vPos.x, m_vPos.y - m_fRadius/2, szBuf, strlen(szBuf));
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void cNode::AddEdge(cNode* node) {
	if (node->GetNodeNum() == m_nNum)
		return;

	for(auto e : m_vecEdges){
		if (e->GetNodeNum() == node->GetNodeNum())
			return;
	}

	m_vecEdges.push_back(node);
}

int cNode::GetNodeNum() {
	return m_nNum;
}

int cNode::GetEdgesSize()
{
	return m_vecEdges.size();
}

cVector2 cNode::GetNodePos() {
	return m_vPos;
}
