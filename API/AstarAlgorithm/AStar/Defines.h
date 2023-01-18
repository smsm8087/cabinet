#pragma once

#pragma comment(lib, "msimg32.lib")

#include <vector>
#include <string>

#include "Struct.h"

using namespace std;
extern HWND g_hWnd;

#define WINDOWSX 1000
#define WINDOWSY 1000

#define TILE_SIZE 15	// 이 부분을 수정하시면 됩니다.

#define TILE_SQUARE 50

// TILE_SQUARE * TILE_SIZE = WINDOWSXY