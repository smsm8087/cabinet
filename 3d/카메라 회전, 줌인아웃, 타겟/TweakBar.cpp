#include "stdafx.h"
#include "AntTweakBar.h"
#include "TweakBar.h"

TweakBar* TweakBar::instance = NULL;

TweakBar * TweakBar::Get()
{
	if (instance == NULL)
		instance = new TweakBar();

	return instance;
}

void TweakBar::Delete()
{
	SAFE_DELETE(instance);
}

void TweakBar::Start()
{
	isDraw = true;

	BOOL result = TwInit(TW_DIRECT3D9, DEVICE);
	assert(result == TRUE);

	bar = TwNewBar("TweakBar");
	TwDefine("TweakBar color='0 128 255' alpha=128");
	TwDefine("TweakBar size='250 500'");
	TwDefine("TweakBar valueswidth=120");
	TwDefine("TweakBar movable=false");
}

void TweakBar::InputProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TwEventWin(wnd, msg, wParam, lParam);
}

void TweakBar::Render()
{
	TwDraw();
}

TweakBar::TweakBar()
{
	
}

TweakBar::~TweakBar()
{
	TwTerminate();
}
