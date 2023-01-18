// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
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
//#include <wingdi.h>
#pragma comment(lib, "msimg32.lib")

using namespace std;
using namespace chrono;

extern HWND g_hWnd;

enum eDir
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
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


#define PI 3.14159265359f
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL; }
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
#include "cTimeManager.h"
#include "cVector2.h"
#include "cUtil.h"
#include "cPoint2N.h"