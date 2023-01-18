// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include<Ole2.h>
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
#include<map>
#include <assert.h>
#include <gdiplus.h>


//구조체 클래스
#include "cStruct.h"
enum eNodeType
{
	E_START = 0,
	E_EMPTY = 1,
	E_WALL = 2,
	E_DEST = 3,
	E_PATH = 4
};

struct Wall
{
	int Tilesize;
	int WallCount;
	POINT pt;
	int Tileindex;
	int rowindex, colindex;
	eNodeType walltype;
};
//ENUM 클래스
#include "cEnum.h"

#pragma comment(lib, "gdiplus")
#pragma comment(lib,"msimg32.lib")

using namespace std;
using namespace chrono;
using namespace Gdiplus;

extern HWND g_hWnd;

#define PI 3.14159265359f
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL; }

#include "cTimeManager.h"
#include "cVector2.h"
#include "cUtil.h"
#include "cPoint2N.h"
#include<set>