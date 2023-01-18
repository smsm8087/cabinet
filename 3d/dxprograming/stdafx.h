// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define KEYBOARD InputManager::GetInstance()


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include<d3d9.h>//기본적인 DX함수가 정의
#include<d3dx9.h>//x가 붙은함수가 정의
#include <vector>
#include <iostream>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include"InputManager.h"
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
extern HWND g_hWnd;
using namespace std;

enum
{
	E_LINE,
	E_TRIANGLE,
	E_RECTANGLE,
	E_NONE
};