#pragma once
#include "stdafx.h"

enum AStarDirect{
	RIGHT = 0,
	RT = 2,
	TOP = 4,
	LT = 6,
	LEFT = 8,
	LB = 10,
	BOTTOM = 12,
	RB = 14,
	_NONE,
	_DEST,
};

typedef struct tagAStarCost{
	// F = G + H;
	int F; // F ���
	int G; // G ���������� ������ �������������� �Ÿ�(�̵����) ����, ���� ��� : 10, �밢�� ��� : 14
	int H; // ������������ ���� ��ֹ��� ������ ������������ ���� �Ÿ�(���� �̵����)
	int p_G; // �θ��� G���� �̿��Ͽ� ����ȭ �� ���� ã�´�.
	AStarDirect Direct; // �θ�� ���� �ڽ��� ����. (����; ���� �˻��� ��.)
	AStarDirect p_Direct; // �θ� �ٶ󺸴� ����. (����; ���� �������� ������Ʈ�� ã�� ����.)
	int list; // 0����������� / 1���� / 2���� / 3��
}COST;

enum Option{
	OPTION_RECT,
	OPTION_ELLIPSE,
	OPTION_RESOURCE,
	OPTION_DESTINATION,
};
typedef struct tagTile{
	RECT rc;
	int Option;
	int index;
	COST cost;
}TILE;