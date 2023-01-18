// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Ole2.h>
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <chrono>
#include <vector>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <gdiplus.h>
#include "inc/fmod.h"

#pragma comment(lib, "lib/fmodex_vc.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "gdiplus")

using namespace std;
using namespace chrono;
using namespace Gdiplus;

extern HWND g_hWnd;

//게임 메인 구조
enum MAINSTATUS
{
	E_MAININIT,
	E_MAINLOADING,
	E_MAINFIGHT,
	E_MAINGAMEOVER,
	E_MAINCOUNT
};
enum CHARNAME
{
	DAO,
	DIGENIE,
	BAZZI,
	UNI,
	RANDOM,
	NAMECOUNT
};
enum CHARMOVE
{
	STAND,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIE,
	BUBBLE,
	POP,
	MOVECOUNT
};
enum PLAYER
{
	E_PLAYER1,
	E_PLAYER2,
	E_PLAYERCOUNT
};

enum ItemMove
{
	E_UP,
	E_DOWN
};
enum ItemValue
{
	E_SPEED,
	E_POWER,
	E_ADDBOMB,
	E_FULLPOPWER,
	E_NONE
};
struct ST_SIZE
{
	int nWidth;
	int nHeight;
	ST_SIZE(int _w = 0, int _h = 0) : nWidth(_w), nHeight(_h) {}
};

#define NUM_TILE	30
#define SQUARE_SIZE 20

#define MAX_SPEED 10.f

#define WINSIZE_X	800
#define WINSIZE_Y	600

#define TILE_W		40
#define TILE_H		40

#define PLAYER_X		40 		
#define PLAYER_Y		60
#define STAGE_ROW		13
#define	STAGE_COL		11

#define STAGE_START_X	60		//스테이지1 맵 시작좌표
#define STAGE_START_Y	81		//맵 y좌표 81


/////////////////////////
#define OBJ_TILE_W	40
#define OBJ_TILE_H	40
#define OBJ_TREE_W	40
#define OBJ_TREE_H	70
#define OBJ_HOUSE_W	40
#define OBJ_HOUSE_H	53
#define OBJ_BLOCK_W 40
#define OBJ_BLOCK_H 44

#define CHA_SHEET_W	200
#define CHA_SHEET_H	360
#define CHA_MOVE_W	50
#define CHA_MOVE_H	60
#define CHA_TRAP_W	60		//물풍선에 갇혔을 경우
#define CHA_TRAP_H	60
#define CHA_POP_W	65		//물풍선이 터질 경우
#define CHA_POP_H	60
#define CHA_COLL_W	40		//캐릭터 충돌 렉트
#define CHA_COLL_H	40

#define STAGE_WIDTH		13		//스테이지1 맵 칸의 수
#define STAGE_HEIGHT	11
#define STAGE_END_X		STAGE_START_X + OBJ_TILE_W * STAGE_WIDTH
#define STAGE_END_Y		STAGE_START_Y + OBJ_TILE_H * STAGE_HEIGHT
#define PLAYER_X		60 		
#define PLAYER_Y		60
#define PLAYER_END_X	STAGE_END_X - CHA_MOVE_W
#define PLAYER_END_Y	STAGE_END_Y - 65
#define BLOCK_MAX		STAGE_WIDTH * STAGE_HEIGHT

#define BOMB_W			40
#define BOMB_H			44
#define BOMB_LINE_W		40
#define BOMB_LINE_H		40
#define BOMBMAX			6
#define POWERMAX		6

#define PLAYER_SPAWN_0_X PLAYER_X
#define PLAYER_SPAWN_0_Y PLAYER_Y
#define PLAYER_SPAWN_1_X PLAYER_X
#define PLAYER_SPAWN_1_Y PLAYER_END_Y
#define PLAYER_SPAWN_2_X PLAYER_END_X
#define PLAYER_SPAWN_2_Y PLAYER_Y
#define PLAYER_SPAWN_3_X PLAYER_END_X
#define PLAYER_SPAWN_3_Y PLAYER_END_Y

#define PI 3.14159265359f
//크아
#define CHA_MOVE_W	60
#define CHA_MOVE_H	60
#define CHA_TRAP_W	60		//물풍선에 갇혔을 경우
#define CHA_TRAP_H	60
#define CHA_POP_W	65		//물풍선이 터질 경우
#define CHA_POP_H	60
#define CHA_COLL_W	40		//캐릭터 충돌 렉트
#define CHA_COLL_H	40

#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL; }
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL; }
#define SAFE_ADDREF(p) if(p) { (p)->AddRef(); }
#define SINGLETON(class_name) private:\
class_name();\
~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}
#define GETSET(varType, varName, funcName) protected:\
varType varName;\
public:\
	varType Get##funcName()\
	{\
		return varName;\
	}\
	void Set##funcName(varType var)\
	{\
		varName = var;\
	}
#define GETSETREF(varType, varName, funcName) protected:\
varType varName;\
public:\
	varType& Get##funcName()\
	{\
		return varName;\
	}\
	void Set##funcName(varType& var)\
	{\
		varName = var;\
	}
#define GET(varType, varName, funcName) protected:\
	varType			varName;\
public:\
	varType Get##funcName()\
	{\
		return varName;\
	}

#define SET(varType, varName, funcName) protected:\
	varType			varName;\
public:\
	void Set##funcName(varType var)\
	{\
		varName = var;\
	}

#define GETSET_ADDREF(varType, varName, funcName) protected:\
varType			varName;\
void Set##funcName(varType var)\
{\
	if (varName != var)\
	{\
		SAFE_ADDREF(var);\
		SAFE_RELEASE(varName);\
		varName = var;\
	}\
}\
varType Get##funcName()\
{\
	return varName;\
}

#include "cTimeManager.h"
#include "cVector2.h"
#include "cUtil.h"
#include "cPoint2N.h"
#include "cKeyManager.h"

