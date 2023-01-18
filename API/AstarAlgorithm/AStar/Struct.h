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
	int F; // F 비용
	int G; // G 시작점으로 부터의 현재지점까지의 거리(이동비용) 가로, 세로 비용 : 10, 대각선 비용 : 14
	int H; // 현재지점으로 부터 장애물을 무시한 도착점까지의 예상 거리(예상 이동비용)
	int p_G; // 부모의 G값을 이용하여 최적화 된 길을 찾는다.
	AStarDirect Direct; // 부모로 부터 자신의 방향. (추측; 길을 검색할 때.)
	AStarDirect p_Direct; // 부모를 바라보는 뱡향. (흔적; 길을 역순으로 오브젝트가 찾아 갈때.)
	int list; // 0사용하지않음 / 1열림 / 2닫힘 / 3벽
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