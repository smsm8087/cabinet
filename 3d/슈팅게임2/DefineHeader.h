#pragma once
#define SafeRelease(p)	{ if(p) {(p)->Release(); (p) = nullptr; }}
#define SafeDelete(p)	{ if(p) delete (p); (p) = nullptr; }
#define SafeDeleteClass(p)	{ if(p) { (p)->Release(); delete (p);} (p) = nullptr; }
#define SafeDeleteArray(p)	{ if(p) delete[] (p); (p) = nullptr; }

//	Singleton Module, ½Ì±ÛÅæ ¸ðµâ
#include "DeviceModule.h"
#define _DeviceInstance DeviceModule::GetInstance()
#define _DEVICE			DeviceModule::GetInstance()->GetDevice()

#include "KeyModule.h"
#define _KEY			KeyModule::GetInstance()