// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#include <d3d9.h> //기본적인 DX함수가 정의
#include <d3dx9.h>//X가 붙은 함수가 정의

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma comment(lib, "winmm.lib")

#define SAFE_DELETE(p) {if(p){delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p) {if(p){(p)->Release(); (p) = NULL;}}

#define DEVICE Device::GetInstance()->GetDevice()
#define KEYBOARD InputManager::GetInstance()
#define CAMERA Camera::GetInstance()
#define TIMER Timer::GetInstance()

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <mmsystem.h>
#include <functional>
#include <assert.h>
#include <string>

using namespace std;

//FrameWork Header File
#include "Device.h"
#include "InputManager.h"
#include "Camera.h"
#include "Texture.h"
#include "World.h"
#include "Xml.h"
#include "Animator.h"
#include "Shader.h"
//GameObject Header File
#include "Test.h"
//#include "PaintTool.h"
//#include "WVPTest.h"
//#include "SRTTest.h"
//#include "TextureTest.h"
#include "Planet.h"
#include "SolarSystem.h"
#include "Monster.h"
#include "XmlTest.h"
#include "ShaderTest.h"
#include "Timer.h"

//MainGame
#include "MainGame.h"
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

extern HWND hWnd;
extern D3DXVECTOR2 mousePos;
